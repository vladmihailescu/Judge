#include "util.h"

int util::CompareFiles(std::string FirstFilePath, std::string SecondFilePath){
    ///NRVO
    int result = 1;
    std::ifstream firstFileStream(FirstFilePath);
    std::ifstream secondFileStream(SecondFilePath);
    std::string x;
    std::string y;

    while(firstFileStream >> x){
        secondFileStream >> y;
        if(x != y){
            result = 0;
            break;
        }
    }
    while(secondFileStream >> y){
        result = 0;
        break;
    }
    firstFileStream.close();
    secondFileStream.close();
    return result;
}

void util::SleepInMilliseconds(int Milliseconds){
    std::this_thread::sleep_for(std::chrono::milliseconds(Milliseconds));
}
