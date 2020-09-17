#pragma once
#include "publicdef.h"
// À≥ ±’Î

//  i,j  , column , row , 
//i =0  ,j++ , j=column , i++,;
//i=row, j=column , j--;  
// j=0,i=row , i--;  

class Solutionof29 {
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        int row = matrix.size();
        if (row == 0) return{ -1,-1 };
        int column = matrix[0].size();
        int i=0, j = column-1;
        int top = 0, bottom = row - 1;
        vector<int> ans;
        while (i<j&&top<bottom)
        {
            for (int col = i; col <= j; col++)
            {
                ans.push_back(matrix[i][col]);
            }

            for (int rows = top + 1; rows <= bottom; rows++)
            {
                ans.push_back(matrix[rows][j]);
            }
            if (i < j&&top < bottom)
            {
                for (int col = j - 1; col > i; col--) {
                    ans.push_back(matrix[bottom][col]);
                }
                for (int ro = bottom; ro > top; ro--) {
                    ans.push_back(matrix[ro][i]);
                }
            }

            i++;
            top++;
            j--;
            bottom--;
         
        }
        return ans;
        
    }

    vector<int> function(vector<vector<int>>& matrix)
    {
        if (matrix.size() == 0 || matrix[0].size() == 0) {
            return{};
        }

        int rows = matrix.size(), columns = matrix[0].size();
        vector<int> order;
        int left = 0, right = columns - 1, top = 0, bottom = rows - 1;
        while (left <= right && top <= bottom) {
            for (int column = left; column <= right; column++) {
                order.push_back(matrix[top][column]);
            }
            for (int row = top + 1; row <= bottom; row++) {
                order.push_back(matrix[row][right]);
            }
            if (left < right && top < bottom) {
                for (int column = right - 1; column > left; column--) {
                    order.push_back(matrix[bottom][column]);
                }
                for (int row = bottom; row > top; row--) {
                    order.push_back(matrix[row][left]);
                }
            }
            left++;
            right--;
            top++;
            bottom--;
        }
        return order;

  
    }
};