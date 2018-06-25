#ifndef _UTIL_H_
#define _UTIL_H_

#include "defines.h"

namespace util{
    enum class Verdict{
        OK,
        WA,
        TLE,
        KBS
    };

    int CompareFiles(std::string FirstFilePath, std::string SecondFilePath);

    void SleepInMilliseconds(int Milliseconds);
}

#endif

