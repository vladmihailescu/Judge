#ifndef _LOCALDIRECTORY_H_
#define _LOCALDIRECTORY_H_

#include "defines.h"

class LocalDirectory{
public:
    LocalDirectory();

    std::string GetPath();
    std::vector<std::string> GetSources();

private:
    std::string m_path;

};

#endif
