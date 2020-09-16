#pragma once
#include "publicdef.h"
class Solutionof22 {
public:
    ListNode* getKthFromEnd(ListNode* head, int k) 
    {
        ListNode* fasttail = head;
        ListNode* slowtail = head;
        while (fasttail&&k > 0)
        {
            k--;
            fasttail = fasttail->next_;
        }
        while (fasttail != nullptr)
        {
            slowtail = slowtail->next_;
            fasttail = fasttail->next_;
        }
        return slowtail;
    }
    void test()
    {
        string input_vec;
        char youcontinue;
        int pos=0;
        while (getline(cin, input_vec)) {
            trimleftspace(input_vec);
            trimrightspace(input_vec);

            ListNode *testlist = stringTolistnode(input_vec);

            cout << " select kth from end pos :" << endl;
            cin >> pos;
            cin.get();
            string str = listnodetostring(getKthFromEnd(testlist,pos));
            cout << str << endl;
            cout << "do you want to continue...(y/n)" << endl;
            cin.get(youcontinue);
            if (youcontinue != 'y')break;
            cin.get();
        }
    }
};