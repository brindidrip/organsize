#include "dirFile.h"
#include <iostream>

dirFile::dirFile(fs::directory_entry dirEntry, int extensionType, std::string path) : dirEntry(dirEntry), extensionType(extensionType), path(path){}

dirFile::~dirFile(){}