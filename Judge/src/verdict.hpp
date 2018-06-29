#ifndef _VERDICT_HPP
#define _VERDICT_HPP

#include "standard_util.hpp"

namespace judge{
class Verdict{
public:
    Verdict()
    :   message_ { judge::Message::KBS },
        time_ { 0.0 },
        memory_kb_ { 0 } {
    }
    Verdict(judge::Message init_message, float time, int memory_kb)
    :   message_ { init_message },
        time_ { time },
        memory_kb_ { memory_kb } {
    }
    judge::Message GetMessageAA(){
        return this->message_;
    }
    float GetTime(){
        return this->time_;
    }
    int GetMemory(){
        return this->memory_kb_;
    }

private:
    judge::Message message_;
    float time_;
    int memory_kb_;

};
}

#endif
