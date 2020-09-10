#pragma once
struct ListNode
{
	int val_;
	ListNode* prev_;// previous 
	ListNode* next_; 
	ListNode(int val) :val_(val), prev_(nullptr), next_(nullptr) {};
	ListNode(int val, ListNode* next) :val_(val), next_(nullptr) {};
	ListNode(int val, ListNode* prev, ListNode* next) :val_(val), prev_(prev), next_(next)
	{};
};