#include "judge.hpp"

int main(){
    char problemName[MAX_PATH];
    float timeLimit = 0.0;
    int testCases = 0;
    int testPoints = 0;
    printf("<--Judge system-->\n");
    printf("Problem name: \n");
    scanf("%s",problemName);
    printf("Time limit: \n");
    scanf("%f",&timeLimit);
    printf("Number of test cases: \n");
    scanf("%d",&testCases);
    printf("Points per test case: \n");
    scanf("%d",&testPoints);

    judge::Problem problem{"in","out",problemName,testCases,testPoints,timeLimit};
    std::vector<std::string> t = judge::LocalDirectory::GetSourcesLocalDir();
    for(auto i : t){
        judge::Contestant currentContestant{i};
        if(".cpp" == currentContestant.GetSourceExtension() || ".c" == currentContestant.GetSourceExtension()){
            currentContestant.JudgeProblem(problem);
            currentContestant.AppendScoreToFile("results.txt", problem);
        }
    }
    return 0;
}


