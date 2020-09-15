#ifndef _LINKLIST_H_
#define _LINKLIST_H_
#include "ListNode.h"
class LinkList
{
public:
    LinkList();
    LinkList(ListNode* head);
    LinkList(const LinkList& lk);
    LinkList(LinkList&& lk);
    LinkList& operator=(const LinkList& lk);

    bool isEmpty()const;
    int getlength()const;

    void clear(ListNode* head);

    void addElem(ListNode* node);
    void addElem(Element e);
    void addBack(Element e);

    void insertNode(ListNode* node, int index);
    void insertElem(Element e, int index);
    void deleteElem(Element e);

    void modify(Element e, Element dst);

    int search(Element e);

    void Descending();
    void Ascending();
    void reverse();

    void display()const;
private:
    void initLink(const LinkList& lk);

private:
    ListNode* head_;
    int len_;

};



#endif  //_LINKLIST_H_