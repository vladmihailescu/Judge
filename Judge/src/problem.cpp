#include "problem.h"

Problem::Problem(std::string InDirPath, std::string OutDirPath, std::string Name, int NrTests, int TestPoints, float TimeLimit)
:   m_inDirPath { InDirPath },
    m_okDirPath { OutDirPath },
    m_name { Name },
    m_nrTests { NrTests },
    m_testPoints { TestPoints },
    m_secondsTimeLimit { TimeLimit }
{
}

std::string Problem::GetInDirPath(){
    return this->m_inDirPath;
}

std::string Problem::GetOkDirPath(){
    return this->m_okDirPath;
}

std::string Problem::GetName(){
    return this->m_name;
}

int Problem::GetNumberOfTests(){
    return this->m_nrTests;
}

int Problem::GetTestPoints(){
    return this->m_testPoints;
}

float Problem::GetTimeLimit(){
    return this->m_secondsTimeLimit;
}
