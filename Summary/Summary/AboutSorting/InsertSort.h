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
    for (i = 0; i < len; i++)
    {
        k = i-1;
        if (Descending)
        {
           
            while (k>=0&&Pending[k] < Pending[i])
            {

            }
        }
        else
        {

        }
//         for (j = 0; j < i; j++)
//         {
//             while()
//         }
    }


}


#endif //_INSERTSORT_H_