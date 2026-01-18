#include <iostream>
#include <cstdlib>
#include <string>

class FileSystemManager
{
public:
    FileSystemManager() {};
    ~FileSystemManager() {};

    static std::string getFile();
    static std::string getFolder();
};