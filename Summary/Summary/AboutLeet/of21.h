#pragma once
#include "publicdef.h"
class Solutionof21 {
public:
    vector<int> exchange(vector<int>& nums) {
        vector<int> ans;
        int len = nums.size();
        if (len == 0)return ans;
        int left = 0;
        int right = len - 1;
        ans.resize(len);
        int i = 0;
        while (i<len&&left <= right)
        {
            if (nums[i] % 2 != 0) {
                ans[left] = nums[i];
                left++;
            }
            else
            {
                ans[right] = nums[i];
                right--;
            }
            i++;
        }
        return ans;
    }
};