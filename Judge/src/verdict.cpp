#include "verdict.h"

Verdict::Verdict()
:   m_message { util::Message::KBS },
    m_time { 0.0 },
    m_memoryKb { 0 }
{
}

Verdict::Verdict(util::Message InitMessage, float Time, int MemoryKb)
:   m_message { InitMessage },
    m_time { Time },
    m_memoryKb { MemoryKb }
{
}

util::Message Verdict::GetMessage(){
    return this->m_message;
}
float Verdict::GetTime(){
    return this->m_time;
}
int Verdict::GetMemory(){
    return this->m_memoryKb;
}
