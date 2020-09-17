#pragma once
#include "publicdef.h"

class Solutionof24 {
public:
    ListNode* func2(ListNode* head)
    {
        if (head == nullptr || head->next_ == nullptr)
        {
            return head;
        }
        ListNode* ret = func2(head->next_);
        head->next_->next_ = head;
        head->next_ = nullptr;
        return ret;
    }
    ListNode* reverseList(ListNode* head) {
        ListNode* pre = nullptr, *cur = head, *next = head;
        while (cur != nullptr)
        {
            next = cur->next_;
            cur->next_ = pre;
            pre = cur;
            cur = next;
        }
        return pre;
    }
};