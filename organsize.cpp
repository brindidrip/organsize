#include "organsize.h"
#include "dirFile.h"
#include "segment.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string.h>
#include <cstddef>
#include <sstream>
#include <algorithm>
#include <stdexcept>
#include <experimental/filesystem>

namespace fs = std::experimental::filesystem;

Organsize::Organsize(std::string file, std::string fileDir, std::string dirPath, int fileSize, int segments, int segSize, int remainderSS, int totalSegs)
    : mFilePath(file), mFileDir(fileDir), mdirPath(dirPath), mFileSize(fileSize), mSegments(segments), mSegSize(segSize), mRemainderSegSize(remainderSS), mTotalSegments(totalSegs)
{
    /*
    std::cout << "File Path: " << this->mFilePath << "\nDirectory Path: " << this->mdirPath << "\nFile Size: " << this->mFileSize << 
    "\nmSegments: " << this->mSegments << "\nSegment Size: " << this->mSegSize << "\nRemainder Segment Size: " << this->mRemainderSegSize << "\nTotal Segments: " <<
    mTotalSegments << std::endl;
    
    segmentFile();
    reconstructFile();
    */
}

Organsize::~Organsize(){}

void Organsize::segmentFile(){
    std::streampos fsize = 0;
    char * memblock;

    std::ifstream file ( this->mFilePath, std::ios::in|std::ios::binary|std::ios::ate);

    if (file.is_open())
    {
        fsize = file.tellg();
        memblock = new char [fsize];
        file.seekg(0, std::ios::beg);
        file.read(memblock, fsize);
        file.close();
    }

  
    std::ofstream subnode[this->mTotalSegments];
    std::stringstream sstm;

    long long sequence = 0;
    char sequenceHex[8];
    // Convert decimal to hex and output into a file
    long long totalSegments = this->mTotalSegments;
    char totalSegmentsHex[8];
    memcpy(totalSegmentsHex, &totalSegments, sizeof(totalSegmentsHex));

    // Randomize buffer with special signature    
    char randomByteBuffer[30];
    for(size_t i = 0; i < 30; i++){
            //randomByteBuffer[i] = rand() % 256;
            randomByteBuffer[i] = 0x3D;
            }

    for( int i=0; i <= this->mSegments; i++){
        std::cout << "i: " << i << std::endl;

        memcpy(sequenceHex, &sequence, sizeof(sequenceHex));

        sstm.str("");
        sstm << this->mdirPath << "/subnode" << i;

        subnode[i].open(sstm.str(), std::fstream::out | std::fstream::binary);

        if(i == this->mSegments){
            if(subnode[i]){
                subnode[i].write(memblock + (i * this->mSegSize) , this->mRemainderSegSize);
                subnode[i].write(randomByteBuffer, 28);
                subnode[i].write(sequenceHex, sizeof(sequenceHex));
                subnode[i].write(totalSegmentsHex, sizeof(totalSegmentsHex));
                sequence++;

            }
        }
        else if(subnode[i]){
            std::cout << i * this->mSegSize << std::endl;
            subnode[i].write(memblock + (i * this->mSegSize) , this->mSegSize);
            subnode[i].write(randomByteBuffer, 28);
            subnode[i].write(sequenceHex, sizeof(sequenceHex));
            subnode[i].write(totalSegmentsHex, sizeof(totalSegmentsHex));
            sequence++;
        }
        // Close subnodes, as there is a max number of files that can be opened simultaneously 
        subnode[i].close();
        std::cout << "i end: " << i << std::endl;

    }
}

// bug: if cancels out file explorer for path selection, path will be none 
void Organsize::reconstructFile( ){
    uint64_t totSegments = 0;
    uint64_t segSeqNum = 0;
    uint64_t lastSeqNum = 0;

    std::vector<Segment> segments;
  
    std::stringstream sstm;
    sstm.str("");
    sstm << this->mdirPath << "/reconstruction";

    std::ofstream reconstructedFile;
    reconstructedFile.open(sstm.str(), std::fstream::out | std::fstream::binary);

    for (auto &p : fs::directory_iterator(this->mFileDir)){

        std::ifstream fp ( p.path().string(), std::ios::binary);
        
        if (fp.fail())
        {
            throw std::invalid_argument("file '" + p.path().string() + "' opening error.");
        }

        // Load a segment into memory
        std::vector<unsigned char> segBytes((std::istreambuf_iterator<char>(fp)), (std::istreambuf_iterator<char>()));
        fp.close();

        // Vectors holding segment metadata in bytes in decimal form. Little endian
        std::vector <int> segTotalSegBytes;
        std::vector <int> segSeqBytes;
        
        for (uint i = segBytes.size() - 16; i<segBytes.size(); i++){
            // Grab last 8 bytes of segmented file for total number of segments
            if(i>=segBytes.size()-8)
            {
                segTotalSegBytes.push_back((int)segBytes[i]);
                }
            // Grab 8 bytes prior to last 8 bytes for segment sequence number
            else
            {
                segSeqBytes.push_back((int)segBytes[i]);
            }
        }
        
        // Convert container of bytes as a single decimal value
        const int base = 0x100;/* base 256 */ 
        // right to left, as it is little endian
        for (int i = sizeof(segTotalSegBytes); i > 0;)
        {
            totSegments *= base;
            totSegments += (int)segTotalSegBytes[--i];
        }

        for (int i = sizeof(segSeqBytes); i > 0;)
        {
            segSeqNum *= base;
            segSeqNum += (int)segSeqBytes[--i];
        }

        std::cout << "Total segments: " << totSegments << std::endl;
        std::cout << "Current sequence number: " << segSeqNum << std::endl;
        std::cout << "Last sequence number: " << lastSeqNum << std::endl;

        // First approach:
        // Store all segments in container and then sort them all by sequence number. 

        Segment segment(segSeqNum, 0, totSegments, segBytes, segments.size());
        segments.push_back(segment);

        /*
        // if out of sequence
        if(segSeqNum > (lastSeqNum + 1))
        {
            std::cout << "Out of sequence..." << std::endl;
            
            auto result = std::find_if(segments.begin(), segments.end(),
                [=](Segment s)
            {
                if(s.sequenceNum == segSeqNum)
                {   
                    return true;
                }
                else
                {
                    return false;
                }
            });

            // DNE in vector
            if (result == segments.end())
            {
                std::cout << "Not found in segments vector." << std::endl;
                std::cout << "Inserting " << segSeqNum << "at position: " << segments.size() << std::endl;
                Segment segment(segSeqNum, 0, totSegments, segBytes, segments.size());
                segments.push_back(segment);
            }

        }
        */

        // Clean-up
        lastSeqNum = segSeqNum;
        segTotalSegBytes.clear();
        segSeqBytes.clear();
        segBytes.erase(segBytes.begin(), segBytes.end());
        totSegments = 0;
        segSeqNum = 0;
        //delete segment;

    }
        if(reconstructedFile)
        {
            /*
            for(const Segment& s : segments)
            {
                std::cout << s.sequenceNum << std::endl;
            }*/

            std::sort(segments.begin(), segments.end(),
            [=](Segment s1, Segment s2)
            {
                if (s1.sequenceNum < s2.sequenceNum )
                {
                    return true;
                }
                else
                {
                    return false;
                }
            });
            
            for(const Segment& s: segments)
            {
                reconstructedFile.write((const char*)&s.segmentData[0], s.segmentData.size() - 44);
            }

           //std::cout << "Writing " << segSeqNum << "into reconstructed file" << std::endl;
           //reconstructedFile.write((const char*)&segBytes[0], segBytes.size());
           //reconstructedFile.close();
        }
}