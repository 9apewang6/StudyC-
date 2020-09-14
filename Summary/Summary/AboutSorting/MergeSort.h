#ifndef _MERGESORT_H_
#define _MERGESORT_H_
#include <iostream>
// merge sort 
// 分治 
// 自上而下  递归 
// 自下而上  迭代 
// 1. 申请空间， 大小为两个已经排序序列之和， 
// 2. 设置两个指针， 最初位置分别为两个已经排序序列的起始位置 
// 3. 比较两个指针指向的元素 ， 
// 4. 重复3 
// 5. 将另一序列剩下的所有元素直接复制到合并序列尾

template <typename T>
void merge_sort(T arr[], int len)
{
    T *a = arr;
    T *b = new T[len];
    for (int seg = 1; seg < len; seg += seg)
    {
        for (int start = 0; start < len; start += seg+seg)
        {
            int low = start, mid = min(start + seg, len), high = min(start + seg + seg, len);
            int k = low;
            int start1 = low, end1 = mid;
            int start2 = mid, end2 = high;
            while (start1 < end1&&start2 < end2)
                b[k++] = a[start1] < a[start2] ? a[start1++] : a[start2++];
            while (start1 < end1)
                b[k++] = a[start1++];
            while (start2 < end2)
                b[k++] = a[start2++];
        }
        T *temp = a;
        a = b;
        b = temp;

    }
    if (a != arr)
    {
        for (int i = 0; i < len; i++)
        {
            b[i] = a[i];
        }
        b = a;
    }
    delete[] b;
}

template<typename T>
void Merge(vector<T>& vec, int front, int mid, int end)
{
    // 前闭后开
    vector<T> LeftSubArray(vec.begin() + front, vec.begin() + mid + 1);
    vector<T> RightSubArray(vec.back()+mid+1,vec.begin()+end+1);
    int idxleft = 0, idxright = 0;
    LeftSubArray.insert(LeftSubArray.end(), numeric_limits<T>::max());
    RightSubArray.insert(RightSubArray.end(), numeric_limits<T>::max());

    for (int i = front; i <= end; i++)
    {
        if (LeftSubArray[idxleft] < RightSubArray[idxright])
        {
            vec[i] = LeftSubArray[idxleft];
            idxleft++;
        }
        else
        {
            vec[i] = RightSubArray[idxright];
            idxright++;
        }
    }
}
template<typename T>
void MergeSort(vector<T>& vec, int front, int end)
{
    if (front >= end)
        return;
    int mid = (front + end) / 2; // 递归， 自上而下 ，后序
    MergeSort(vec, front, mid);
    MergeSort(vec, mid + 1, end);
    Merge(vec,front,mid,end);
}
#endif //_MERGESORT_H_