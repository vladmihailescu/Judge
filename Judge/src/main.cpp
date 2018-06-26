#include "problem.h"
#include "contestant.h"
#include "localdirectory.h"
#include "defines.h"

int main(){
    char problemName[MAX_PATH];
    float timeLimit = 0.0;
    int testCases = 0;
    int testPoints = 0;

    printf("Problem name: \n");
    scanf("%s",problemName);
    printf("Time limit: \n");
    scanf("%f",&timeLimit);
    printf("Number of test cases: \n");
    scanf("%d",&testCases);
    printf("Points per test case: \n");
    scanf("%d",&testPoints);

    Problem problem{"in","out",problemName,testCases,testPoints,timeLimit};

    LocalDirectory a;

    std::vector<std::string> t = a.GetSources();

    for(auto i : t){
        Contestant currentContestant{i};
        if(".cpp" == currentContestant.GetSourceExtension() || ".c" == currentContestant.GetSourceExtension()){
            currentContestant.JudgeProblem(problem);
            currentContestant.AppendScoreToFile("results.txt", problem);
        }
    }
    return 0;
}
