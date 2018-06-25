#ifndef _CONTESTANT_H_
#define _CONTESTANT_H_

#include "defines.h"
#include "problem.h"

class Contestant{
public:
    Contestant(std::string sourceName);

    void JudgeProblem(Problem CurrentProblem);
    void AppendScoreToFile(std::string FileName, Problem CurrentProblem);

private:
    void CopyFileLocal(std::string Path, std::string Destination);
    std::pair<float, util::Verdict> RunSource(std::string ProblemName, Problem CurrentProblem);
    void DeleteFileLocal(std::string Path);

    std::string m_sourceName;
    std::map<int, std::pair<float, util::Verdict> > m_score;
    int m_integerScore;
};

#endif
