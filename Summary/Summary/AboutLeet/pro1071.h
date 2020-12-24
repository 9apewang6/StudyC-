#pragma once
#include "publicdef.h"
class Solutionpro1071 {
public:
    string gcdOfStrings(string str1, string str2) {
        int len1 = str1.size();
        int len2 = str2.size();
        if (len1 == len2) {
            return str1 == str2 ? str1 : "";
        }
        string temp;
        int difference = len1 - len2;
        int i = 0;
        if (difference > 0)
        {
            temp = str1.substr(len2, difference);
            string temp2 = str1.substr(0, len2);
            return gcdOfStrings(temp, temp2);
        }
        else
        {
            temp = str2.substr(len1, abs(difference));
            string temp2 = str2.substr(0, len2);
            return gcdOfStrings(temp, temp2);
        }
    }
};

/*
输入：str1 = "ABCABC", str2 = "ABC"
输出："ABC"
示例 2：

输入：str1 = "ABABAB", str2 = "ABAB"
输出："AB"
示例 3：

输入：str1 = "LEET", str2 = "CODE"
输出：""
*/

