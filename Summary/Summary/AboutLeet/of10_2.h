#pragma once
#include "publicdef.h"
class Solutionof10_2 {
private:
    int nums;
public:
    // 1 . �ݹ�  ��ʱ 
    void dfs(int l, int n)
    {
        if (l == n)
        { 
            nums++;// mod 1000000007
            return;
        }
        else if (l > n)
        {
            return;
        }       
        for (int i = 1; i <= 2; i++)
        {
            dfs(l + i, n);
        }
        return ;
    }
    int numWays(int n) {
        if (n == 0)return 1;
         nums = 0;
        for (int i = 1; i <= 2; i++)
        {          
            dfs(i,n);
        }
        
        return nums;
    }

    //2. ��̬�滮 fn = fn-1+fn-2
    int numWays(int n)
    {
        if (n == 0)return 1;
        if (n == 1)return 1;
        if (n == 2)return 2;
        int dp0 = 1;
        int dp1 = 2;
        int sum = 0;
        for (int i = 3; i <= n; i++)
        {
            sum = (dp0 + dp1)% 1000000007;
            dp0 = dp1;
            dp1 = sum;
        }
        return sum;
    }
};


/************************************************************************/
/* 

ʾ�� 1��

���룺n = 2
�����2
ʾ�� 2��

���룺n = 7
�����21
ʾ�� 3��

���룺n = 0
�����1



*/
/************************************************************************/