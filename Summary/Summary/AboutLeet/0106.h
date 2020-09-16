#pragma once
#include "publicdef.h"
/*
×Ö·û´®Ñ¹Ëõ

*/

class Solution0106 {
public:
    string compressString(string S) {
        int len = S.size();
        if (len <= 2)return S;

        string ans;

        int counts = 0;
        int i = 0;
        char cur = ' ';
        for (i = 0; i < len; i++)
        {
            if (cur != S.at(i))
            {
                cur = S.at(i);
                if (counts > 0)ans += to_string(counts);
                counts = 1;
                ans += cur;
            }
            else
            {
                counts++;
            }
        }
        if (counts > 0)ans += to_string(counts);
        int anslen = ans.size();
        return (anslen>=len) ? S:ans;
    }
    void test()
    {
        string inputstr;
        string output;
        char youcontinue;
        while (getline(cin, inputstr))
        {
            output = compressString(inputstr);
            cout << "after compressString the string is " << output << endl;
            cout << "do you want to continue test...(y/n)" << endl;
            cin.get(youcontinue);
            if (youcontinue != 'y')break;
            cin.get();
        }
    }
};