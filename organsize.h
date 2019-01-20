#ifndef ORGANSIZE_H
#define ORGANSIZE_H

#include <dirFile.h>
#include <string>

class Organsize
{
    public:
        // constructor:
        Organsize( std::string file, std::string fileDir, std::string dirPath, int fileSize, int segments, int selectedSegmentSize, int remainderSS, int totalSegs );
        ~Organsize();

        // data members:
        std::vector<dirFile> dirFiles;
        enum extensionType{ DOC };
        std::string mFilePath;
        std::string mFileDir;
        std::string mdirPath;
        int mFileSize;
        int mSegments;
        int mSegSize;
        int mRemainderSegSize;
        int mTotalSegments;

        // member functions:
        void reconstructFile( );
        void segmentFile( );

    private:
    
};

#endif // ORGANSIZE_H