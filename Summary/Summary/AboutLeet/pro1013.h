#pragma once
#include "publicdef.h"
class Solutionpro1013 {
public:
    //bool canThree(vector<int>& A)
    //{
    //    int s /*= accumulate(A.begin(), A.end(), 0)*/;
    //    if (s % 3 != 0) {
    //        return false;
    //    }
    //    int target = s / 3;
    //    int n = A.size(), i = 0, cur = 0;
    //    while (i < n) {
    //        cur += A[i];
    //        if (cur == target) {
    //            break;
    //        }
    //        ++i;
    //    }
    //    if (cur != target) {
    //        return false;
    //    }
    //    int j = i + 1;
    //    while (j + 1 < n) {  // 需要满足最后一个数组非空
    //        cur += A[j];
    //        if (cur == target * 2) {
    //            return true;
    //        }
    //        ++j;
    //    }
    //    return false;
    //}
    bool canThreePartsEqualSum(vector<int>& A) {

        int total = 0;
        int len = A.size();
        if (len < 3)return false;
        int i, j;
        for (i = 0; i < len; i++)
        {
            total += A[i];
        }
        int per = total / 3;       
        if (total%3!=0)return false;
        //  
        int cur = 0;
        i = 0;
        while (i < len) {
            cur += A[i];
            if (cur == per) {
                break;
            }
            ++i;
        }
        if (cur != per) {
            return false;
        }
        j = i + 1;
        while (j + 1 < len) {  // 需要满足最后一个数组非空
            cur += A[j];
            if (cur == per * 2) {
                return true;
            }
            ++j;
        }
        return false;
    }
    void test()
    {
        string inputstr;
        vector<int > inputvec;
        char marks;
        while (getline(cin, inputstr))
        {
            inputvec = stringTovector(inputstr);
            cout << booltostring(canThreePartsEqualSum(inputvec)) << endl;
            cout << "do you want to continue .. y/n" << endl;
            cin.get(marks);
            if (marks != 'y')break;
            cin.get();
        }
    }
};



