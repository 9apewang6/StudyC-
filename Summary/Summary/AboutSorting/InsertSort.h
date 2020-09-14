#ifndef _INSERTSORT_H_
#define _INSERTSORT_H_

#include <iostream>
#include <vector>
using namespace std;
/*


*/
template<typename T>
void InsertSort(vector<T> &Pending, bool Descending = false)
{
    int i, j;
    int k = 0;
    int len = Pending.size();
    T temp;
    for (i = 0; i < len; i++)
    {
        k = i-1;
        if (Descending)
        {
           // 降序,大的在前， 
            temp = Pending[i];
            while (k>=0&&Pending[k] <temp)
            {
                Pending[k + 1] = Pending[k];
                k--;
            }
            Pending[k + 1] = temp;
        }
        else
        {
            temp = Pending[i];
            while (k >= 0 && Pending[k] > temp)
            {
                Pending[k + 1] = Pending[k];
                k--;
            }
            Pending[k + 1] = temp;
        }
    }
}
#endif //_INSERTSORT_H_