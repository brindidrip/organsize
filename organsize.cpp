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
    char randomByteBuffer[8];
    for(size_t i = 0; i < 8; i++){
            //randomByteBuffer[i] = rand() % 256;
            randomByteBuffer[i] = 0x3D;
            }

    for( int i=0; i <= this->mSegments; i++){
        memcpy(sequenceHex, &sequence, sizeof(sequenceHex));

        sstm.str("");
        sstm << this->mdirPath << "/subnode" << i;

        subnode[i].open(sstm.str(), std::fstream::out | std::fstream::binary);

        if(i == this->mSegments){
            if(subnode[i]){
                subnode[i].write(memblock + (i * this->mSegSize) , this->mRemainderSegSize);
                subnode[i].write(randomByteBuffer, sizeof(randomByteBuffer));
                subnode[i].write(sequenceHex, sizeof(sequenceHex));
                subnode[i].write(totalSegmentsHex, sizeof(totalSegmentsHex));
                sequence++;
            }
        }
        else if(subnode[i]){
            subnode[i].write(memblock + (i * this->mSegSize) , this->mSegSize);
            subnode[i].write(randomByteBuffer, sizeof(randomByteBuffer));
            subnode[i].write(sequenceHex, sizeof(sequenceHex));
            subnode[i].write(totalSegmentsHex, sizeof(totalSegmentsHex));
            sequence++;
        }
        // Close subnodes, as there is a max number of files that can be opened simultaneously 
        subnode[i].close();
    }
}

void Organsize::reconstructFile( ){
    uint64_t totSegments = 0;
    uint64_t segSeqNum = 0;
    uint64_t segSigNum = 0;
    uint64_t lastSeqNum = 0;

    std::vector<Segment> segments;
  
    std::stringstream sstm;
    sstm.str("");
    sstm << this->mdirPath << "/reconstruction";

    std::ofstream reconstructedFile;
    reconstructedFile.open(sstm.str(), std::fstream::out | std::fstream::binary);

    // initialize initial segment signature storage 
    initInitialSegSig(this->mFilePath);

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
        std::vector <int> segSigBytes;
        
        for (uint i = segBytes.size()-24; i<segBytes.size(); i++){
            
            // Grab last 8 bytes of segmented file for total number of segments
            if( i >= segBytes.size() - 8)
            {
                segTotalSegBytes.push_back((int)segBytes[i]);
            }
            // Grab 8 bytes prior to last 8 bytes for segment sequence number
            else if ( i >= segBytes.size() - 16)
            {
                segSeqBytes.push_back((int)segBytes[i]);
            }
            else
            {
                segSigBytes.push_back((int)segBytes[i]);
            }
        }
    
        // Convert container of bytes as a single decimal value
        const int base = 0x100;/* base 256 */ 
        // right to left, as it is little endian
        for (int i = segTotalSegBytes.size(); i > 0;)
        {
            totSegments *= base;
            totSegments += (int)segTotalSegBytes[--i];
        }

        for (int i = segSeqBytes.size(); i > 0;)
        {
            segSeqNum *= base;
            segSeqNum += (int)segSeqBytes[--i];
        }

        for (int i = segSigBytes.size(); i > 0;)
        {
            segSigNum *= base;
            segSigNum += (int)segSigBytes[--i];
        }

        /*
        std::cout << "Total segments: " << totSegments << std::endl;
        std::cout << "Current sequence number: " << segSeqNum << std::endl;
        std::cout << "Last sequence number: " << lastSeqNum << std::endl;
        std::cout << "Seg signature number: " << segSigNum << std::endl;
        */

        if(!validateSegment(p.path().string(), this->mSegSize, segSigNum))
        {   
            //std::cout << "Segment is not valid: " <<p.path().string() << std::endl;
            // File is not part of the segment collection
            continue;
        }
        // First approach:
        // Store all segments in container and then sort them all by sequence number. 

        Segment segment(segSeqNum, 0, totSegments, segBytes, segments.size());
        segments.push_back(segment);

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
                reconstructedFile.write((const char*)&s.segmentData[0], s.segmentData.size() - 24);
            }

           //std::cout << "Writing " << segSeqNum << "into reconstructed file" << std::endl;
           //reconstructedFile.write((const char*)&segBytes[0], segBytes.size());
           //reconstructedFile.close();
        }
}

bool Organsize::validateSegment ( std::string fp, int segSize, uint64_t segSignature)
{
    // Compare against initial segment size and initial signature to validate
    if(segSignature == this->initialSegSig)
    {
        return true;
    }
    return false;
}

void Organsize::initInitialSegSig ( std::string fp )
{
    uint64_t initSegSigNum = 0;

    std::ifstream file ( fp, std::ios::binary);

        if (file.fail())
        {
            throw std::invalid_argument("file '" + fp + "' opening error.");
        }

        // Load a segment into memory
        std::vector<unsigned char> initsegBytes((std::istreambuf_iterator<char>(file)), (std::istreambuf_iterator<char>()));
        file.close();

        // Vectors holding segment metadata in bytes in decimal form. Little endian
        std::vector <int> initsegSigBytes;
        
        for (uint i = initsegBytes.size()-24; i<initsegBytes.size(); i++){
            
            // Grab last 8 bytes of segmented file for total number of segments
            if( i >= initsegBytes.size() - 8)
            {
                // Do nothing
            }
            // Grab 8 bytes prior to last 8 bytes for segment sequence number
            else if ( i >= initsegBytes.size() - 16)
            {
                // Do nothing
            }
            else
            {
                // Grab signature
                initsegSigBytes.push_back((int)initsegBytes[i]);
            }
        }
    
        // Convert container of bytes as a single decimal value
        const int base = 0x100;/* base 256 */ 
        // right to left, as it is little endian

        for (int i = initsegSigBytes.size(); i > 0;)
        {
            initSegSigNum *= base;
            initSegSigNum += (int)initsegSigBytes[--i];
        }
        this->initialSegSig = initSegSigNum;
}