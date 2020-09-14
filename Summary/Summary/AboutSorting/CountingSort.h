#ifndef _COUNTINGSORT_H_
#define _COUNTINGSORT_H_
#include <algorithm>
#include <iostream>
using namespace std;

template<typename T>
// ���� ����
void countingsort(T arr[], int len)
{
    int* countarr = new int[100];
    int* temp = new int[len] {0};
    int i, j, k;
    for (k = 0; k < 100; k++)
    {
        countarr[k] = 0;
    }
    for (i = 0; i < len; i++)
    {
        countarr[arr[i]]++;
    }
    for (k = 1; k < 100; k++)
    {
        countarr[k] += countarr[k - 1];
    }
    for (j = len; j > 0; j--)
    {
        countarr[arr[j - 1]]--; // �ȼ��� �����Խ����
        temp[countarr[arr[j - 1]]] = arr[j - 1];    
    }
    for (i = 0; i < len; i++)
    {
        arr[i] = temp[i];
    }
    delete[] temp;
    delete[] countarr;
}


#endif //_COUNTINGSORT_H_