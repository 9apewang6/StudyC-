#pragma once
#include "publicdef.h"
// ������ ��ͬλ����
class Solution {
public:
    int hammingDistance(int x, int y) {
        int z = x^y;
        int len = 0;
        while (z != 0)
        {
            len++;
            z = z&(z - 1);
       }
        return len;
    }
};