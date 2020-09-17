#pragma once
#include "publicdef.h"

class Solution202
{
public:
    //位数 平方  = 1
    //哈希表
    // 最后 演变成检测环 
    bool isHappy(int n) {
        if (n == 0)return false;
        map<int, bool> warehouse;
        warehouse[n] = true;
        int value = 0;
        int mod = 0;
        while (n != 0)
        {
            mod = n % 10;
            n = n / 10;
            value += mod*mod;
        }
        warehouse[value] = true;
        while (value != 1)
        {
            n = value;
            value = 0;
            while (n != 0)
            {
                mod = n % 10;
                n = n / 10;
                value += mod*mod;
            }
            if (warehouse[value])return false;
            warehouse[value] = true;
        }
        return true;
    }
};