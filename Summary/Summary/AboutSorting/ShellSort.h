#ifndef _SHELLSORT_H_
#define _SHELLSORT_H_
#include <iostream>

// 希尔排序 
// 插入排序基础之上
// 改进， 分治 ，  分组插入排序， 整组插入排序
template<typename T>
void shell_sort(T arr[], int len)
{
    int h = 1;
    while (h < len / 3)
    {
        h = 3 * h + 1;
    }
    while (h >= 1)
    {
        for (int i = h; i < len; i++)
        {
            for (int j = i; j >= h&&arr[j] < arr[j - h]; j -= h)
            {
                swap(arr[j],arr[j-h]);
            }
        }
        h = h / 3;
    }
}




#endif //_SHELLSORT_H_