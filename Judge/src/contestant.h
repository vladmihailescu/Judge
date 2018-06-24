#ifndef _CONTESTANT_H_
#define _CONTESTANT_H_

#include "string"
#include "map"
#include "problem.h"
#include "util.h"
#include "utility"

class Contestant{
public:
    void JudgeProblem(Problem CurrentProblem);
    void PrintScore();
    void AppendScoreToFile(std::string FileName, Problem CurrentProblem);

    Contestant(std::string sourceName);
private:
    void CopyFileLocal(std::string Path, std::string Destination);
    std::pair<float, util::Verdict> RunSource(std::string ProblemName, Problem CurrentProblem);
    void DeleteFileLocal(std::string Path);

    std::string m_sourceName;
    std::map<int, std::pair<float, util::Verdict> > m_score;
    int m_integerScore;
};

#endif
