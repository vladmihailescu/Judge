#include "contestant.h"

Contestant::Contestant(std::string sourceName){
    m_score.clear();
    m_sourceName = "";
    m_sourceExtension = "";
    m_totalScore = 0;
    int ext = 0;

    for(int i = 0; i < sourceName.size(); ++i){
        if(sourceName[i] == '.'){
            ext = 1;
        }
        if(1 == ext){
            m_sourceExtension += sourceName[i];
        }else{
            m_sourceName += sourceName[i];
        }
    }
}

void Contestant::JudgeProblem(Problem CurrentProblem){
    std::string inFile;
    std::string okFile;
    std::string exeFile = m_sourceName + "Exec";
    std::string cmd;

    cmd = "g++ " + m_sourceName + m_sourceExtension + " -o " + exeFile;
    system(cmd.c_str());

    for(int i = 1; i <= CurrentProblem.GetNumberOfTests(); ++i){
        inFile = CurrentProblem.GetInDirPath() + "\\" + std::to_string(i) + "-" + CurrentProblem.GetName() + ".in";
        okFile = CurrentProblem.GetOkDirPath() + "\\" + std::to_string(i) + "-" + CurrentProblem.GetName() + ".ok";

        CopyFileLocal(inFile, CurrentProblem.GetName() + ".in");
        CopyFileLocal(okFile, CurrentProblem.GetName() + ".ok");
        Verdict testVerdict = RunSource(CurrentProblem);
        DeleteFileLocal(CurrentProblem.GetName() + ".in");
        DeleteFileLocal(CurrentProblem.GetName() + ".ok");

        m_score[i] = testVerdict;
        if(testVerdict.GetMessage() == util::Message::OK){
            m_totalScore += CurrentProblem.GetTestPoints();
        }
    }

    cmd = "del " + m_sourceName + "Exec" + ".exe";
    system(cmd.c_str());
}
void Contestant::AppendScoreToFile(std::string FileName, Problem CurrentProblem){
    FILE *f = fopen(FileName.c_str(),"a");

    fprintf(f,"\n---Contestant: %s, Problem: %s\n", m_sourceName.c_str(), CurrentProblem.GetName().c_str());
    for(auto i : m_score){
        std::string judge;
        if(i.second.GetMessage() == util::Message::OK)
            judge = "OK";
        if(i.second.GetMessage() == util::Message::TLE)
            judge = "TLE";
        if(i.second.GetMessage() == util::Message::WA)
            judge = "WA";
        if(i.second.GetMessage() == util::Message::KBS)
            judge = "KBS";
        fprintf(f, "Test %3d, Time %2.2f, Memory %5d, Verdict %5s \n", i.first, i.second.GetTime(), i.second.GetMemory(), judge.c_str());
    }
    fprintf(f,"---Contestant \"%s\" score for problem \"%s\" is : %d \n",
              m_sourceName.c_str(), CurrentProblem.GetName().c_str(), m_totalScore);
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

Verdict Contestant::RunSource(Problem CurrentProblem){
    std::string exeFile = m_sourceName + "Exec";
    std::string cmd = "";
    bool status = 0;
    bool tle = 1;
    util::Message verdict = util::Message::OK;
    float timeLimitInSeconds = CurrentProblem.GetTimeLimit();
    int timeLimitInMilliseconds = (int)((float)timeLimitInSeconds * (float)1000);
    int timeElapsedInMilliseconds = 0;
    int timeLapseInMilliseconds = 10;
    DWORD processExitCode = 0;
    PROCESS_INFORMATION pi { 0 };
    STARTUPINFO si { 0 };
    bool killProcess = 0;
    int memoryUsed = 0;
    PROCESS_MEMORY_COUNTERS memoryMap;

    cmd = exeFile + ".exe";

    status = CreateProcess(NULL, (LPTSTR)cmd.c_str(), NULL, NULL, TRUE, 0, NULL,
                           NULL, &si, &pi);

    if(0 == status){
        verdict = util::Message::KBS;
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
            verdict = util::Message::KBS;
            goto CleanUp;
        }
        if(STILL_ACTIVE != processExitCode){
            tle = 0;
            break;
        }

        status = GetProcessMemoryInfo(
            pi.hProcess,
            &memoryMap,
            sizeof(memoryMap)
        );
        if(0 == status){
            continue;
        }
        memoryUsed = std::max(memoryUsed, (int)memoryMap.PeakWorkingSetSize + (int)memoryMap.WorkingSetSize +
                                     (int)memoryMap.QuotaPeakPagedPoolUsage +
                                     (int)memoryMap.QuotaPagedPoolUsage + (int)memoryMap.QuotaPeakNonPagedPoolUsage +
                                     (int)memoryMap.QuotaNonPagedPoolUsage +
                                     (int)memoryMap.PagefileUsage + (int)memoryMap.PeakPagefileUsage);
    }

    if(1 == tle){
        status = TerminateProcess(
            pi.hProcess,
            0
        );
        killProcess = 0;
        if(0 == status){
            goto CleanUp;
        }
        killProcess = 0;
    }

    verdict = util::Message::OK;

    if(1 == tle){
        verdict = util::Message::TLE;
    }
    if(util::Message::OK == verdict && 0 == util::CompareFiles(CurrentProblem.GetName() + ".ok", CurrentProblem.GetName() + ".out")){
        verdict = util::Message::WA;
    }

    CleanUp:
    if(1 == killProcess){
        TerminateProcess(pi.hProcess, 0);
    }

    cmd = "del " + CurrentProblem.GetName() + ".out";
    system(cmd.c_str());

    return {verdict, timeElapsedInMilliseconds / 1000.0, memoryUsed / 1024};
}

