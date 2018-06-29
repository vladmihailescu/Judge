#ifndef _CONTESTANT_HPP_
#define _CONTESTANT_HPP_

#include "windows.h"
#include "Psapi.h"

#include "string"
#include "map"
#include "vector"

#include "problem.hpp"
#include "verdict.hpp"

namespace judge{
class Contestant{
public:
    Contestant(std::string source_name)
    :   source_name_ { "" },
        source_extension_ { "" },
        score_ { },
        total_score_ { 0 }
    {
        //split name.extension
        int dot = 0;
        for(int i = 0; i < source_name.size(); ++i){
            if('.' == source_name[i])
                dot = 1;
            if(1 == dot)
                source_extension_ += source_name[i];
            else
                source_name_ += source_name[i];
        }
    }
    void JudgeProblem(judge::Problem current_problem){
        //create .exe file
        std::string exe_file = source_name_ + "Exec";
        std::string cmd = "";
        if(source_extension_ == ".cpp")
            cmd = "g++ -std=c++1y " + source_name_ + source_extension_ + " -o " + exe_file;
        if(source_extension_ == ".c")
            cmd = "gcc -std=c99 " + source_name_ + source_extension_ + " -o " + exe_file;
        system(cmd.c_str());

        //run .exe for all tests
        for(int i = 1; i <= current_problem.GetNumberOfTests(); ++i){
            std::string in_file = current_problem.GetInDirPath() + "\\" + std::to_string(i) + "-" + current_problem.GetName() + ".in";
            std::string ok_file = current_problem.GetOkDirPath() + "\\" + std::to_string(i) + "-" + current_problem.GetName() + ".ok";
            CopyFileLocal(in_file, current_problem.GetName() + ".in");
            CopyFileLocal(ok_file, current_problem.GetName() + ".ok");
            judge::Verdict test_verdict = RunSource(current_problem);
            DeleteFileLocal(current_problem.GetName() + ".in");
            DeleteFileLocal(current_problem.GetName() + ".ok");
            score_[i] = test_verdict;
            if(judge::Message::OK == test_verdict.GetMessageAA())
                total_score_ += current_problem.GetTestPoints();
        }

        //delete the .exe file
        cmd = "del " + source_name_ + "Exec" + ".exe";
        system(cmd.c_str());
    }
    void AppendScoreToFile(std::string file_name, judge::Problem current_problem){
        FILE *f = fopen(file_name.c_str(),"a");
        fprintf(f,"\n---Contestant: %s, Problem: %s\n", source_name_.c_str(), current_problem.GetName().c_str());
        for(auto i : score_){
            std::string judge_message;
            if(i.second.GetMessageAA() == judge::Message::OK)
                judge_message = "OK";
            if(i.second.GetMessageAA() == judge::Message::TLE)
                judge_message = "TLE";
            if(i.second.GetMessageAA() == judge::Message::WA)
                judge_message = "WA";
            if(i.second.GetMessageAA() == judge::Message::KBS)
                judge_message = "KBS";
            fprintf(f, "Test %3d, Time %2.2f, Memory %5d, Verdict %5s \n", i.first, i.second.GetTime(), i.second.GetMemory(), judge_message.c_str());
        }
        fprintf(f,"---Contestant \"%s\" score for problem \"%s\" is : %d \n",
                  source_name_.c_str(), current_problem.GetName().c_str(), total_score_);
        fclose(f);
    }
    std::string GetSourceExtension(){
        return this->source_extension_;
    }

private:
    void CopyFileLocal(std::string path, std::string destination){
        std::string cmd = "";
        cmd = "copy " + path + " " + destination;
        system(cmd.c_str());
    }
    judge::Verdict RunSource(judge::Problem current_problem){
        judge::Message result = judge::Message::OK;
        bool tle = 1;
        bool kill_process = 0;
        bool done = 0;

        //run the .exe file
        PROCESS_INFORMATION process_info { 0 };
        STARTUPINFO startup_info { 0 };
        std::string cmd = source_name_ + "Exec" + ".exe";
        bool status = CreateProcess(NULL, (LPTSTR)cmd.c_str(), NULL, NULL, TRUE, 0, NULL,
                                    NULL, &startup_info, &process_info);
        if(0 == status){
            result = judge::Message::KBS;
            done = 1;
        }
        kill_process = 1;

        //manage the running process
        int memory_used = 0;
        int time_limit_in_milliseconds = (int)((float)current_problem.GetTimeLimit() * (float)1000);
        int time_elapsed_in_milliseconds = 0;
        int time_lapse_in_milliseconds = 1;
        while(time_elapsed_in_milliseconds < time_limit_in_milliseconds && !done){
            judge::SleepInMilliseconds(time_lapse_in_milliseconds);
            time_elapsed_in_milliseconds += time_lapse_in_milliseconds;

            //check if the process is still running
            DWORD process_exit_code = 0;
            status = GetExitCodeProcess(process_info.hProcess,&process_exit_code);
            if(0 == status){
                result = judge::Message::KBS;
                done = 1;
            }
            if(STILL_ACTIVE != process_exit_code){
                tle = 0;
                break;
            }

            //checks memory used
            PROCESS_MEMORY_COUNTERS memory_map;
            status = GetProcessMemoryInfo(process_info.hProcess,&memory_map,sizeof(memory_map));
            if(0 == status)
                continue;
            memory_used = std::max(memory_used, (int)memory_map.WorkingSetSize);
        }

        //check if tle
        if(!done && 1 == tle){
            result = judge::Message::TLE;
            TerminateProcess(process_info.hProcess,0);
            kill_process = 0;
        }

        //check if output is correct
        if(!done && judge::Message::OK == result && 0 == judge::CompareFiles(current_problem.GetName() + ".ok", current_problem.GetName() + ".out"))
            result = judge::Message::WA;

        if(1 == kill_process)
            TerminateProcess(process_info.hProcess, 0);
        cmd = "del " + current_problem.GetName() + ".out";
        system(cmd.c_str());

        return {result, time_elapsed_in_milliseconds / 1000.0, memory_used / 1024};
    }
    void DeleteFileLocal(std::string path){
        std::string cmd = "";
        cmd = "del " + path;
        system(cmd.c_str());
    }
    std::string source_name_;
    std::string source_extension_;
    std::map<int, Verdict> score_;
    int total_score_;

};
}

#endif
