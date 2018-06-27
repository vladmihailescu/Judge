#include "localdirectory.h"

LocalDirectory::LocalDirectory()
:   m_path { "" }
{
    char aux[MAX_PATH] = {0};
    GetCurrentDirectory(MAX_PATH, aux);
    m_path = aux;
}

std::string LocalDirectory::GetPath(){
    return m_path;
}
std::vector<std::string> LocalDirectory::GetSources(){
    WIN32_FIND_DATA ffd;
    HANDLE fileHandle;
    std::vector<std::string> files;
    std::string newPath = m_path + "\\*";

    fileHandle = FindFirstFile(newPath.c_str(), &ffd);
    if(INVALID_HANDLE_VALUE == fileHandle){
        return files;
    }

    do{
        if(!(FILE_ATTRIBUTE_DIRECTORY & ffd.dwFileAttributes)){
            files.push_back(ffd.cFileName);
        }
    }while(FindNextFile(fileHandle, &ffd));

    return files;
}

