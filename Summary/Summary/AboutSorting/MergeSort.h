#ifndef _MERGESORT_H_
#define _MERGESORT_H_
#include <iostream>
// merge sort 
// ���� 
// ���϶���  �ݹ� 
// ���¶���  ���� 
// 1. ����ռ䣬 ��СΪ�����Ѿ���������֮�ͣ� 
// 2. ��������ָ�룬 ���λ�÷ֱ�Ϊ�����Ѿ��������е���ʼλ�� 
// 3. �Ƚ�����ָ��ָ���Ԫ�� �� 
// 4. �ظ�3 
// 5. ����һ����ʣ�µ�����Ԫ��ֱ�Ӹ��Ƶ��ϲ�����β

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
    // ǰ�պ�
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
    int mid = (front + end) / 2; // �ݹ飬 ���϶��� ������
    MergeSort(vec, front, mid);
    MergeSort(vec, mid + 1, end);
    Merge(vec,front,mid,end);
}
#endif //_MERGESORT_H_