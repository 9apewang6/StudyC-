#pragma once
#include "publicdef.h"
class Solution0101 {
public:
    bool isUnique(string astr) {
        map<char, int> buckets;
        int len = astr.size();
        for (int i = 0; i < len; i++)
        {
            buckets[astr[i]]++;
            if (buckets[astr[i]] > 1)return false;
        }
        return true;
    }
    void test()
    {
        string inpustr;
        char marks;
        while (getline(cin, inpustr))
        {
            cout << booltostring(isUnique(inpustr)) << endl;
            cout << "do you want to continue...y/n" << endl;
            cin.get(marks);
            if (marks != 'y')break;
            cin.get();
        }
    }
};



class Solutionof06 {
public:
    vector<int> reversePrint(ListNode* head) {
        stack<int> tep;
        ListNode* tail = head;
        vector<int> ans;
        while (tail != nullptr)
        {
            tep.push(tail->val);
            tail = tail->next_;
        }
        while (!tep.empty())
        {
            ans.push_back(tep.top());
            tep.pop();
        }
        return ans;
    }
};



