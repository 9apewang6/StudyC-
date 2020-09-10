/*!
 * \file SelectSort.h
 * 
 * \author wang
 * \date ���� 2020
 *
 * 
 */
#include <iostream>
#include <vector>
using std::vector;
/*
ѡ������
ѡ���������� ð������  
ѡ����ǰ�� ð���ں�
*/
template<typename T>
void SelectSort(vector<T> &Pending, bool Descending = false)
{
    int i, j;
    int minormax = 0;
    for (i = 0; i < Pending.size() - 1; i++)
    {
        minormax = i;
        for (j = i + 1; j < Pending.size(); j++) 
        {
            if (Descending)
            {
                if (Pending[minormax] < Pending[j])
                    minormax = j;
            }
            else
            {
                if (Pending[minormax] > Pending[j])
                    minormax = j;
            }
            swap(Pending[minormax], Pending[i]);
        }
    }

}