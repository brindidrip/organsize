#include "analysis.h"
#include <iostream>
#include <fstream>

Analysis::Analysis(std::string fp, int segmentSize, int unit)
{
    this->validSelection = true;
    this->errorString = "No errors found.";

    identifyPlatform();
    // Validate user selection
    fileAnalysis(fp.c_str());
    segmentAnalysis(segmentSize, unit);
}

Analysis::~Analysis(){}

void Analysis::fileAnalysis(const char* filePath)
{
    std::streampos fsize = 0;
    std::ifstream f(filePath);

    if(!f.good())
    {
        this->validSelection = false;
        this->errorString = "File is invalid.";
        this->mFileSize = 0;
    }
    else
    {
        std::ifstream file( filePath, std::ios::binary );
        fsize = file.tellg();
        file.seekg( 0, std::ios::end );
        fsize = file.tellg() - fsize;
        this->mFileSize = fsize;
        file.close();
    }
    
    
}

void Analysis::segmentAnalysis(int segmentSize, int unitSize)
{

    switch (unitSize)
    {
    case 0:
        // bytes
        this->mSegSize = segmentSize;
        break;
    case 1:
        // KB
        this->mSegSize = segmentSize * 1000;
        break;
    case 2:
        // MB
        this->mSegSize = segmentSize * 1000000;
        break;
    case 3:
        // GB
        this->mSegSize = segmentSize * 1000000000;
        break;
    case 4:
        // TB
        this->mSegSize = segmentSize * 1000000000000;
    default:
        this->mSegSize = 1024;
    }

    // Initialize segment data members
    this->mSegments = (this->mFileSize / this->mSegSize);
    this->mRemainderSegSize = this->mFileSize % this->mSegSize;
    this->mTotalSegments = this->mSegments;

    if(this->mRemainderSegSize != 0)
    {
        this->mTotalSegments++;
    }

    if(this->mSegSize > this->mFileSize)
    {   
        this->validSelection = false;
        this->errorString = "Segment size selected is larger than the selected file size. \nSelected segment size: "
                            + std::to_string(this->mSegSize) + " bytes.\nSelected file size: " + std::to_string(this->mFileSize) + " bytes.";
    }
}

void Analysis::identifyPlatform()
{
#ifdef _WIN32
   //define something for Windows (32-bit and 64-bit, this part is common)
   #ifdef _WIN64
      //define something for Windows (64-bit only)
      this->machinePlatform = WIN64;
      this->machinePlatform = WIN64;
   #else
      //define something for Windows (32-bit only)
      this->machinePlatform = WIN32;
   #endif
#elif __APPLE__
    #include "TargetConditionals.h"
    #if TARGET_IPHONE_SIMULATOR
         // iOS Simulator
    #elif TARGET_OS_IPHONE
        // iOS device
    #elif TARGET_OS_MAC
        // Other kinds of Mac OS
    #else
    #   error "Unknown Apple platform"
    #endif
#elif __linux__
    // linux
    this->machinePlatform = LINUX;
#elif __unix__ // all unices not caught above
    // Unix
    this->machinePlatform = UNIX;
#elif defined(_POSIX_VERSION)
    // POSIX
    this->machinePlatform = POSIX;
#else
    this->machinePlatform = ERROR;
#   error "Unknown compiler"
#endif
}
