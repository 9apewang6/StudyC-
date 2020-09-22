#pragma once
#include "publicdef.h"
using namespace  std;
class Aboutmutex
{
public:
    Aboutmutex();
    ~Aboutmutex() ;
    void print1();
    void print2();
private:
  //  list<int> data_;
    std::mutex lck1;
    int i;
};


class AboutRecursive_mutex
{
public:
    AboutRecursive_mutex(int num);
    ~AboutRecursive_mutex();
    void Factorial();
private:
    std::recursive_mutex lck2;
    int n;
};

class AboutRecursive_timed_mutex {
public:
    AboutRecursive_timed_mutex(int num=10,int time = 10);
    ~AboutRecursive_timed_mutex();
    void Decline();
private:
    std::recursive_timed_mutex lck3; //
    int n;
    int timeout;
};

class AboutTimed_mutex
{
public:
    AboutTimed_mutex(int num,int time = 1);

    ~AboutTimed_mutex();
    void testTimedout();
    void print3();
private:
    std::timed_mutex lck4; // 带超时功能的独占互斥量
    int timeout;
    int n;
};