#include "contestant.h"

#define GCC 0

Contestant::Contestant(std::string sourceName){
    m_score.clear();
    m_sourceName = sourceName;
}

void Contestant::JudgeProblem(Problem CurrentProblem){
    std::string inFile;
    std::string okFile;

    for(int i = 1; i <= CurrentProblem.GetNumberOfTests(); ++i){
        inFile = CurrentProblem.GetInDirPath() + "\\" + std::to_string(i) + "-" + CurrentProblem.GetName() + ".in";
        okFile = CurrentProblem.GetOkDirPath() + "\\" + std::to_string(i) + "-" + CurrentProblem.GetName() + ".ok";

        CopyFileLocal(inFile, CurrentProblem.GetName() + ".in");
        CopyFileLocal(okFile, CurrentProblem.GetName() + ".ok");
        std::pair<float, util::Verdict> verdict = RunSource(CurrentProblem.GetName(), CurrentProblem);
        DeleteFileLocal(CurrentProblem.GetName() + ".in");
        DeleteFileLocal(CurrentProblem.GetName() + ".ok");

        m_score[i] = verdict;
    }
}
void Contestant::AppendScoreToFile(std::string FileName, Problem CurrentProblem){
    FILE *f = fopen(FileName.c_str(),"a");
    int total = 0;

    fprintf(f,"\n---Contestant: %s, Problem: %s\n", m_sourceName.c_str(), CurrentProblem.GetName().c_str());
    for(auto i : m_score){
        std::string judge;
        if(i.second.second == util::Verdict::OK){
            total += CurrentProblem.GetTestPoints();
            judge = "OK";
        }
        if(i.second.second == util::Verdict::TLE)
            judge = "TLE";
        if(i.second.second == util::Verdict::WA)
            judge = "WA";
        if(i.second.second == util::Verdict::KBS)
            judge = "KBS";
        fprintf(f, "Test %3d, Time %2.2f, Verdict %5s \n", i.first, i.second.first , judge.c_str());
    }
    fprintf(f,"---Contestant \"%s\" score for problem \"%s\" is : %d \n",
              m_sourceName.c_str(), CurrentProblem.GetName().c_str(), total);
    fclose(f);
}

void Contestant::CopyFileLocal(std::string Path, std::string Destination){
    std::string cmd = "";
    cmd = "copy " + Path + " " + Destination;
    system(cmd.c_str());
}

void Contestant::DeleteFileLocal(std::string Path){
    std::string cmd = "";
    cmd = "del " + Path;
    system(cmd.c_str());
}

std::pair<float,util::Verdict> Contestant::RunSource(std::string ProblemName, Problem CurrentProblem){
    std::string exeFile = m_sourceName + "Exec";
    std::string cmd = "";
    bool status = 0;
    bool tle = 1;
    util::Verdict verdict = util::Verdict::OK;
    float timeLimitInSeconds = CurrentProblem.GetTimeLimit();
    int timeLimitInMilliseconds = (int)((float)timeLimitInSeconds * (float)1000);
    int timeElapsedInMilliseconds = 0;
    int timeLapseInMilliseconds = 10;
    DWORD processExitCode = 0;
    PROCESS_INFORMATION pi { 0 };
    STARTUPINFO si { 0 };
    bool killProcess = 0;

    #if GCC
    cmd = "gcc " + m_sourceName + ".c" + " -o " + exeFile;
    #else
    cmd = "g++ " + m_sourceName + ".cpp" + " -o " + exeFile;
    #endif

    system(cmd.c_str());
    cmd = exeFile + ".exe";
    status = CreateProcess(
        NULL,
        (LPTSTR)cmd.c_str(),
        NULL,
        NULL,
        TRUE,
        0,
        NULL,
        NULL,
        &si,
        &pi
    );
    if(0 == status){
        verdict = util::Verdict::KBS;
        goto CleanUp;
    }
    printf("CreateProcess succeded\n");
    killProcess = 1;

    while(timeElapsedInMilliseconds < timeLimitInMilliseconds){
        util::SleepInMilliseconds(timeLapseInMilliseconds);
        timeElapsedInMilliseconds += timeLapseInMilliseconds;

        status = GetExitCodeProcess(
            pi.hProcess,
            &processExitCode
        );
        if(0 == status){
            verdict = util::Verdict::KBS;
            goto CleanUp;
        }
        if(STILL_ACTIVE != processExitCode){
            tle = 0;
            break;
        }
    }

    if(1 == tle){
        status = TerminateProcess(
            pi.hProcess,
            0
        );
        if(0 == status){
            goto CleanUp;
        }
        killProcess = 0;
    }

    verdict = util::Verdict::OK;

    if(1 == tle){
        verdict = util::Verdict::TLE;
    }
    if(util::Verdict::OK == verdict && 0 == util::CompareFiles(ProblemName + ".ok", ProblemName + ".out")){
        verdict = util::Verdict::WA;
    }

    CleanUp:
    if(1 == killProcess){
        TerminateProcess(pi.hProcess, 0);
    }

    cmd = "del " + ProblemName + ".out";
    system(cmd.c_str());
    cmd = "del " + m_sourceName + "Exec" + ".exe";
    system(cmd.c_str());

    return std::make_pair(timeElapsedInMilliseconds / 1000.0, verdict);
}

