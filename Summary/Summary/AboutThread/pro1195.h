#pragma once
#include "publicdef.h"
class FizzBuzz {
private:
    int n;
    int cur_n;
    std::mutex mymutex;
    std::condition_variable cv;
public:
    FizzBuzz(int n) {
        this->n = n;
        cur_n = 1;
    }

    // printFizz() outputs "fizz".
    void fizz(function<void()> printFizz) {
        std::unique_lock<std::mutex> lck(mymutex);
        cv.wait(lck, [this]() {return cur_n % 3 != 0; });

        if (cur_n % 3 == 0 && cur_n % 5 != 0)
        {
            printFizz();
            cur_n++;
        }
        cv.notify_all();
    }

    // printBuzz() outputs "buzz".
    void buzz(function<void()> printBuzz) {
        std::unique_lock<std::mutex> lck(mymutex);
        cv.wait(lck, [this]() {return cur_n % 5 != 0; });

        if (cur_n % 5 == 0 && cur_n % 3 != 0)
        {
            printBuzz();
            cur_n++;
        }
        cv.notify_all();

    }

    // printFizzBuzz() outputs "fizzbuzz".
    void fizzbuzz(function<void()> printFizzBuzz) {
        std::unique_lock<std::mutex> lck(mymutex);
        cv.wait(lck, [this]() {return cur_n % 3 != 0&&cur_n%5!=0 ; });
        
        if (cur_n % 3 == 0 && cur_n % 5 == 0)
        {
            printFizzBuzz();
            cur_n++;
        }
        cv.notify_all();

    }

    // printNumber(x) outputs "x", where x is an integer.
    void number(function<void(int)> printNumber) {
        std::unique_lock<std::mutex> lck(mymutex);
        cv.wait(lck, [this]() {return cur_n % 3 == 0 || cur_n % 5 == 0; });
        std::cout << cur_n << std::endl;
        cur_n++;     
        cv.notify_all();
    }

};