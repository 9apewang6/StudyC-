#ifndef _MIDDLENODE_H_
#define _MIDDLENODE_H_
#include "publicdef.h"
class GetMidNode {
public:
    ListNode* middleNode(ListNode* head) {
        ListNode* tail = head;
        ListNode* setail = head;
        int idx = 0;
        while (tail != nullptr)
        {
            idx++;
            if (idx % 2 == 0)
            {
                setail = setail->next_;
            }
            tail = tail->next_;           
        }
        return setail;
    }
    void test()
    {
        string input_vec;
        char youcontinue;
        while (getline(cin, input_vec)) {
            trimleftspace(input_vec);
            trimrightspace(input_vec);

            ListNode *testlist = stringTolistnode(input_vec);
            string str = listnodetostring(middleNode(testlist));
            cout << str << endl;
            cout << "do you want to continue...(y/n)" << endl;
            cin.get(youcontinue);
            if (youcontinue != 'y')break;
            cin.get();
        }
    }
};


#endif //_MIDDLENODE_H_