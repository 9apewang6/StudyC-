#pragma once
#include "publicdef.h"
/*

一个有名的按摩师会收到源源不断的预约请求，每个预约都可以选择接或不接。在每次预约服务之间要有休息时间，因此她不能接受
相邻的预约。给定一个预约请求序列，替按摩师找到最优的预约集合（总预约时间最长），返回总的分钟数。

注意：本题相对原题稍作改动

定义 dp[i][0]dp[i][0] 表示考虑前 ii 个预约，第 ii 个预约不接的最长预约时间，dp[i][1]dp[i][1] 表示考虑前 ii 个预约，第 ii 个预约接的最长预约时间。

从前往后计算 dpdp 值，假设我们已经计算出前 i-1i−1 个 dpdp 值，考虑计算 dp[i][0/1]dp[i][0/1] 的答案。

首先考虑 dp[i][0]dp[i][0] 的转移方程，由于这个状态下第 ii 个预约是不接的，所以第 i-1i−1 个预约接或不接都可以，故可以从 dp[i-1][0]dp[i−1][0] 和 dp[i-1][1]dp[i−1][1] 两个状态转移过来，转移方程即为：

dp[i][0]=max(dp[i-1][0],dp[i-1][1])
dp[i][0]=max(dp[i−1][0],dp[i−1][1])

对于 dp[i][1]dp[i][1] ，由于这个状态下第 ii 个预约要接，根据题目要求按摩师不能接受相邻的预约，所以第 i-1i−1 个预约不能接受，故我们只能从 dp[i-1][0]dp[i−1][0] 这个状态转移过来，转移方程即为：

dp[i][1]=dp[i-1][0]+\textit{nums}_i
dp[i][1]=dp[i−1][0]+nums
i
​


其中 \textit{nums}_inums
i
​
表示第 ii 个预约的时长。

最后答案即为 max(dp[n][0],dp[n][1])max(dp[n][0],dp[n][1]) ，其中 nn 表示预约的个数。

再回来看转移方程，我们发现计算 dp[i][0/1]dp[i][0/1] 时，只与前一个状态 dp[i-1][0/1]dp[i−1][0/1] 有关，所以我们可以不用开数组，只用两个变量 dp_0dp
0
​
，dp_1dp
1
​
分别存储 dp[i-1][0]dp[i−1][0] 和 dp[i-1][1]dp[i−1][1] 的答案，然后去转移更新答案即可。



*/
class Solution1716 {
public:
    int massage(vector<int>& nums) {
        //
        int i = 0;
        int len = nums.size();
  
        int sum = 0;
        if (len == 0)return 0;
        if (len == 1)return nums.at(0);
        if (len == 2)return max(nums.at(0),nums.at(1));
        int f0 = nums.at(0);
        int f1 = max(nums.at(0), nums.at(1));
        if (len % 2 == 0)
        {
            sum += f1;
            for (i = 3; i < len; i+=2)
            {
                sum = sum + max(nums.at(i),nums.at(i-1));
            }
        }
        else
        {
            sum += f0;
            for (i = 2; i < len; i+=2)
            {
                sum = sum + max(nums.at(i), nums.at(i -1));
            }
        }
        return sum;
    }

    int message(vector<int>& nums)
    {
        int n = (int)nums.size();
        if (!n) return 0;
        int dp0 = 0, dp1 = nums[0];
        int tdp0 = 0;
        int tdp1 = 0;
        for (int i = 1; i < n; ++i) {
            tdp0 = max(dp0, dp1); // 计算 dp[i][0]
            tdp1 = dp0 + nums[i]; // 计算 dp[i][1]

            dp0 = tdp0; // 用 dp[i][0] 更新 dp_0
            dp1 = tdp1; // 用 dp[i][1] 更新 dp_1
        }
        return max(dp0, dp1);
    }
    void test()
    {
        string inputstr;
        vector<int> inputvec;
        int ans;
        char youcontinue;
        while (getline(cin, inputstr))
        {
            inputvec = stringTovector(inputstr);
            ans = massage(inputvec);
            cout << " answer is " << ans << endl;
            cout << "do you want to continue ... y/n" << endl;
            cin.get(youcontinue);
            if (youcontinue != 'y')break;
            cin.get();
        }
    }
};