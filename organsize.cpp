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

Organsize::Organsize(std::string file, std::string dirPath, int tier)
{
    this->mFilePath = file.c_str();
    this->dirPath = dirPath.c_str();

    // Analyze & prep file for segmentation
    if (!fileAnalysis(this->mFilePath)){
        return;
    }   

    //segmentFile(this->mFilePath);
    reconstructFile(this->dirPath);

}
Organsize::~Organsize(){}

bool Organsize::fileAnalysis(const char* filePath){
    // Check if file is valid
    std::ifstream f(filePath);
    std::cout << "Is file valid: " << f.good() << '\n';

    this->mfileSize = Organsize::fileSize(filePath);
    this->segmentSize = 1500;
    this->mSegments = (this->mfileSize / this->segmentSize);
    this->lastSegmentSize = this->mfileSize % this->segmentSize;

    std::cout << "Last segment size: " << this->lastSegmentSize << std::endl;
    std::cout << "Total segments: " << this->mSegments + 1 << std::endl;

    // Check filesize limitation
    std::cout << "File size: " << Organsize::fileSize(filePath) << '\n';

    return true;
}

void Organsize::segmentFile( const char* filePath){
    std::streampos fsize = 0;
    char * memblock;

    std::ifstream file ( filePath, std::ios::in|std::ios::binary|std::ios::ate);

    if (file.is_open())
    {
        fsize = file.tellg();
        memblock = new char [fsize];
        file.seekg(0, std::ios::beg);
        file.read(memblock, fsize);
        file.close();
    }

    std::ofstream subnode[this->mSegments + 1];
    std::stringstream sstm;

    long long sequence = 0;
    char sequenceHex[8];
    // Convert decimal to hex and output into a file
    // 999 is tmp holder
    long long totalSegments = 999999999999;
    char totalSegmentsHex[8];
    memcpy(totalSegmentsHex, &totalSegments, sizeof(totalSegmentsHex));

    // Randomize buffer with special signature    
    char randomByteBuffer[30];
    for(size_t i = 0; i < 30; i++){
            //randomByteBuffer[i] = rand() % 256;
            randomByteBuffer[i] = 0x3D;
            }

    for( int i=0; i <= this->mSegments; i++){
        
        memcpy(sequenceHex, &sequence, sizeof(sequenceHex));

        sstm.str("");
        sstm << "subnode" << i;
        
        subnode[i].open(sstm.str(), std::fstream::out | std::fstream::binary);

        //std::cout << totalSegments << std::endl;

        if(i == this->mSegments){
            if(subnode[i]){
                subnode[i].write(memblock + (i * this->segmentSize) ,this->lastSegmentSize);
                subnode[i].write(randomByteBuffer, 28);
                subnode[i].write(sequenceHex, sizeof(sequenceHex));
                subnode[i].write(totalSegmentsHex, sizeof(totalSegmentsHex));
                sequence++;
            }
        }

        else if(subnode[i]){
            subnode[i].write(memblock + (i * this->segmentSize) ,this->segmentSize);
            subnode[i].write(randomByteBuffer, 28);
            subnode[i].write(sequenceHex, sizeof(sequenceHex));
            subnode[i].write(totalSegmentsHex, sizeof(totalSegmentsHex));
            sequence++;
        }
        // Close subnodes, as there is a max number of files that can be opened simultaneously 
        subnode[i].close();
        
    }
    delete memblock;
}

void Organsize::reconstructFile( const char* directoryPath){
    uint64_t totSegments = 0;
    uint64_t segSeqNum = 0;
    uint64_t lastSeqNum = 0;

    std::vector<Segment> segments;
  
    // create a collection of segments and insert at front or back depending of seq num
    std::ofstream reconstructedFile;
    reconstructedFile.open("reconstruction", std::fstream::out | std::fstream::binary);

    for (auto &p : fs::directory_iterator(directoryPath)){

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

std::streampos Organsize::fileSize( const char* filePath ){
    std::streampos fsize = 0;
    std::ifstream file( filePath, std::ios::binary );

    fsize = file.tellg();
    file.seekg( 0, std::ios::end );
    fsize = file.tellg() - fsize;
    file.close();

    return fsize;
}   