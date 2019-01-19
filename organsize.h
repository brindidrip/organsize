#ifndef ORGANSIZE_H
#define ORGANSIZE_H

#include <dirFile.h>
#include <string>

class Organsize
{
    public:
        std::vector<dirFile> dirFiles;
        Organsize( std::string file, std::string dirPath, int );
        ~Organsize();
        void reconstructFile( const char* directoryPath );
        enum extensionType{ DOC };
    private:
        bool fileAnalysis( const char* filePath );
        void segmentFile( const char* filePath );
        std::streampos fileSize( const char* filePath );
        const char* dirPath;
        const char* mFilePath;
        int mfileSize;
        int mSegments;
        int lastSegmentSize;
        int segmentSize;
};

#endif // ORGANSIZE_H