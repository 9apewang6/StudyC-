#ifndef _QUICKSORT_H_
#define _QUICKSORT_H_

#include <iostream>
// 快速排序， 选择基准值， 大于基准值的放右边， 小于基准值的放左边 ,所谓分区paritition

template<typename T>
int Paritition(vector<T>&vec, int  low, int high,bool Descending = false)
{
    int pivot = vec[low];
    // 小于 vec[left]的数字放左边 ， 大于放右边 
    while (low < high)
    {
        while (low < high&&vec[high] >= pivot)
            --high;
        vec[low] = vec[high];
        while (low < high&&vec[low] <= pivot)
            ++low;
        vec[high] = vec[low];
       
    }
    vec[low] = pivot;
    return low;
}

template<typename T>
void quickSort(vector<T>&vec,int low,int high ,bool Descending = false)
{
    if (low < high)
    {
        int pivot = Paritition(vec, low, high, Descending);
        quickSort(vec, 0, pivot - 1, Descending);
        quickSort(vec, pivot + 1,high, Descending);
    }
};




// 函数法  
struct Range
{
    int start, end;
    Range(int s = 0, int e = 0)
    {
        start = s;
        end = e;
    }
};
template<typename T>
void quick_sort(T arr[], const int len)
{
    if (len <= 0)
        return;
    Range r[len];
    int p = 0;
    r[p++] = Range(0,len-1);
    while (p)
    {
        Range range = r[--p];
        if (range.start >= range.end)
            continue;
        T mid = arr[range.end];
        int left = range.start;
        int right = range.end - 1;
        while (left < right)
        {
            while (arr[left] < mid && left < right) left++;
            while (arr[right] > mid &&left < right)right--;
            swap(arr[left], arr[right]);
        }
        if (arr[left] >= arr[range.end])
            swap(arr[left], arr[range.end]);
        else
            left++;
        r[p++] = Range(range.start, left - 1);
        r[p++] = Range(left + 1, range.end);
    }
}


// 迭代法 
template<typename T>
void quick_sort_recursive(T arr[], int start, int end)
{
    if (start >= end)
    {
        return;
    }
    T mid = arr[end];
    int left = start, right = end-1;
    while (left < right)
    {
        while (arr[left] < mid && left < right)
        {
            left++;
        }
        arr[right] = arr[left];
        while (arr[right] > mid && left < right)
            right--;
        arr[left] = arr[right];
    }
    if (arr[left] >= arr[right])
        swap(arr[left], arr[right]);
    else
        left++;
    quick_sort_recursive(arr, start, left - 1);
    quick_sort_recursive(arr, left + 1, end);
}
template<typename T>
void quicksortrecur(T arr[], int len)
{
    quick_sort_recursive(arr, 0, len - 1);
}

#endif //_QUICKSORT_H_