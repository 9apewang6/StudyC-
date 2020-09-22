#pragma once
#include "publicdef.h"
using namespace std;
void t1()
{
    cout << "t1" << endl;
}
void t2()
{
    cout << "t2" << endl;
}
void testt1()
{
    std::thread t_1(t1);
    std::thread t_2(t2);
    std::thread::id id1 = t_1.get_id();
    cout << " id1 is " << id1 << endl;
    std::thread::id id2 = t_2.get_id();
    cout << "id2 is " << id2 << endl;
    std::thread::id id3 =  std::this_thread::get_id();
    cout << "id3 is" << id3 << endl;

    t_1.join(); // �ڲ������� joinable
    t_2.join();


}
