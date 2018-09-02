#ifndef DIRFILE_H
#define DIRFILE_H

#include <string>
#include <experimental/filesystem>

namespace fs = std::experimental::filesystem;

class dirFile
{
    public:
        fs::directory_entry dirEntry;
        int extensionType;
        std::string path;

        dirFile(fs::directory_entry dirEntry, int extensionType, std::string path);
        ~dirFile();
    
    private:

};

#endif // DIRFILE_H