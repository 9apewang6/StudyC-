#pragma once
struct Element
{
    int val_;
    Element()
    {
        val_ = 0;
    }
    bool operator==(const Element &e)
    {
        return val_ == e.val_;
    }
};
struct ListNode
{
    Element e;
	ListNode* prev_;// previous 
	ListNode* next_; 
    ListNode() :e(Element()), prev_(nullptr), next_(nullptr) {};
	ListNode(Element val) :e(val), prev_(nullptr), next_(nullptr) {};
	ListNode(Element val, ListNode* next) :e(val), next_(nullptr) {};
	ListNode(Element val, ListNode* prev, ListNode* next) :e(val), prev_(prev), next_(next){};
};