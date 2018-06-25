#include "problem.h"
#include "contestant.h"
#include "defines.h"

int main(){
    std::string problemName = "";
    float timeLimit = 0.0;
    int testCases = 0;
    int testPoints = 0;

    std::cout << "Problem nameee: ";
    std::cin >> problemName;
    std::cout << "Time limit: ";
    std::cin >> timeLimit;
    std::cout << "Number of test cases: ";
    std::cin >> testCases;
    std::cout << "Points per test case: ";
    std::cin >> testPoints;

    Problem ghiozdan{"in","out",problemName,testCases,testPoints,timeLimit};

    Contestant a{"axinteteodor.cpp"};
    a.JudgeProblem(ghiozdan);
    a.AppendScoreToFile("results.txt", ghiozdan);

    Contestant b{"burdescualexandru.cpp"};
    b.JudgeProblem(ghiozdan);
    b.AppendScoreToFile("results.txt", ghiozdan);

    Contestant c{"madarasalexandra.cpp"};
    c.JudgeProblem(ghiozdan);
    c.AppendScoreToFile("results.txt", ghiozdan);

    Contestant d{"moldoveanvlad.cpp"};
    d.JudgeProblem(ghiozdan);
    d.AppendScoreToFile("results.txt", ghiozdan);

    Contestant e{"netarazvan.cpp"};
    e.JudgeProblem(ghiozdan);
    e.AppendScoreToFile("results.txt", ghiozdan);

    Contestant f{"sarandiandrei.cpp"};
    f.JudgeProblem(ghiozdan);
    f.AppendScoreToFile("results.txt", ghiozdan);
    return 0;
}
