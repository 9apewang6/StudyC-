#pragma once
#include "publicdef.h"
// 设计一个栈
// 栈 LIFO
//  队列 FIFO
// 两个队列实现栈 
class MinStack2 {
public:
    /** initialize your data structure here. */
    MinStack2() {       
        len_ = 0;
    }

    void push(int x) {
        data_.push_back(x);
        data.push(x);
        len_++;
    }

    void pop(){
        if (len_ > 0)data_.erase(std::next(data_.end(),-1));
        len_--;
    }
    int top() {
      if(len_>0)return  data_.back();
      else return -1;
    }

    int getMin() {
        if (len_ == 0)return -1;
        int minvalue = data_.at(0);
        for (int i = 0; i < data_.size(); i++)
        {
            if (minvalue > data_.at(i))
            {
                minvalue = data_.at(i);
            }
        }
        return minvalue;
    }
private:
    vector<int> data_;
    queue<int> data;
    int len_;
 };

class MinStack
{
public:
    MinStack()
    {
        assiststack.push(INT_MAX);
    }
    void push(int x)
    {
        assiststack.push(min(assiststack.top(),x));
        data_.push(x);
    }
    int top()
    {
        if (data_.size() > 0) return data_.top();
        else return -1;
    }
    void pop()
    {
        data_.pop();
        assiststack.pop();
    }
    int getMin()
    {
        return assiststack.top();
    }
private:
    stack<int > data_;
    stack<int> assiststack;
};


class MyStack {
public:
    /** Initialize your data structure here. */
    MyStack() {

    }

    /** Push element x onto stack. */
    void push(int x) {
        m_stack.push(x);
        if (temp_stack.empty())
        {
            while (!m_stack.empty())
            {
                temp_stack.push(m_stack.front());
                m_stack.pop();
            }

        }
        else if (!temp_stack.empty())
        {
            while (!temp_stack.empty())
            {
                m_stack.push(temp_stack.front());
                temp_stack.pop();

            }
            while (!m_stack.empty())
            {
                temp_stack.push(m_stack.front());
                m_stack.pop();
            }
        }
    }

    /** Removes the element on top of the stack and returns that element. */
    int pop() {
        if (temp_stack.empty())return 0;
        int value = temp_stack.front();
        temp_stack.pop();
        return value;
    }


    // 		void reversequeue(queue<int>& thisqueue)
    // 		{
    // 			int *p = new int[thisqueue.size()];
    // 			int i = 0;
    // 			while (!thisqueue.empty())
    // 			{
    // 				p[i] = thisqueue.front();
    // 				thisqueue.pop();
    // 				i++;
    // 			}
    // 			i--;
    // 			for (int j = i; j >=0; j--)
    // 			{
    // 				thisqueue.push(p[j]);
    // 			}
    // 			delete[] p;
    // 			p = nullptr;
    // 		}

    /** Get the top element. */
    int top() {
        if (temp_stack.empty())return 0;

        return temp_stack.front();
    }

    /** Returns whether the stack is empty. */
    bool empty() {
        return getsize() == 0;
    }

    int getsize()
    {
        return temp_stack.size() + m_stack.size();
    }
private:
    queue<int> m_stack;
    queue<int> temp_stack;
};

/**
* Your MinStack object will be instantiated and called as such:
* MinStack* obj = new MinStack();
* obj->push(x);
* obj->pop();
* int param_3 = obj->top();
* int param_4 = obj->getMin();
*/

/*
["MinStack","push","push","push","getMin","pop","top","getMin"]
[[],[-2],[0],[-3],[],[],[],[]]

输出：
[null,null,null,null,-3,null,0,-2]

解释：
MinStack minStack = new MinStack();
minStack.push(-2);
minStack.push(0);
minStack.push(-3);
minStack.getMin();   --> 返回 -3.
minStack.pop();
minStack.top();      --> 返回 0.
minStack.getMin();   --> 返回 -2.
*/