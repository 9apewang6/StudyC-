#ifndef _FINDMINK_H_
#define _FINDMINK_H_
#include "publicdef.h"
class Solutionof40 {
public:
    // func1 √∞≈›≈≈–Ú £¨ n^2 ,≥¨ ± 
    vector<int> getLeastNumbers(vector<int>& arr, int k) {
        vector<int> ans;
        if (k <= 0)return ans;     
        int i, j;
        int len = arr.size();
        ans.resize(min(len,k));
        for (i = 0; i <len; i++)
        {
            for (j = 0; j < len - i-1; j++)
            {
                if (arr[j] < arr[j + 1])
                {
                    swap(arr[j],arr[j+1]);
                }
            }
           ans.at(i) = arr[len - i - 1];
           if ((i + 1) == k)return ans;
        }
        return ans;

    }

    int partition(vector<int>& vec, int low, int high)
    {
        int pivot = vec[low];
        while (low < high)
        {
            while (low<high&&vec[high]>=pivot)
            {
                high--;
            }
            vec[low] = vec[high];
            while (low < high&&vec[low] <= pivot)
            {
                low++;
            }
            vec[high] = vec[low];
        }
        vec[low] = pivot;
        return low;
    }
    void quicksort(vector<int>& vec, int low, int high)
    {
        if (low < high)
        {
            int pivot = partition(vec, low, high);
            quicksort(vec,  0, pivot - 1);
            quicksort(vec, pivot + 1, high);
        }
    }
    vector<int> getLeastNumbers2(vector<int>& arr, int k)
    {
        int len = arr.size();
       //quicksort(arr, 0,len-1);
        sort(arr.begin(), arr.end());
        if (k >= len) { return arr; }

        vector<int> ans;
        ans.resize(k);
        for (int i = 0; i < k; i++)
        {
            ans[i] = arr[i];
        }
      
        return ans;
    }
    vector<int > getLeastNumbers3(vector<int>& arr, int k)
    {
        vector<int> vec(k,0);
        if (k == 0)return vec;
        priority_queue<int> Q;
        for (int i = 0; i < k; ++i)Q.push(arr[i]);
        for (int i = k; i < (int)arr.size(); ++i)
        {
            if (Q.top() > arr[i])
            {
                Q.pop();
                Q.push(arr[i]);
            }
        }
        for (int i = 0; i < k; ++i)
        {
            vec[i] = Q.top();
            Q.pop();
        }
        return vec;
    }
    void test()
    {
        std::string inputvec;
        vector<int> inp;
        vector<int> ans;
        cout << "please input a vector to test the alg ."
            << "such as [1,3,5]" << endl;
        char marks;
        int k;
        while (getline(cin, inputvec))
        {
            inp = stringTovector(inputvec);
            cout << "excute..." << endl;
            cin >> k;
            ans = getLeastNumbers2(inp,k);
            string anstring = vectorTostring(ans);
            cout << "answer is " << anstring << endl;
            cout << " do you want to continue ... (y/n)" << endl;
            cin.get();
            cin.get(marks);
            if (marks != 'y')break;
            cin.get();

        }
    }
};


#endif //_FINDMINK_H_