#include "t1.h"
//#include "t2.h"
//#include "t3.h"
#include "t4.h"
#include "aboutlck.h"
#include "AboutConditionalvariable.h"
void main()
{
    Aboutmutex testmutex1;
    std::thread  thread1(std::bind(&Aboutmutex::print1,&testmutex1));
    std::thread thread2(std::bind(&Aboutmutex::print2,&testmutex1));

    std::thread thread1_1;
    thread1_1.swap(thread1);
    thread1.native_handle(); 

    if(thread1.joinable())thread1.join();
    if(thread2.joinable())thread2.join();
    if (thread1_1.joinable())thread1_1.join();


    AboutRecursive_mutex testmutex2(15);
    std::thread thread3(std::bind(&AboutRecursive_mutex::Factorial,&testmutex2));
    thread3.join();


    AboutRecursive_timed_mutex testmutex3(23,10);
    std::thread thread6(std::bind(&AboutRecursive_timed_mutex::Decline,&testmutex3));
    thread6.join();

    AboutTimed_mutex testmutex4(23, 10);
    std::thread thread4(std::bind(&AboutTimed_mutex::testTimedout,&testmutex4));
    std::thread thread5(std::bind(&AboutTimed_mutex::print3,&testmutex4));
    thread4.join();
    thread5.join();


    AboutConditionalVariable testcv;
    std::thread thread7(std::bind(&AboutConditionalVariable::r1,&testcv));

    testcv.r2();

    if(thread7.joinable())thread7.join();
    
    system("pause");
}