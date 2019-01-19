#ifndef ORGANSIZE_H
#define ORGANSIZE_H

#include <dirFile.h>
#include <string>

class Organsize
{
    public:
        // constructor:
        Organsize( std::string file, std::string dirPath, long long fileSize, long long segments, long long selectedSegmentSize, long long remainderSS, long long totalSegs );
        ~Organsize();

        // data members:
        std::vector<dirFile> dirFiles;
        enum extensionType{ DOC };
        const char* mFilePath;
        const char* dirPath;
        long long mFileSize;
        long long mSegments;
        long long mSegSize;
        long long mRemainderSegSize;
        long long mTotalSegments;

        // member functions:
        void reconstructFile( const char* directoryPath );
        void segmentFile( const char* filePath );

    private:
    
};

#endif // ORGANSIZE_H