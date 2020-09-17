#pragma once
#include "publicdef.h"
//递归 ，迭代 ，暴力 
class Solutionpro189 {
public:
    //1. 暴力
    void rotate(vector<int>& nums, int k) {
        int len = nums.size();
        k = k%len;
        int temp = 0;
        int i;
        while (k > 0)
        {
            {
                temp = nums[len - 1];
                for (i = len - 1; i > 0; i--)
                {
                    nums[i] = nums[i - 1];
                }
                nums[i] = temp;          
            }

            k--;
        }
    }
    // 2.
    void rotate(vector<int>& nums, int k)
    {
        int len = nums.size();
        if (len == 0)return;
        k = k%len;
        stack<int> q;
        vector<int> ans;
        ans.resize(len);
        int i;
        for (i = len - 1; i > len - 1 - k; i--)
        {
            q.push(nums[i]);
        }
        i = 0;
        while (!q.empty())
        {
            ans[i] = q.top();
            q.pop();
            i++;
        }
        for (i = 0; i < len-k; i++)
        {
            ans[i + k] = nums[i];
        }
        nums = ans;
    }
};


/*
给定一个数组，将数组中的元素向右移动 k 个位置，其中 k 是非负数。

示例 1:

输入: [1,2,3,4,5,6,7] 和 k = 3
输出: [5,6,7,1,2,3,4]
解释:
向右旋转 1 步: [7,1,2,3,4,5,6]
向右旋转 2 步: [6,7,1,2,3,4,5]
向右旋转 3 步: [5,6,7,1,2,3,4]
示例 2:

输入: [-1,-100,3,99] 和 k = 2
输出: [3,99,-1,-100]
解释:
向右旋转 1 步: [99,-1,-100,3]
向右旋转 2 步: [3,99,-1,-100]
说明:

尽可能想出更多的解决方案，至少有三种不同的方法可以解决这个问题。
要求使用空间复杂度为 O(1) 的 原地 算法。



*/