#pragma once
#include "publicdef.h"
class Solution {
public:
    
    bool hasGroupsSizeX(vector<int>& deck) {
        sort(deck.begin(),deck.end());
        int minsize = 0;
        int len = deck.size();
        int i = 0;
        if (len <= 1)return false;
        map<int, int> warehouse;
        warehouse[deck[0]] = 1;
        for (i = 1; i < len; i++)
        {
            if (deck[i] != deck[i - 1])
            {
                if (minsize == 0)minsize = warehouse[deck[i - 1]];
                else {
                    minsize = gcd(minsize,warehouse[deck[i-1]]);
                }            
            }
            warehouse[deck[i]]++;
        }
        minsize = gcd(minsize, warehouse[deck[len - 1]]);
        if(minsize-==)
        // minsize 因式分解    
//         if (minsize == 1)return false;
//         for (i = 2; i < minsize; i++)
//         {
//             if (minsize%i == 0) {
//                 break;
//             }  
//         }
      
        for (auto iter : warehouse)
        {
            if (iter.second%minsize != 0)return false;
          /*  if (iter.second%minsize != 0)return false;*/
        }
        return true;
        
    }
};


int count[10000];
public:
    bool hasGroupsSizeX(vector<int>& deck) {
        int N = (int)deck.size();
        for (int c : deck) count[c]++;

        vector<int> values;
        for (int i = 0; i < 10000; ++i) {
            if (count[i] > 0) {
                values.emplace_back(count[i]);
            }
        }

        for (int X = 2; X <= N; ++X) {
            if (N % X == 0) {
                bool flag = 1;
                for (int v : values) {
                    if (v % X != 0) {
                        flag = 0;
                        break;
                    }
                }
                if (flag) return true;
            }
        }
        return false;
    }






/************************************************************************/
/* 
给定一副牌，每张牌上都写着一个整数。

此时，你需要选定一个数字 X，使我们可以将整副牌按下述规则分成1组或更多组：

每组都有 X 张牌。
组内所有的牌上都写着相同的整数。
仅当你可选的 X >= 2 时返回 true。

 

 示例 1：

 输入：[1,2,3,4,4,3,2,1]
 输出：true
 解释：可行的分组是 [1,1]，[2,2]，[3,3]，[4,4]
 示例 2：

 输入：[1,1,1,2,2,2,3,3]
 输出：false
 解释：没有满足要求的分组。
 示例 3：

 输入：[1]
 输出：false
 解释：没有满足要求的分组。
 示例 4：

 输入：[1,1]
 输出：true
 解释：可行的分组是 [1,1]
 示例 5：

 输入：[1,1,2,2,2,2]
 输出：true
 解释：可行的分组是 [1,1]，[2,2]，[2,2]

 提示：

 1 <= deck.length <= 10000
 0 <= deck[i] < 10000
*/
/************************************************************************/