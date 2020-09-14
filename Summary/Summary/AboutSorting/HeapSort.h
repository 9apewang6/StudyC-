#ifndef _HEAPSORT_H_
#define _HEAPSORT_H_
#include <iostream>
#include <algorithm>
// ´ó¶¥¶Ñ 

template<typename T>
void max_heapify(T arr[], int start, int end)
{
    int parentnode = start;
    int childnode = parentnode * 2 + 1;
    while (childnode <= end)
    {
        if (childnode + 1 <= end&& arr[childnode] < arr[childnode + 1])
            childnode++;
        if (arr[parentnode] > arr[childnode])
            return;
        else
        {
            swap(arr[parentnode], arr[childnode]);
            parentnode = childnode;
            childnode = parentnode * 2 + 1;
        }
    }
}

template<typename T>
void heapsort(T arr[], int len)
{
    for (int i = len / 2 - 1; i >= 0; i--)
    {
        max_heapify(arr, i, len - 1);

    }
    for (int i = len - 1; i > 0; i--)
    {
        swap(arr[0],arr[i]);
        max_heapify(arr, 0, i - 1);
    }
}


#endif // _HEAPSORT_H_