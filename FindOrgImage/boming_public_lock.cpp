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
                  互斥量父类
*********************************************************/
CLockableObject::CLockableObject()
{

}

CLockableObject::~CLockableObject()
{

}

/********************************************************
      利用线程mutex实现上锁，解锁的封装类
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
    该类对上锁，解锁操作进行封装
    在构造函数中上锁，在析构函数中解锁
    可使上锁，解锁操作成对进行
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
