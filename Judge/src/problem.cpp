#include "problem.h"

Problem::Problem(
    std::string InDirPath,
    std::string OkDirPath,
    std::string Name,
    int NrTests,
    int TestPoints,
    float TimeLimit
)
{
    m_inDirPath = InDirPath;
    m_okDirPath = OkDirPath;
    m_name = Name;
    m_nrTests = NrTests;
    m_testPoints = TestPoints;
    m_secondsTimeLimit = TimeLimit;
}

const std::string& Problem::GetInDirPath(){
    return this->m_inDirPath;
}

const std::string& Problem::GetOkDirPath(){
    return this->m_okDirPath;
}

const std::string& Problem::GetName(){
    return this->m_name;
}

const int& Problem::GetNumberOfTests(){
    return this->m_nrTests;
}

const int& Problem::GetTestPoints(){
    return this->m_testPoints;
}

const float& Problem::GetTimeLimit(){
    return this->m_secondsTimeLimit;
}
