/*!
 * \file Bubble.h
 * \ 冒泡排序
 * \author peng.wang@bommnig.com
 * \date 九月 2020
 *
 * 
 */
/*
核心流程:
    
    void bubble_sort(T arr[], int len) {
    int i, j;
    for (i = 0; i < len - 1; i++)
    for (j = 0; j < len - 1 - i; j++)
    if (arr[j] > arr[j + 1])
    swap(arr[j], arr[j + 1]);
    }



*/
#include <iostream>
#include <algorithm>
#include <vector>
using std::vector;
//template<typename T>
// 这是什么排序？  冒泡? 选择
// void BubbleSort(vector<T> &PendingArray,bool Descending = false)
// {
//     int i = 0; 
//     int j = 0;
//     int size = PendingArray.size();
//     if (size == 0)return;
//     int temp = 0;
//     while (i < (size-1))
//     {
//         j = i + 1;
//         while (j < size)
//         {
//             if (Descending&& PendingArray[i]<=PendingArray[j])
//             {
//                 swap(PendingArray[i], PendingArray[j]);
//             }
//             else if (!Descending&& PendingArray[i] >= PendingArray[j])
//             {
//                 swap(PendingArray[i], PendingArray[j]);
//             }
//             ++j;
//         }
//         ++i;
//     }
// }

template<typename T>
void BubbleSort2(vector<T> &PendingArray, bool Descending = false)
{
    int i = 0;
    int j = 0;
    int size = PendingArray.size();
    if (size == 0)return;   
    while (i < (size - 1))
    {

        while (j < (size-1-i))
        {
            if (Descending&&( PendingArray[j] < PendingArray[j+1]))
            {
                swap(PendingArray[j], PendingArray[j + 1]);
            }
            else if (!Descending&&( PendingArray[j] > PendingArray[j+1]))
            {
                swap(PendingArray[j], PendingArray[j + 1]);

            }
            ++j;
        }
        ++i;
        j = 0;// 
    }
}

