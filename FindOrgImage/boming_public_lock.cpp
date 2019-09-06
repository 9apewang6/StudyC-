/*	File name: boming_public_lock.h
 *
 *	boming_public_lock implementation
 *
 *	CCopyright (C) boming
 *	
 *	Created @ ylshan 2018-3-23
 */

#include "boming_public_lock.h"

using namespace std;

/********************************************************
                  ����������
*********************************************************/
CLockableObject::CLockableObject()
{

}

CLockableObject::~CLockableObject()
{

}

/********************************************************
      �����߳�mutexʵ�������������ķ�װ��
*********************************************************/

CMyMutex::CMyMutex()
{

}

CMyMutex::~CMyMutex()
{
    
}

void CMyMutex::Lock()
{
	m_tMutex.lock();
}

void CMyMutex::Unlock()
{
    m_tMutex.unlock();
}

/********************************************************
    ����������������������з�װ
    �ڹ��캯���������������������н���
    ��ʹ���������������ɶԽ���
*********************************************************/


CLock::CLock(CLockableObject &LockableObject)
    :m_LockableObject(LockableObject)
{
    m_LockableObject.Lock();
}

CLock::~CLock()
{
    m_LockableObject.Unlock();
}
