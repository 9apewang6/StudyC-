#include <iostream>
#include <algorithm>
#include <vector>
#include "Linklist.h"
using namespace std;
LinkList::LinkList():head_(nullptr),len_(0)
{

}

LinkList::LinkList(ListNode* head) : head_(head)
{
    ListNode* tail = head_;
    while (tail != nullptr)
    {
        len_++;
        tail = tail->next_;
    }

}

void LinkList::initLink(const LinkList& lk)
{
    head_ = lk.head_;
    len_ = lk.len_;
}

LinkList::LinkList(const LinkList& lk)
{
    initLink(lk);
}
LinkList::LinkList(LinkList&& lk)
{
    initLink(lk);
    
    clear(lk.head_);
    lk.len_ = 0;
}

LinkList& LinkList::operator=(const LinkList& lk)
{
    if (&lk != this)
        return *this;
    clear(head_);
    initLink(lk);
    return *this;
}

bool LinkList::isEmpty()const
{
    return len_ > 0;
}
int LinkList::getlength()const
{
    return len_;
}
void LinkList::clear(ListNode* head)
{
    if (head != nullptr)
    {
        ListNode *tail = head;
        while (tail != nullptr)
        {
            ListNode* tmp = tail;
            tail = tail->next_;
            delete tmp;
        }
    }
    
}
void LinkList::addElem(ListNode* node)
{
    //直接插在头部 
    if (head_ == nullptr)
    {
        head_ = node;
        len_++;
        return;
    }
    node->next_ = head_;
    head_ = node;
    len_++;
}
void LinkList::addBack(Element e)
{
    if (head_ == nullptr)
    {
        ListNode *node = new ListNode(e);
        head_ = node;
        len_++;
        return;
    }
    ListNode* tail = head_;
    while (tail->next_ != nullptr)
        tail = tail->next_;
    ListNode* newnode = new ListNode(e);
    tail->next_ = newnode;
    len_++;
}
void LinkList::addElem(Element e)
{
    if (head_ == nullptr)
    {
        head_ = new ListNode(e);
        len_++;
        return;
    }
    ListNode* newnode = new ListNode(e);
    newnode->next_ = head_;
    head_ = newnode;
    len_++;
}
void LinkList::insertElem(Element e, int index)
{
    if (index <= 0)
    {
        addElem(e);
        return;
    }
    ListNode* tail = head_;
    ListNode* lasttail = nullptr;
    while (tail != nullptr)
    {
        if (index == 0)
        {
            ListNode* newnode = new ListNode(e);
            newnode->next_ = tail;
            lasttail->next_ = newnode;
            len_++;
        }
        index--;
        lasttail = tail;
        tail = tail->next_;
    }
    if (index >= 0) {
        ListNode* newnode = new ListNode(e);
        newnode->next_ = tail;
        lasttail->next_ = newnode;
        len_++;
    }

}
void LinkList::insertNode(ListNode* node, int index)
{
    if (index <= 0)
    {
        addElem(node);
        len_++;
        return;
    }
    ListNode* tail = head_;
    ListNode* lasttail = nullptr;
    while (tail != nullptr)
    {
        if (index == 0)
        {   
            node->next_ = tail;
            lasttail->next_ = node;
            len_++;
        }
        index--;
        lasttail = tail;
        tail = tail->next_;
    }
    if (index >= 0)
    {
        node->next_ = tail;
        lasttail->next_ = node;
        len_++;
    }
}
void LinkList::deleteElem(Element e)
{
    if (len_ == 0)
        return;
    ListNode* tail = head_;
    ListNode* last = nullptr;
    while (tail != nullptr)
    {
        if (tail->e == e)
        {
            // delete tail;
            if (last != nullptr)
            {
                last->next_ = tail->next_;
            }
            else
            {
                head_ = head_->next_;
            }
            ListNode* tmp = tail;
            tail = tail->next_;
            delete tmp;
            tmp = nullptr;
            len_--;
            return;
        }
        last = tail;
        tail = tail->next_;
    }
}

void LinkList::modify(Element e, Element dst)
{
    if (len_ == 0)
        return;
    ListNode* tail = head_;
    while (tail != nullptr)
    {
        if (tail->e == e)
        {
            // delete tail;
            tail->e = dst;
        }
        tail = tail->next_;
    }
}

int LinkList::search(Element e)
{
    if (len_ == 0)
        return NULL;
    ListNode* tail = head_;
    int idx=0;
    while (tail != nullptr)
    {
        idx++;
        if (tail->e == e)
        {
            // delete tail;
            return idx;
        }
        tail = tail->next_;
    }
    return -1;
}
//冒泡排序，降序 
void LinkList::Descending()
{
    //ListNode ans;
    ListNode* tail = head_;
    ListNode* tail2 = head_;
    
    while (tail->next_ != nullptr)
    {
        while (tail2->next_ != nullptr)
        {
            if (tail2->e < tail2->next_->e)
            {
                std::swap(tail2->e, tail2->next_->e);     
            }
            tail2 = tail2->next_;
        }   
        tail2 = head_;
        tail = tail->next_;
    }


}
void LinkList::Ascending()
{
    ListNode* tail = head_;
    ListNode* tail2 = head_;

    while (tail->next_ != nullptr)
    {
        while (tail2->next_ != nullptr)
        {
            if (tail2->e > tail2->next_->e)
            {
                std::swap(tail2->e, tail2->next_->e);
            }
            tail2 = tail2->next_;
        }
        tail2 = head_;
        tail = tail->next_;
    }
}

void LinkList::reverse()
{
    ListNode* pre=nullptr, *cur=head_, *next=head_->next_;
    while (cur != nullptr)
    {
        next = cur->next_;

        cur->next_ = pre;

        pre = cur;

        cur = next;
    }
    head_ = pre;
}

void LinkList::display()const
{
    ListNode* tail = head_;
    while (tail != nullptr)
    {
        cout << tail->e.val_ << "-->";
        tail = tail->next_;
    }
    cout <<"NULL"<< endl;
}