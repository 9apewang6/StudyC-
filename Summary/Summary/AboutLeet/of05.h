#pragma once
#include "publicdef.h"
class Solutionof05 {
public:
    string replaceSpace(string s) {
        char key = ' ';
        int pos = s.find(key);
        if (pos < 0)return s;
        int len = s.size();
        string ans;
        for (int i = 0; i < len; i++)
        {
            if (s[i] == key)
            {
                ans += "%20";
            }
            else
            {
                ans += s.at(i);
            }
        }
        return ans;
    }

    void test()
    {
        string inputstr;
        string output;
        char youcontinue;
        while (getline(cin,inputstr))
        {
            output = replaceSpace(inputstr);
            cout << "after replacespace the string is " << output<<endl;
            cout << "do you want to continue test...(y/n)" << endl;
            cin.get(youcontinue);
            if (youcontinue != 'y')break;
            cin.get();
        }
    }
};