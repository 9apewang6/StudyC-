#pragma once
#include "publicdef.h"
class Solution {
public:
    inline void revert(string& s)
    {
        int len = s.size();
        for (int i = 0; i < len / 2; i++)
        {
            swap(s[i],s[len-i-1]);
        }
    }
    string reverseWords(string s) {
        
        stringstream ss;
        string ans;
        if (s.size() == 0)return ans;
        ss.str(s);
        char delim = ' ';
        string item;
        while (getline(ss, item, delim))
        {
            revert(item);
            ans += item;
            ans += delim;
        }

        return ans.substr(0,ans.size()-2);
    }

    string reverseWords(string s)
    {
        int length = s.length();
        int i = 0;
        while (i < length) {
            int start = i;
            while (i < length && s[i] != ' ') {
                i++;
            }

            int left = start, right = i - 1;
            while (left < right) {
                swap(s[left], s[right]);
                left++;
                right--;
            }
            while (i < length && s[i] == ' ') {
                i++;
            }
        }
        return s;

       
    }
};


/************************************************************************/
/* 


给定一个字符串，你需要反转字符串中每个单词的字符顺序，同时仍保留空格和单词的初始顺序。

 

 示例：

 输入："Let's take LeetCode contest"
 输出："s'teL ekat edoCteeL tsetnoc"
  

  提示：

  在字符串中，每个单词由单个空格分隔，并且字符串中不会有任何额外的空格。

  */
/************************************************************************/