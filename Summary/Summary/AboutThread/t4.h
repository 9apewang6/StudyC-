#pragma once
#include "publicdef.h"
using namespace std;
list<int> datalist;
std::mutex lck;

void producer(int num)
{
    lck.lock();
    datalist.push_back(num);
    lck.unlock();
}

void cosumer()
{
    lck.lock();
    if (datalist.size() == 0)
    {
        lck.unlock();
        return;
    }
    cout << " consumer 1 " << datalist.back() << endl;
    datalist.pop_back();
    lck.unlock();
}

void consumer2()
{
    lck.lock();
    if (datalist.size() == 0)
    {
        lck.unlock();
        return;
    }
    cout << " consumer 2" << datalist.back() << endl;
    datalist.pop_back();
    lck.unlock();
}


void testt4()
{
    srand((unsigned int)time(NULL));
    std::thread produ(producer,10);
    std::thread con1(cosumer);
    std::thread con2(consumer2);


    std::this_thread::sleep_for(std::chrono::seconds(3));
    produ.join();
    con1.join();
    con2.join();



    cout << datalist.size() << endl;

}