#pragma once
#include "publicdef.h"
class Solutionp167 {
public:
    vector<int> twoSum2(vector<int>& numbers, int target) {
        int len = numbers.size();
        int i, j;
        vector<int> ans;
        int sum = 0;
        for (i = 0; i < len - 1; i++)
        {        
            if(i>0 && numbers.at(i)==numbers.at(i-1))continue;
            for(j=i+1;j<len;j++)
            {
                if (j >= len)return ans;
                if (numbers.at(j) >= target)
                {
                    len = j+1;
                }
                if (numbers.at(i) == (target - numbers.at(j)))
                {
                    ans.push_back((i+1));
                    ans.push_back((j+1));
                    return ans;
                }
            }
        }
        return ans;
    }

    vector<int> twoSum(vector<int>& numbers, int target)
    {
        int left = 0;
        int right = numbers.size() - 1;
        int sum = 0;
        while (left < right)
        {
            sum = numbers.at(left) + numbers.at(right);
            if (sum == target)
            {
                return{ left + 1,right + 1 };
            }
            else if (sum > target)
            {
                right--;
            }
            else
            {
                left++;
            }
        }
        return {-1, -1};

    }

    void test()
    {
        string inputstr;
        vector<int> inputvec;
        vector<int> output;
        
        char youcontinue;
        int target;
        while (getline(cin, inputstr))
        {
            inputvec = stringTovector(inputstr);
            cout << " input your target num:";
            cin >> target;
            cin.get();
            output = twoSum(inputvec,target);
            string ans = vectorTostring(output);
            cout << " answer is :" << "    " << ans<<endl;
            cout << "do you want to continue ...(y/n)" << endl;
            cin.get();
            cin.get(youcontinue);
            if (youcontinue != 'y')break;
            cin.get();
        }
    }
};