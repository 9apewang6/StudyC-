#pragma once
#include "publicdef.h"

class Solution202
{
public:
    //λ�� ƽ��  = 1
    //��ϣ��
    // ��� �ݱ�ɼ�⻷ 
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