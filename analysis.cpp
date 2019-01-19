#include "analysis.h"
#include <iostream>
#include <fstream>

Analysis::Analysis(std::string fp, int segmentSize, int unit)
{
    this->validSelection = true;
    this->errorString = "No errors found.";

    identifyPlatform();
    // Validate user selection
    fileAnalysis(fp.c_str(), segmentSize, unit);
}

Analysis::~Analysis(){}

void Analysis::fileAnalysis(const char* filePath, int segmentSize, int unitSize)
{
    std::streampos fsize = 0;
    std::ifstream f(filePath);
    long long segSize = 0;

    if(!f.good())
    {
        this->validSelection = false;
        this->errorString = "File is invalid.";
    }

    else
    {
        std::ifstream file( filePath, std::ios::binary );
        fsize = file.tellg();
        file.seekg( 0, std::ios::end );
        fsize = file.tellg() - fsize;
        this->fileSize = fsize;
        file.close();
    }

    std::cout << unitSize << std::endl;
    switch (unitSize)
    {
    case 0:
        // bytes
        segSize = segmentSize;
        break;
    case 1:
        // KB
        segSize = segmentSize * 1000;
        break;
    case 2:
        // MB
        segSize = segmentSize * 10000;
        break;
    case 3:
        // GB
        segSize = segmentSize * 100000;
        break;
    case 4:
        // TB
        segSize = segmentSize * 1000000;
    default:
        segSize = 1;
    }

    std::cout << segSize << "vs" << fsize << std::endl;


    if(segSize > fsize)
    {   

        this->validSelection = false;
        this->errorString = "Segment size selected is larger than the selected file size. \nSelected segment size: "
                            + std::to_string(segSize) + " bytes.\nSelected file size: " + std::to_string(this->fileSize) + " bytes.";
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
