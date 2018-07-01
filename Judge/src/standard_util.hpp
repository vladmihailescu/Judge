#ifndef _STANDARD_UTIL_HPP_
#define _STANDARD_UTIL_HPP_

#include "string"
#include "fstream"
#include "thread"

namespace judge{
enum class Message{
    OK = 0,
    WA,     //Wrong answer
    TLE,    //Time limit exceeded
    KBS,    //Killed by signal
    MLE,    //Memory limit exceeded
    CE      //Compilation error
};
int CompareFiles(std::string first_file_path, std::string second_file_path){
    int result = 1;
    std::ifstream first_file_stream(first_file_path);
    std::ifstream second_file_stream(second_file_path);
    std::string x;
    std::string y;
    while(first_file_stream >> x){
        second_file_stream >> y;
        if(x != y){
            result = 0;
            break;
        }
    }
    while(second_file_stream >> y){
        result = 0;
        break;
    }
    first_file_stream.close();
    second_file_stream.close();
    return result;
}
inline void SleepInMilliseconds(int milliseconds){
    std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
}
}

#endif
