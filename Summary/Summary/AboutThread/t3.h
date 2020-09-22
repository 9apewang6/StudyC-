#pragma once
#include "publicdef.h"
using namespace std;
list<int> datalist;
std::mutex lck;
void producer()
{
    lck.lock();
    datalist.push_back(rand() % 10 + 2);
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


void testt3()
{
    srand((unsigned int)time(NULL));
    std::thread produ(producer);
    std::thread con1(cosumer);
    std::thread con2(consumer2);


    std::this_thread::sleep_for(std::chrono::seconds(3));
    produ.detach();
    con1.detach();
    con2.detach();

    std::thread::id  id1 = produ.get_id();
    cout << " produ id is " << id1 << endl;
    std::thread::id id2 = con1.get_id();
    cout << " con1 id is" << id2 << endl;
    std::thread::id id3 = con2.get_id();
    cout << " con2  id is " << id3 << endl;
    std::thread::id id4 = std::this_thread::get_id();
    cout << " id4 is " << endl;
    try {
        produ.join();
    }
    catch (system_error e)
    {
        cout << e.what() << endl; // invalid argument
        exit(1);
    }
//     try {
// 
// 
//         con1.join();
//     }
//     catch()
//     con2.join();
    cout << datalist.size() << endl;

}