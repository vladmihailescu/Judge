#include "judge.hpp"

int main(){
    char problem_name[MAX_PATH];
    float time_limit = 0.0;
    int test_cases = 0;
    int test_points = 0;
    printf("<--Judge system-->\n");
    printf("Problem name: \n");
    scanf("%s",problem_name);
    printf("Time limit: \n");
    scanf("%f",&time_limit);
    printf("Number of test cases: \n");
    scanf("%d",&test_cases);
    printf("Points per test case: \n");
    scanf("%d",&test_points);

    judge::Problem problem{"in","out",problem_name,test_cases,test_points,time_limit};
    std::vector<std::string> files = judge::LocalDirectory::GetSourcesLocalDir();
    for(auto i : files){
        judge::Contestant current_contestant{i};
        if(".cpp" == current_contestant.GetSourceExtension() || ".c" == current_contestant.GetSourceExtension()){
            current_contestant.JudgeProblem(problem);
            current_contestant.AppendScoreToFile("results.txt", problem);
        }
    }
    return 0;
}


