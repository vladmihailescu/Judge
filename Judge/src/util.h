#ifndef _UTIL_H_
#define _UTIL_H_

#include "string"
#include "fstream"
#include "thread"

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

