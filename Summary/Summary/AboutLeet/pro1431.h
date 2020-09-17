#pragma once
#include "publicdef.h"

class Solution {
public:
    vector<bool> kidsWithCandies(vector<int>& candies, int extraCandies) {
        // 首先找到最大
        vector<bool> ans;
        int len = candies.size();      
        if (len==0)return ans;
        ans.resize(len);
        int maxcandies = candies[0];
        int i;
        for (i = 0; i < len; i++)
        {
            maxcandies = max(maxcandies,candies[i]);
        }

        for (i = 0; i < len; i++)
        {
            if ((extraCandies + candies[i]) >= maxcandies)
            {
                ans[i] = true;
            }
            else
            {
                ans[i] = false;
            }
        }
        return ans;
        
    }
};