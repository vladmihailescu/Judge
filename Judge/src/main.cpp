#include "util.h"
#include "problem.h"
#include "contestant.h"

#include "windows.h"
#include "string"
#include "thread"
#include "iostream"
#include "fstream"

int main(){

    std::string problemName = "";
    float timeLimit = 0.0;
    int testCases = 0;
    int testPoints = 0;

    std::cout << "Problem name: ";
    std::cin >> problemName;
    std::cout << "Time limit: ";
    std::cin >> timeLimit;
    std::cout << "Number of test cases: ";
    std::cin >> testCases;
    std::cout << "Points per test case: ";
    std::cin >> testPoints;

    Problem ghiozdan{"in","out",problemName,testCases,testPoints,timeLimit};

    Contestant a{"sursa1"};
    a.JudgeProblem(ghiozdan);
    a.AppendScoreToFile("results.txt", ghiozdan);

    Contestant b{"sursa2"};
    b.JudgeProblem(ghiozdan);
    b.AppendScoreToFile("results.txt", ghiozdan);

    Contestant c{"sursa1"};
    c.JudgeProblem(ghiozdan);
    c.AppendScoreToFile("results.txt", ghiozdan);
    return 0;
}
