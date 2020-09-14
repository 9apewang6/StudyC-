#ifndef _BUCKETSORT_H_
#define _BUCKETSORT_H_
#include <iostream>
#include <algorithm>
const int BUCKET_NUM = 10;
template<typename T>
struct listnode {
    explicit listnode(T i = 0) :mdata_(i), next_(nullptr) {};
    listnode* next_;
    T mdata_;
};
template<typename T>
listnode<T>* insert(listnode<T>* head, T val)
{
    listnode<T> dummynode;
    listnode<T> *newnode = new listnode<T>(val);
    listnode<T> *prev, *curr;
    dummynode.next_ = head;
    prev = &dummynode;
    curr = head;
    while (NULL != curr&& curr->mdata_ <= val)
    {
        prev = curr;
        curr = curr->next_;
    }
    newnode->next_ = curr;
    prev->next_ = newnode;
    return dummynode.next_;
}
template<typename T>
listnode<T>* merge(listnode<T>* head1, listnode<T>* head2)
{
    listnode<T> dummynode;
    listnode<T>* dummy = &dummynode;
    while (head1 != nullptr&&head2 != nullptr)
    {
        if (head1->mdata_ <= head2->mdata_)
        {
            dummy->next_ = head1;
            head1 = head1->next_;
        }
        else
        {
            dummy->next_ = head2;
            head2 = head2->next_;
        }
        dummy = dummy->next_;
    }
    if (head1 != nullptr)dummy->next_ = head1;
    if (head2 != nullptr)dummy->next_ = head2;
    return dummynode.next_;

}

template<typename T>
void BucketSort(T arr[], int len)
{
    vector<listnode<T>*> buckets(BUCKET_NUM,(listnode<T>*)(0));
    for (int i = 0; i < len; i++) 
    {
        int index = arr[i] / BUCKET_NUM;
        listnode<T> *head = buckets.at(index);
        buckets.at(index) = insert(head,arr[i]);

    }
    listnode<T>* head = buckets.at(0);
    for (int i = 1; i < BUCKET_NUM; i++)
    {
        head = merge(head, buckets.at(i));
    }
    for (int i = 0; i < len; i++)
    {
        arr[i] = head->mdata_;
        head = head->next_;
    }
}


#endif //_BUCKETSORT_H_