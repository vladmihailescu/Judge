#ifndef _CONTESTANT_H_
#define _CONTESTANT_H_

#include "defines.h"
#include "problem.h"
#include "verdict.h"

class Contestant{
public:
    Contestant(std::string sourceName);

    void JudgeProblem(Problem CurrentProblem);
    void AppendScoreToFile(std::string FileName, Problem CurrentProblem);
    std::string GetSourceExtension();

private:
    void CopyFileLocal(std::string Path, std::string Destination);
    Verdict RunSource(Problem CurrentProblem);
    void DeleteFileLocal(std::string Path);

    std::string m_sourceName;
    std::string m_sourceExtension;
    std::map<int, Verdict> m_score;
    int m_totalScore;

};

#endif
