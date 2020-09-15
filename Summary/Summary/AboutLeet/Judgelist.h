#ifndef _JUDGELIST_H_
#define _JUDGELIST_H_
#include "publicdef.h"

class Solutionp392 {
public:
    // 判断s是否为t的子序列 
    // 双指针 
    bool isSubsequence(string s, string t) {
        int  n = s.size();
        int m = t.size();
        int i=0, j=0;
        while (i<n&&j<m)
        {
            if (s[i] == t[j])
            {
                i++;
            }
            j++;
        }
        return i == n;
    }

    //动态规划方程  
    // f[i]|s[j]| = i , t[i] == s[j]
    // f[i] |s[j]| = f[i+1]|s[j]| , t[i]!=s[j]

    bool isSubsequence(string s, string t)
    {
        int  n = s.size();
        int m = t.size();
        vector<vector<int >> f(m + 1, vector<int>(26, 0));
        for (int i = 0; i < 26; i++)
        {
            f[m][i] = m;
        }
        for (int i = m - 1; i >= 0; i--) {
            for (int j = 0; j < 26; j++) {
                if (t[i] == j + 'a')
                    f[i][j] = i;
                else
                    f[i][j] = f[i + 1][j];
            }
        }
        int add = 0;
        for (int i = 0; i < n; i++) {
            if (f[add][s[i] - 'a'] == m) {
                return false;
            }
            add = f[add][s[i] - 'a'] + 1;
        }

        return true;

     }

};

#endif //_JUDGELIST_H_