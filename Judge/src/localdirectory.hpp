#ifndef _LOCALDIRECTORY_H_
#define _LOCALDIRECTORY_H_

#include "windows.h"

namespace judge{
class LocalDirectory{
public:
    LocalDirectory()
    :   path_ { "" } {
        char aux[MAX_PATH] = {0};
        GetCurrentDirectory(MAX_PATH, aux);
        path_ = aux;
    }
    std::string GetPath(){
        return this->path_;
    }
    static std::vector<std::string> GetSourcesLocalDir(){
        char aux[MAX_PATH] = {0};
        GetCurrentDirectory(MAX_PATH, aux);
        std::string path = aux;

        //searches the current directory
        WIN32_FIND_DATA ffd;
        std::string new_path = path + "\\*";
        std::vector<std::string> files;
        HANDLE file_handle = FindFirstFile(new_path.c_str(), &ffd);
        if(INVALID_HANDLE_VALUE == file_handle){
            return files;
        }
        do{
            if(!(FILE_ATTRIBUTE_DIRECTORY & ffd.dwFileAttributes)){
                files.push_back(ffd.cFileName);
            }
        }while(FindNextFile(file_handle, &ffd));

        return files;
    }

private:
    std::string path_;

};
}

#endif
