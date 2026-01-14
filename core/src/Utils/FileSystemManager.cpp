#include "../../include/Utils/FileSystemManager.h"

std::string FileSystemManager::getFile()
{
    char buffer[128];

    FILE* pipe = popen("zenity --file-selection --title='Select file'", "r");
    if (!pipe) return "";

    std::string result = "";
    while (fgets(buffer, sizeof(buffer), pipe) != NULL)
        result += buffer;

    pclose(pipe);

    if (!result.empty() && result.back() == '\n')
        result.pop_back();
    
    return result;
}

std::string FileSystemManager::getFolder()
{
    char buffer[128];

    FILE* pipe = popen("zenity --file-selection --directory --title='Select folder'", "r");
    if (!pipe) return "";

    std::string result = "";
    while (fgets(buffer, sizeof(buffer), pipe) != NULL)
        result += buffer;

    pclose(pipe);

    if (!result.empty() && result.back() == '\n')
        result.pop_back();

    return result;
}