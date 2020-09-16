#pragma once
#include "publicdef.h"
#include <time.h>
const int WIDTH = 9;
const int HEIGHT = 10;
class Solutionof04{
public:
    //
    bool findNumberIn2DArray(vector<vector<int>>& matrix, int target) {
        int width = 0;
        int height = 0;
        height = matrix.size();
        if (height == 0)return false;
        width = matrix.at(0).size();
        if (width == 0)return false;

        int i, j;
        for (i = 0; i < height; i++)
        {
            for (j = 0; j < width; j++)
            {
                if (matrix[i][j] == target)
                {
                    return true;
                }
            }
        }
        return false;
    }
    //  way2 
    //[[1, 4, 7, 11, 15], [2, 5, 8, 12, 19], [3, 6, 9, 16, 22], [10, 13, 14, 17, 24], [18, 21, 23, 26, 30]]
   // 20
    bool findNumberIn2DArray2(vector<vector<int>>& matrix, int target) {
       
        
        int row = matrix.size();
        if (row == 0)return false;
        int column = matrix.at(0).size();
        if (column == 0)return false;
        int num = 0;
        int i = 0, j = 0;
        while (i < row)
        {
            j = 0;
            num = matrix[i][j];          
            while (j < column&&num < target)
            {
                num = matrix[i][j];
                j++;        
            }
            if (num == target)
            {
                return true;
            }         
            else 
            {
                i++;
            }
        }
        return false;
    }
    bool findNumberIn2DArray3(vector<vector<int>>& matrix, int target) {


        int row = matrix.size();
        if (row == 0)return false;
        int column = matrix.at(0).size();
        if (column == 0)return false;
        column = column - 1;
        int num = 0;
        int i = 0;
        while (i < row&&column>=0)
        {
            num = matrix[i][column];
            if (num == target)
            {
                return true;
            }
            else if (num > target)
            {
                column--;
                
            }
            else
            {
                i++;
            }
        }
        return false;
    }
    void test()
    {
        srand((unsigned int)time(NULL));
        vector<vector<int>> inputvec;
        char youcontinue;
        while (true)
        {
//             for (int i = 0; i < WIDTH; i++)
//             {
//                 vector<int> item;
//                 for (int j = 0; j < HEIGHT; j++)
//                 {
//                     item.push_back(i*HEIGHT+j);
//                 }
//                 inputvec.push_back(item);
//             }
            inputvec.push_back(vector<int>{5});
            inputvec.push_back(vector<int>{6});

            string str = booltostring(findNumberIn2DArray3(inputvec,6 ));
            cout << "the answer is " << str << endl;
            cout << "do you want to continue...(y/n)" << endl;
            cin.get(youcontinue);
            if (youcontinue != 'y')break;
            cin.get();
        }
    }
};