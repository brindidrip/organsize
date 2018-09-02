#include "organsize.h"
#include "dirFile.h"
#include <iostream>
#include <experimental/filesystem>

namespace fs = std::experimental::filesystem;


Organsize::Organsize(std::string path, int tier)
{
    // Collect each file and store into container

    std::vector<dirFile> & files;

    for (auto p : fs::directory_iterator(path))
        //std::cout << p << std::endl;
        files.push_back(dirFile(p, 0, p.path().string()));
    
    for(auto t=files.begin(); t!=files.end(); ++t)
	std::cout << t->path << "\ndirEntry: " << t->dirEntry << '\n';

    extensionSort(path);
}
Organsize::~Organsize(){}


void Organsize::extensionSort(std::string path){}