#include "aboutlck.h"
Aboutmutex::Aboutmutex():i(0)
{

}
Aboutmutex::~Aboutmutex()
{

}
void Aboutmutex::print1()
{
    std::unique_lock<mutex> lock(lck1);
    for (i = 0; i < 10; i++)
    {
        cout << "i : " << i << endl;
    }

}
void Aboutmutex::print2()
{
    std::unique_lock<mutex> lock(lck1);
    for (i = 0; i < 10; i++)
    {
        cout << "i : " << i << endl;
    }
}

AboutRecursive_mutex::AboutRecursive_mutex(int num):n(num)
{

}
AboutRecursive_mutex::~AboutRecursive_mutex()
{

}
void AboutRecursive_mutex::Factorial()
{
    std::unique_lock<recursive_mutex> lck(lck2);
    if (n == 1)
    {
        cout << " n is:" << n << endl;
        return;
    }
    cout << " n is :" << n << endl;
    n--;
    Factorial();

}
AboutRecursive_timed_mutex::AboutRecursive_timed_mutex(int num,int time):n(num),timeout(time)
{

}
AboutRecursive_timed_mutex::~AboutRecursive_timed_mutex()
{

}
void AboutRecursive_timed_mutex::Decline()
{
    if (n == 1)
    {
        cout << "AboutRecursive_timed_mutex::n is " << n << endl;
        return;
    }
    std::chrono::milliseconds time(timeout);
    if (lck3.try_lock_until(chrono::steady_clock::now() + time))
    {
        cout << " AboutRecursive_timed_mutex::n  is " << n << endl;
        n--;
        Decline();
        lck3.unlock();
    }
    else
    {
        std::this_thread::sleep_for(chrono::milliseconds(10));
        cout << " wait for 10 milliseconds " << endl;
    }
}
AboutTimed_mutex::AboutTimed_mutex(int num,int time):n(num),timeout(time)
{

}
void AboutTimed_mutex::testTimedout()
{
    std::chrono::milliseconds time(timeout);
    if (lck4.try_lock_until(chrono::steady_clock::now() + time))
    {
        cout << " n is : " << n << endl;
        n--;
        lck4.unlock();
    }
    else
    {
        cout << "testTimeout wait for 1 second" << endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}
void AboutTimed_mutex::print3()
{
    std::chrono::microseconds time(timeout);
    if (lck4.try_lock_until(chrono::steady_clock::now() + time))
    {
        cout << " n is : " << n << endl;
        n--;
        lck4.unlock();
    }
    else
    {
        cout << "print3 wait for 1 second" << endl;

        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}
AboutTimed_mutex::~AboutTimed_mutex()
{

}

