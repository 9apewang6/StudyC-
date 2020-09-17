#pragma once
#include "publicdef.h"
class Solution {
public:
    vector<int> intersect(vector<int>& nums1, vector<int>& nums2) {
        map<int, int> warehouse;
        vector<int> ans;
        int len1 = nums1.size();
        int len2 = nums2.size();
        if (len1 == 0 || len2 == 0)return ans;
        int i = 0;
        for (i = 0; i < len1; i++)
        {
            warehouse[nums1[i]]++;
        }
        for (i = 0; i < len2; i++)
        {
            if (warehouse[nums2[i]]>0)
            {
                warehouse[nums2[i]]--;
                ans.push_back(nums2[i]);
            }
        }
        return ans;

    }


    vector<int> intersect(vector<int>& nums1, vector<int>& nums2) {
        map<int, int> warehouse;
        vector<int> ans;
        int len1 = nums1.size();
        int len2 = nums2.size();
        if (len1 == 0 || len2 == 0)return ans;
        int i = 0;
        if (len1 < len2)
        {
            for (i = 0; i < len1; i++)
            {
                warehouse[nums1[i]]++;
            }
            for (i = 0; i < len2; i++)
            {
                if (warehouse[nums2[i]] > 0)
                {
                    warehouse[nums2[i]]--;
                    ans.push_back(nums2[i]);
                }
            }
        }
        else
        {
            for (i = 0; i < len2; i++)
            {
                warehouse[nums2[i]]++;
            }
            for (i = 0; i < len1; i++)
            {
                if (warehouse[nums1[i]] > 0)
                {
                    warehouse[nums1[i]]--;
                    ans.push_back(nums1[i]);
                }
            }
        }
        return ans;

    }
};