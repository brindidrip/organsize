#ifndef ORGANSIZE_H
#define ORGANSIZE_H

#include <string>

class Organsize
{
    public:
        Organsize(std::string path, int);
        ~Organsize();
        enum extensionType{DOC};
        void extensionSort(std::string path);
    
    private:

};

#endif // ORGANSIZE_H