#pragma once
#include "publicdef.h"
//  �ҵ��ཻ�ڵ�
class Solution {
public:
    // 1. ����
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        ListNode* tailA = headA;
        ListNode* tailB = headB;
        while (tailA != nullptr)
        {
            tailB = headB;
            while (tailB != nullptr)
            {
                if (tailB != tailA)
                {
                    tailB = tailB->next_;
                }
                else if (tailA == tailB)
                {
                    return tailB;
                }
            }
            tailA = tailA->next_;
        }
        return nullptr;
    }
    //2.��ϣ�� 
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        map<ListNode*, bool> hashmap;
        ListNode* tailA = headA;
        ListNode* tailB = headB;
        while (tailA != nullptr)
        {
            hashmap[tailA] = true;
            tailA = tailA->next_;
        }
        while (tailB != nullptr)
        {
            if (hashmap[tailB])return tailB;
            tailB = tailB->next_;
        }
        return nullptr;

    }
    // 3. ˫ָ��  
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        if (headB == nullptr || headA == nullptr)return nullptr;
        ListNode* tailA = headA;
        ListNode* tailB = headB;
        int atrans = 0;
        int btrans = 0;
        while (tailA != tailB)
        {
            tailA = tailA->next_;
            if (tailA == nullptr) {
                atrans++;
                tailA = headB;
            }
            tailB = tailB->next_;
            if (tailB == nullptr)
            {
                btrans++;
                tailB = headA;
            }
            if (atrans > 1 || btrans > 1)return nullptr;
        }
        return tailB;
    }

};