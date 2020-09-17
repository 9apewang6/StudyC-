#pragma once
#include "publicdef.h"
class Solutionp234 {
public:
    // ╩ьнд 
    bool isPalindrome(ListNode* head) {
        if (head == nullptr)return true;
        ListNode* left = head;
        ListNode* right = head;
        int len = 1;
        queue<int> leftqueue;
        stack<int> rightstack;
        while (right != nullptr)
        {
            len++;
            if (len % 2 == 0)
            {
                leftqueue.push(left->val);
                left = left->next_;
            }

            rightstack.push(right->val);
            right = right->next_;
        }   
        
        while (!leftqueue.empty())
        {
            if (leftqueue.front() == rightstack.top())
            {
                leftqueue.pop();
                rightstack.pop();
            }
            else
            {
                return false;
            }
        }
        return true;
    }
};