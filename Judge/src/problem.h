#ifndef _PROBLEM_H_
#define _PROBLEM_H_

#include "defines.h"

class Problem{
public:
    Problem(
        std::string InDirPath,
        std::string OutDirPath,
        std::string Name,
        int NrTests,
        int TestPoints,
        float TimeLimit
    );

    std::string GetInDirPath();
    std::string GetOkDirPath();
    std::string GetName();
    int GetNumberOfTests();
    int GetTestPoints();
    float GetTimeLimit();

private:
    std::string m_inDirPath;
    std::string m_okDirPath;
    std::string m_name;
    int m_nrTests;
    int m_testPoints;
    float m_secondsTimeLimit;
};

#endif

