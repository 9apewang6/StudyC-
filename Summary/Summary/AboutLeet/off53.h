#pragma once
#include "publicdef.h"
class Solutionoff53 {
public:
    int missingNumber(vector<int>& nums) {
        int len = nums.size();
        if (len == 0)return 0;
        int left = 0, right = len - 1;
        while (left <= right)
        {
            int m = (left + right) / 2;
            if (nums[m] == m) left = m + 1;
            else right = m - 1;

            if (nums[left] != left)
            {
                return left;
            }
            if (nums[right] != (right+1))
            {
                return (right+1);
            }
            left++;
            right--;
        }
        return left;
    }
};