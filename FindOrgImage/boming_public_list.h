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

    // ������ָ��
    CLockableObject* m_pLock;
};


/************************************************************************
�������ܣ� ���캯���������������������һ���̻߳��������߶�д��
��������� CLockableObject::LOCK_TYPE lockType  --  ������
���������
����ֵ  ��
˵��    ��
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
�������ܣ� �����������ͷ�����ռ�õĶ��ڴ�
���������
���������
����ֵ  ��
˵��    ��
************************************************************************/
template<typename T>
TSListTemp<T>::~TSListTemp()
{
    delete m_pLock;
};


/************************************************************************
�������ܣ� ������ΪT�Ķ���ŵ�����β��
��������� const T& t  --  Ҫ�ŵ�����β���Ķ���
���������
����ֵ  �� 0  --  �ɹ�����һ��Ԫ��
           -1 --  ����Ԫ���ѵ����ֵ������ʧ��
˵��    ��
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
�������ܣ� ������ΪT�Ķ���ŵ�����ͷ��
��������� const T& t  --  Ҫ�ŵ�����β���Ķ���
���������
����ֵ  �� 0  --  �ɹ�����һ��Ԫ��
           -1 --  ����Ԫ���ѵ����ֵ������ʧ��
˵��    ��
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
�������ܣ� ������ͷ���Ľڵ㷵�ظ�������
���������
��������� T& t  --  ���ظ������ߵĽڵ�ֵ
����ֵ  �� 0  --  �ɹ�����һ���ڵ�
           -1 --  ����Ϊ��
		   -2 --  ��������Ϊ��
modify	: �����������Ϊ���ж�
˵��    ��
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
�������ܣ� ������β���Ľڵ㷵�ظ�������
���������
��������� T& t  --  ���ظ������ߵĽڵ�ֵ
����ֵ  �� 0  --  �ɹ�����һ���ڵ�
           -1 --  ����Ϊ��
˵��    ��
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
�������ܣ� �ж��������Ƿ���������ֵ��ȵĽڵ�
��������� const T& t  --  ҪѰ�ҵĽڵ�ֵ
���������
����ֵ  �� 0  --  ���������ֵ��ȵĽڵ�
           -1 --  �����������ֵ��ȵĽڵ�
˵��    ��
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
�������ܣ� �������Ƴ������ֵ��ȵĵ�һ���ڵ�
��������� const T& t  --  Ҫ�Ƴ��Ľڵ�ֵ
���������
����ֵ  ��
˵��    ��
************************************************************************/
template<typename T>
void TSListTemp<T>::remove(const T& t)
{
    MyLock(*m_pLock);

    m_list.remove(t);
    m_size = m_list.size();
};

/************************************************************************
�������ܣ� ��������Ľڵ����
���������
���������
����ֵ  �� ����Ľڵ����
˵��    ��
************************************************************************/
template<typename T>
unsigned int TSListTemp<T>::size()
{
    MyLock(*m_pLock);

    return m_size;
};


/************************************************************************
�������ܣ� ����������������Ԫ�ظ���
��������� unsigned int max_size  --  ������������Ԫ�ظ���
���������
����ֵ  ��
˵��    ��
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
�������ܣ� ��ȡ������������Ԫ�ظ���
���������
���������
����ֵ  �� ������������Ԫ�ظ���
˵��    ��
************************************************************************/
template<typename T>
unsigned int TSListTemp<T>::get_max_size()
{
    MyLock(*m_pLock);

    return m_maxSize;
};


/************************************************************************
�������ܣ� ��������еĽڵ�ֵ��ָ����ڴ�ָ�룬�ͷ����нڵ�ָ��Ķ��ڴ档
           ��ɾ������������Ԫ��
���������
���������
����ֵ  ��
˵��    �� ���������еĽڵ�ֵ�Ƕ��ڴ�ָ��ʱ���ܵ��ô˺������������
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
�������ܣ� ɾ�������е�����Ԫ��
���������
���������
����ֵ  ��
˵��    ��
************************************************************************/
template<typename T>
void TSListTemp<T>::clear_all()
{
    MyLock(*m_pLock);

    m_list.clear();
    m_size = 0;
};


// �����������
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
