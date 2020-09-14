#ifndef _RADIXSORT_H_
#define _RADIXSORT_H_
#include <iostream>
#include <algorithm>
// 基数排序
int maxbit(int data[], int len) // 辅助函数 ，求最大位
{
    int maxData = data[0];
    for (int i = 1; i < len; i++)
    {
        if (maxData < data[i])
        {
            maxData = data[i];
        }
    }
    int d = 1;
    int p = 10;
    while (maxData >= p)
    {
        maxData /= 10;
        d++;
    }
    return d;
}

void radixsort(int arr[], int len)
{
    int d = maxbit(arr, len);
    int *temp = new int[len];
    int *count = new int[10]; //counter
    int i, j, k;
    int radix = 1;
    for (i = 1; i <= d; i++)
    {
        for (j = 0; j < 10; j++)
        {
            count[j] = 0;
        }
        for (j = 0; j < len; j++)
        {
            k = (arr[j] / radix) % 10;
            count[k]++;
        }
        for (j = 1; j < 10; j++)
            count[j] = count[j - 1] + count[j];
        for (j = len - 1; j >= 0; j--)
        {
            k = (arr[j] / radix) % 10;
            temp[--count[k]] = arr[j];
        }
        for (j = 0; j < len; j++)
        {
            arr[j] = temp[j];
        }
        radix = radix * 10;
    }
    delete[] temp;
    delete[] count;
}


#endif //_RADIXSORT_H_