#pragma once
#include "publicdef.h"
class Solution {
public:
    int findmax(vector<int>& nums, int left, int right)
    {
        int maxvalue = nums[left];
        for (int i = left; i <= right; i++)
        {
            maxvalue = max(maxvalue, nums[i]);
        }
        return maxvalue;
    }
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        int len = nums.size();
        int left = 0;
        int right = 0+k-1;
        vector<int> ans;
        if (k <= 1)return nums;
        if (right >= len) ans.push_back(findmax(nums, left, len - 1));
        int tempmax = 0;
        while (left < right&& right < len)
        {
            tempmax = findmax(nums, left, right);
            ans.push_back(tempmax);
            left++;
            right++;
        }
        return ans;
    }
};