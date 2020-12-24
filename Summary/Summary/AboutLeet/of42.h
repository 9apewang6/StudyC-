#pragma once
#include "publicdef.h"
class Solutionof42 {

public:
    //  an = an-1+an-2
    // ¶¯Ì¬¹æ»®
 
    int maxSubArray(vector<int>& nums) {
        int len = nums.size();
        if (len == 0)return 0;
        int maxvalue = nums[0];
        for (int i = 1; i < len; i++)
        {
            if (nums[i - 1] > 0)
            {
                nums[i] += nums[i - 1];
            }
            maxvalue = max(maxvalue,nums[i]);
        }
        return maxvalue;

    }
};