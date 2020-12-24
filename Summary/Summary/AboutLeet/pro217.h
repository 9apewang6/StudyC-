#pragma once
#include "publicdef.h"
class Solutionpro217 {
public:
    bool containsDuplicate(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        int len = nums.size();
        if (len <= 1)return false;
        int i = 0;
        for (i = 0; i < len-1; i++)
        {
            if (nums[i] == nums[i + 1])return true;
        }
        return false;
    }
};