#ifndef ANALYSIS_H
#define ANALYSIS_H

#include <iostream>

class Analysis
{
    public:
        // constructor:
        Analysis(std::string filepath, int segmentSize, int unitSize);
        ~Analysis();

        // data members:
        enum platform{ WIN32, WIN64, APPLE, LINUX, UNIX, POSIX, ERROR };
        enum fileUnits { byte, KB, MB, GB, TB};
        platform machinePlatform;
        bool validSelection;
        int mFileSize;
        int mSegments;
        int mSegSize;
        int mTotalSegments;
        int mRemainderSegSize;
        std::string errorString;

        // member functions:
        void identifyPlatform();
        void fileAnalysis( const char* filePath );
        void segmentAnalysis (int segmentSize, int unitSize );
    
    private:

};

#endif // ANALYSIS_H
