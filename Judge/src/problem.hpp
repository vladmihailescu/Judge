#ifndef _PROBLEM_HPP_
#define _PROBLEM_HPP_

#include "string"

namespace judge{
class Problem{
public:
    Problem(std::string in_dir_path, std::string out_dir_path, std::string name, int nr_tests, int test_points, float time_limit)
    :   in_dir_path_ { in_dir_path },
        ok_dir_path_ { out_dir_path },
        name_ { name },
        nr_tests_ { nr_tests },
        test_points_ { test_points },
        seconds_time_limit_ { time_limit } {
    }
    std::string GetInDirPath(){
        return this->in_dir_path_;
    }
    std::string GetOkDirPath(){
        return this->ok_dir_path_;
    }
    std::string GetName(){
        return this->name_;
    }
    int GetNumberOfTests(){
        return this->nr_tests_;
    }
    int GetTestPoints(){
        return this->test_points_;
    }
    float GetTimeLimit(){
        return this->seconds_time_limit_;
    }

private:
    std::string in_dir_path_;
    std::string ok_dir_path_;
    std::string name_;
    int nr_tests_;
    int test_points_;
    float seconds_time_limit_;

};
}

#endif
