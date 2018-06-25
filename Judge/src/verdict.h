#ifndef _VERDICT_H_
#define _VERDICT_H_

#include "defines.h"

class Verdict{
public:
    Verdict();
    Verdict(util::Message InitMessage, float Time, int MemoryKb);

    util::Message GetMessage();
    float GetTime();
    int GetMemory();

private:
    util::Message m_message;
    float m_time;
    int m_memoryKb;
};


#endif
