#ifndef ANALYSIS_H
#define ANALYSIS_H

class Analysis
{
    public:
        Analysis(int);
        ~Analysis();
        enum platform{WIN32, WIN64, APPLE, LINUX, UNIX, POSIX};
        int machine_platform;
    
    private:

};

#endif // ANALYSIS_H