
#include <time.h>
#include "Bubble.h"
#include "SelectSort.h"
#include "InsertSort.h"
#include "QuickSort.h"
#include "ShellSort.h"
#include "MergeSort.h"
#include "HeapSort.h"
#include "CountingSort.h"
#include "BucketSort.h"
#include "radixsort.h"
using namespace std;
const int testsize = 10;
int main()
{
    vector<int> vec;
    srand((unsigned int)time(NULL));
    vec.resize(testsize);
    int i = 0;
    int vec2[testsize]{ 0 };
    for (; i < testsize; i++)
    {
        vec[i] = rand() % 21 + 7;

        vec2[i] = rand() % 21+7;
        cout << (i + 1) << ".    " << vec2[i] << endl;
    }
    cout << "************************************************" << endl;
    cout << "************************************************" << endl;
    cout << "************************************************" << endl;
    cout << "************************************************" << endl;
    
    BucketSort(vec2,testsize);

    for (i = 0; i < testsize; i++)
    {
        cout << (i + 1) << ".    " << vec2[i] << endl;
    }
    cout << "************************************************" << endl;
    cout << "************************************************" << endl;
    cout << "************************************************" << endl;
    cout << "************************************************" << endl;
    system("pause");
}