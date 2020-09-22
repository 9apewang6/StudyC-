#include "AboutConditionalvariable.h"
AboutConditionalVariable::AboutConditionalVariable()
{

}
AboutConditionalVariable::~AboutConditionalVariable()
{

}
void AboutConditionalVariable::r1()
{
    std::unique_lock<std::mutex> lck(mymutex);
    if (!ready)
        cve.wait(lck);
    std::cout << " About conditinoal variable r1 " << std::endl;
}
void AboutConditionalVariable::r2()
{
    std::unique_lock<std::mutex> lck(mymutex);
    ready = true;
    cve.notify_one();
}
