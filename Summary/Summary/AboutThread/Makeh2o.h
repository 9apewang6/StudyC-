#pragma once
#include "publicdef.h"
//   构造 水分子 ， h2o , 



class H2O {
public:
    H2O() {
        h_num = 0;
        o_num = 0;
    }
    // 超时 了
    void hydrogen(function<void()> releaseHydrogen) {

        // releaseHydrogen() outputs "H". Do not change or remove this line.
        std::unique_lock<std::mutex> lck(mymutex);
//         if (water.h_num == 2)
//             ho.wait(lck);
        ho.wait(lck, [this] (){return h_num < 2; });
        releaseHydrogen();
        h_num++;
        if (h_num == 2 && o_num == 1)
        {
            h_num = 0;
            o_num = 0;
           
        }
        ho.notify_one();
    }

    void oxygen(function<void()> releaseOxygen) {

        // releaseOxygen() outputs "O". Do not change or remove this line.
        std::unique_lock<std::mutex> lck(mymutex);
        ho.wait(lck, [this]() {return o_num < 1; });

        releaseOxygen();
        o_num++;
        if (h_num == 2 && o_num == 1)
        {
            h_num = 0;
            o_num = 0;
            
        }
        ho.notify_one();

    }
private:
    std::mutex mymutex;
    std::condition_variable ho;
    int h_num;
    int o_num;
};




class Semaphore
{
private:
    int n_;
    std::mutex mymutex;
    std::condition_variable cv;
public:
    Semaphore(int n) :n_(n) {};
    
    void wait()
    {
        std::unique_lock<std::mutex> lck(mymutex);
        if (!n_)
        {
            cv.wait(lck, [this] {return n_; });
        }
        --n_;
    }
    void signal()
    {
        std::unique_lock<std::mutex> lck(mymutex);
        ++n_;
        cv.notify_one();
    }
};

class H2O {
private:
    Semaphore s_hIn, s_oIn;
    Semaphore s_hBarrier, s_oBarrier;

public:
    H2O() : s_hIn{ 2 }, s_oIn{ 1 }, s_hBarrier{ 0 }, s_oBarrier{ 0 } {}

    void hydrogen(function<void()> releaseHydrogen) {
        s_hIn.wait();
        s_oBarrier.signal();
        s_hBarrier.wait();
        releaseHydrogen();
        s_hIn.signal();
    }

    void oxygen(function<void()> releaseOxygen) {
        s_oIn.wait();
        s_oBarrier.wait();
        s_oBarrier.wait();
        s_hBarrier.signal();
        s_hBarrier.signal();
        releaseOxygen();
        s_oIn.signal();
    }
};



