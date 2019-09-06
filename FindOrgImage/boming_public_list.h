/*	File name: boming_public_list.h
 *
 *	list thread safe implementation
 *
 *	CCopyright (C) boming
 *	
 *	Created @  ylshan 2018-3-23
 */

#ifndef BOMING_PUBLIC_LIST_H
#define BOMING_PUBLIC_LIST_H

#include <list>
#include <string>
#include "boming_public_lock.h"

using namespace std;

//------------------------------------------------------------------------
//------------------------------------------------------------------------
template<typename T>
class TSListTemp
{
public:
    typedef typename list<T>::iterator iterator;
    typedef typename list<T>::value_type value_type;
    typedef list<T> inner_type;

    TSListTemp(unsigned int maxSize = 0);
    virtual ~TSListTemp();

    int push_back(const T&);
    int push_front(const T&);
    int pop_front(T&);
    int pop_back(T&);
	T front();

    int find(const T&);
    void remove(const T&);

    void set_max_size(unsigned int max_size);
    unsigned int get_max_size();
    unsigned int size();

    void free_mem_and_clear();
    void clear_all();

protected:
	list<T> m_list;
    unsigned int m_size;
    unsigned int m_maxSize;

    // 互斥锁指针
    CLockableObject* m_pLock;
};


/************************************************************************
函数功能： 构造函数。根据输入参数，建造一个线程互斥锁或者读写锁
输入参数： CLockableObject::LOCK_TYPE lockType  --  锁类型
输出参数：
返回值  ：
说明    ：
************************************************************************/
template<typename T>
TSListTemp<T>::TSListTemp(unsigned int max_size)
: m_size(0), m_maxSize(max_size), m_pLock(NULL)
{
    if (m_maxSize == 0)
    {
        m_maxSize = INT_MAX;
    }

	m_pLock = new CMyMutex();
};


/************************************************************************
函数功能： 析构函数。释放锁所占用的堆内存
输入参数：
输出参数：
返回值  ：
说明    ：
************************************************************************/
template<typename T>
TSListTemp<T>::~TSListTemp()
{
    delete m_pLock;
};


/************************************************************************
函数功能： 把类型为T的对象放到链表尾部
输入参数： const T& t  --  要放到链表尾部的对象
输出参数：
返回值  ： 0  --  成功插入一个元素
           -1 --  链表元素已到最大值，插入失败
说明    ：
************************************************************************/
template<typename T>
int TSListTemp<T>::push_back(const T& t)
{
    MyLock(*m_pLock);

    if(m_size < m_maxSize)
    {
        m_list.push_back(t);
        m_size++;

        return 0;
    }

    return -1;
};


/************************************************************************
函数功能： 把类型为T的对象放到链表头部
输入参数： const T& t  --  要放到链表尾部的对象
输出参数：
返回值  ： 0  --  成功插入一个元素
           -1 --  链表元素已到最大值，插入失败
说明    ：
************************************************************************/
template<typename T>
int TSListTemp<T>::push_front(const T& t)
{
    MyLock(*m_pLock);

    if(m_size < m_maxSize)
    {
        m_list.push_front(t);
        m_size++;

        return 0;
    }

    return -1;
};


/************************************************************************
函数功能： 把链表头部的节点返回给调用者
输入参数：
输出参数： T& t  --  返回给调用者的节点值
返回值  ： 0  --  成功返回一个节点
           -1 --  链表为空
		   -2 --  出队数据为空
modify	: 加入出队数据为空判断
说明    ：
************************************************************************/
template<typename T>
int TSListTemp<T>::pop_front(T& t)
{
    MyLock(*m_pLock);

    if(m_list.empty() == false)
    {
        t = m_list.front();
        m_list.pop_front();
        m_size--;
	        return 0;
    }

    return -1;
};

template<typename T>
T TSListTemp<T>::front()
{
	MyLock(*m_pLock);

	if(m_list.empty() == false)
	{
		return m_list.front();
	}

	return T();
};

/************************************************************************
函数功能： 把链表尾部的节点返回给调用者
输入参数：
输出参数： T& t  --  返回给调用者的节点值
返回值  ： 0  --  成功返回一个节点
           -1 --  链表为空
说明    ：
************************************************************************/
template<typename T>
int TSListTemp<T>::pop_back(T& t)
{
    MyLock(*m_pLock);

    if(m_list.empty() == false)
    {
        t = m_list.back();
        m_list.pop_back();
        m_size--;

        return 0;
    }

    return -1;
};


/************************************************************************
函数功能： 判断链表中是否存在与给定值相等的节点
输入参数： const T& t  --  要寻找的节点值
输出参数：
返回值  ： 0  --  存在与给定值相等的节点
           -1 --  不存在与给定值相等的节点
说明    ：
************************************************************************/
template<typename T>
int TSListTemp<T>::find(const T& t)
{
    MyLock(*m_pLock);

	typename list<T>::iterator it = ::find(m_list.begin(), m_list.end(), t);

    if(it != m_list.end())
        return 0;     //found
    else
        return -1;      //not found
};


/************************************************************************
函数功能： 从链表移除与给定值相等的第一个节点
输入参数： const T& t  --  要移除的节点值
输出参数：
返回值  ：
说明    ：
************************************************************************/
template<typename T>
void TSListTemp<T>::remove(const T& t)
{
    MyLock(*m_pLock);

    m_list.remove(t);
    m_size = m_list.size();
};

/************************************************************************
函数功能： 返回链表的节点个数
输入参数：
输出参数：
返回值  ： 链表的节点个数
说明    ：
************************************************************************/
template<typename T>
unsigned int TSListTemp<T>::size()
{
    MyLock(*m_pLock);

    return m_size;
};


/************************************************************************
函数功能： 设置链表最大允许的元素个数
输入参数： unsigned int max_size  --  链表最大允许的元素个数
输出参数：
返回值  ：
说明    ：
************************************************************************/
template<typename T>
void TSListTemp<T>::set_max_size(unsigned int max_size)
{
    MyLock(*m_pLock);

    if(max_size == 0)
    {
        m_maxSize = INT_MAX;
    }
    else
    {
        m_maxSize = max_size;
    }
};

/************************************************************************
函数功能： 获取链表最大允许的元素个数
输入参数：
输出参数：
返回值  ： 链表最大允许的元素个数
说明    ：
************************************************************************/
template<typename T>
unsigned int TSListTemp<T>::get_max_size()
{
    MyLock(*m_pLock);

    return m_maxSize;
};


/************************************************************************
函数功能： 如果链表中的节点值是指向堆内存指针，释放所有节点指向的堆内存。
           并删除链接中所有元素
输入参数：
输出参数：
返回值  ：
说明    ： 仅当链表中的节点值是堆内存指针时才能调用此函数，否则出错。
************************************************************************/
template<typename T>
void TSListTemp<T>::free_mem_and_clear()
{
    MyLock(*m_pLock);

    for(typename list<T>::iterator it = m_list.begin(); it!= m_list.end(); it++)
    {
        delete (T)*it;
        *it = NULL;
    }
	
    m_list.clear();
	m_size = 0;
};


/************************************************************************
函数功能： 删除链表中的所有元素
输入参数：
输出参数：
返回值  ：
说明    ：
************************************************************************/
template<typename T>
void TSListTemp<T>::clear_all()
{
    MyLock(*m_pLock);

    m_list.clear();
    m_size = 0;
};


// 描述共享队列
template<typename T>
class TAppTSList : public TSListTemp<T>
{
public:
	TAppTSList();
    TAppTSList(const char* pName, unsigned int maxSize = 0);
    int Enqueue(const T& t);
	int EnqueueFront(const T& t);
    const char* GetName();
	void RequstMem(T* t);

protected:
    const string m_strName;

};

template<typename T>
TAppTSList<T>::TAppTSList()
: TSListTemp<T>(0),
  m_strName("List")
{
	int i = 0;
};

template<typename T>
TAppTSList<T>::TAppTSList(const char* pName, unsigned int maxSize)
: TSListTemp<T>(maxSize),
  m_strName(pName)
{

};

template<typename T>
int TAppTSList<T>::Enqueue(const T& t)
{
    int ret = this->push_back(t);

    if (ret != 0)
    {
        delete t;
    }

    return ret;
};

template<typename T>
int TAppTSList<T>::EnqueueFront(const T& t)
{
	int ret = this->push_front(t);

	if (ret != 0)
	{
		delete t;
	}

	return ret;
};

template<typename T>
const char* TAppTSList<T>::GetName()
{
    return m_strName.c_str();
};

#endif
