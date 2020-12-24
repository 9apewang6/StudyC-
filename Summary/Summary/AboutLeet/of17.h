#pragma once
#include "publicdef.h"
class Solution {
public:
    vector<int> printNumbers(int n) {
        int num = pow(10,n)-1;
        
        vector<int> ans;
        if (num == 0)return ans;
        ans.resize(num);
        int i = 0;
        for (i = 0; i < num; i++)
        {
            ans[i] = i + 1;
        }
        return ans;

    }
};