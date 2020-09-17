#pragma once
#include "publicdef.h"
//  fn = fn-1+fn-2;
class Solutionoff10_1 {
public:
    int deal(int n)
    {
        if (n == 0)
        {
            return 0;
        }
        if (n == 1)
        {
            return 1;
        }
        return deal(n - 1) + deal(n - 2);
    }
//     int fib(int n) {
//         int ans = deal(n);
// 
//         return ans % (1000000007);
// 
//     }

    int fib(int n)
    {
        if (n == 0)return 0;
        if (n == 1)return 1;
        int  llast = 0;
        int  last = 1;
        int ans = 0;
        // ¶¯Ì¬¹æ»®
        for (int i = 2; i <= n; i++)
        {
            ans = (last + llast)%(1000000007);
            llast = last % (1000000007);
            last = ans % (1000000007);
        }
        return  ans % (1000000007);
    }
};