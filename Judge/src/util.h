#ifndef _UTIL_H_
#define _UTIL_H_

#include "defines.h"

namespace util{
    enum class Message{
        OK,
        WA,
        TLE,
        KBS,
        MLE
    };

    int CompareFiles(std::string FirstFilePath, std::string SecondFilePath);
    void SleepInMilliseconds(int Milliseconds);
}

#endif

