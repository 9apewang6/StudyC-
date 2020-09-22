#pragma once
#include "publicdef.h"
class AboutConditionalVariable
{
public:
    AboutConditionalVariable();
    ~AboutConditionalVariable();
    void r1();
    void r2();
private:
    std::mutex mymutex;
    std::condition_variable cve;
    bool ready = false;
};