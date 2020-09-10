
#include <time.h>
#include "Bubble.h"
#include "SelectSort.h"


using namespace std;
const int testsize = 50;
int main()
{
    vector<int> vec;
    srand((unsigned int)time(NULL));
    vec.resize(testsize);
    int i = 0;
    for (; i < testsize; i++)
    {
        vec[i] = rand() % 21;
        cout << (i + 1) << ".    " << vec[i] << endl;
    }
    cout << "************************************************" << endl;
    cout << "************************************************" << endl;
    cout << "************************************************" << endl;
    cout << "************************************************" << endl;
    
    SelectSort(vec,false);

    for (i = 0; i < testsize; i++)
    {
        cout << (i + 1) << ".    " << vec[i] << endl;
    }
    cout << "************************************************" << endl;
    cout << "************************************************" << endl;
    cout << "************************************************" << endl;
    cout << "************************************************" << endl;
    system("pause");
}