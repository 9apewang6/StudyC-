#ifndef _MAXPALINDROME_H_
#define _MAXPALINDROME_H_
#include "publicdef.h"
/************************************************************************/
/* 
通过 str 构造最长的 回文字符串 

*/
/************************************************************************/
class Maxpalindrome
{
public:
    int longestpalindrome(std::string &str)
    {
        int len = str.size();
        int i = 0;
        map<char, int> keyvalue;
        for (i = 0; i < len; i++)
        {
            keyvalue[str[i]]++;
        }
        int size = keyvalue.size();
        int length = 0;
        bool odd = false;
        for (auto iter : keyvalue)
        {
            if (iter.second % 2 == 0)
            {
                length += iter.second;
            }
            else
            {
                odd = true;
                length += (iter.second - 1);
            }
       }
        if (odd) length += 1;
        return length;
    }
    void test()
    {
        string inputstr;
        char youcontinue;
        while (getline(cin, inputstr))
        {
            trimleftspace(inputstr);
            trimrightspace(inputstr);
            cout << " answer is :" << longestpalindrome(inputstr) << endl;
            cout << "do you want to continue...(y/n)" << endl;
            cin.get(youcontinue);
            if (youcontinue != 'y')break;
            cin.get();
        }
    }
};

#endif //_MAXPALINDROME_H_