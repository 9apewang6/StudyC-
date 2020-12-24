#pragma once
#include "publicdef.h"
class Solutionpro892 {
private:
    vector<int> vis;
public:
    int surfaceArea(vector<vector<int>>& grid) {
        int rows = grid.size();
        if (rows == 0)return 0;
        int columns = grid[0].size();
      //  vis.resize(rows);
      //  int reccount = 0;
        int surfacecount = 0;
        int i, j;
        for (i = 0; i < rows; i++)
        {
            for (j = 0; j < columns; j++)
            {
                if(grid[i][j]>=1)surfacecount += 6 * grid[i][j] - (grid[i][j] - 1) * 2;

                // 层覆盖 
                if ((j + 1) < columns) {
                    surfacecount -= min(grid[i][j], grid[i][j + 1]) * 2;
                }
                // 列覆盖
                if ((i + 1) < rows)
                {
                    surfacecount -= min(grid[i][j], grid[i + 1][j]) * 2;
                }
              //  reccount += grid[i][j]; 
            }
        }
        return surfacecount;
    }
};

/************************************************************************/
/* 
在 N * N 的网格上，我们放置一些 1 * 1 * 1  的立方体。

每个值 v = grid[i][j] 表示 v 个正方体叠放在对应单元格 (i, j) 上。

请你返回最终形体的表面积。

 
 示例 1：

 输入：[[2]]
 输出：10
 示例 2：

 输入：[[1,2],[3,4]]
 输出：34
 示例 3：

 输入：[[1,0],[0,2]]
 输出：16
 示例 4：

 输入：[[1,1,1],[1,0,1],[1,1,1]]
 输出：32
 示例 5：

 输入：[[2,2,2],[2,1,2],[2,2,2]]
 输出：46

*/
/************************************************************************/