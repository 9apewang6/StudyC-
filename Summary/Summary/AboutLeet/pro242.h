#pragma once
#include "publicdef.h"
// ×ÖÄ¸ÒìÎ»´Ê
class Solutionpro242 {
public:
    bool isAnagram(string s, string t) {
        sort(s.begin(), s.end());
        sort(t.begin(), t.end());
        return s.compare(t)==0;

    }
    bool isAnagram(string s, string t) {
        int slen = s.size();
        int tlen = t.size();
        if (slen != tlen)return false;
        map<char, int> warehouse;
        int i, j;
        for (i = 0; i < slen; i++)
        {
            warehouse[s[i]]++;
            warehouse[t[i]]--;
        }
        for (i = 0; i < slen; i++)
        {
            if (warehouse[t[i]] < 0)return false;
        }
//         for (i = 0; i < tlen; i++)
//         {
//             if (warehouse[t[i]] > 0)
//             {
//                 warehouse[t[i]]--;
//             }
//             else
//             {
//                 return false;
//             }
//         }
        return true;
    }
};