/*	File name: boming_public_lock.h
 *
 *	boming_public_lock implementation
 *
 *	CCopyright (C) boming
 *	
 *	Created @ ylshan 2018-3-23
 */

#ifndef BOMING_PUBLIC_LOCK_H_
#define BOMING_PUBLIC_LOCK_H_

//#include <afxmt.h>
#include <mutex>
using namespace std;
class  CLockableObject
{
public:
    CLockableObject();
    virtual ~CLockableObject();

    virtual void Lock() = 0;

    virtual void Unlock() = 0;
};

class CMyMutex: public CLockableObject
{
public:
    CMyMutex();
    virtual ~CMyMutex();

    virtual void Lock();
    virtual void Unlock();
private:
    //CMutex m_tMutex;
	mutex m_tMutex;
};

class CLock
{
public:
    CLock(CLockableObject &LockableObject);
    ~CLock();

private:
    CLockableObject &m_LockableObject;

private:
    CLock(const CLock&);//½ûÖ¹Ëø¿½±´
    CLock& operator =(const CLock &); //½ûÖ¹¸³Öµ
};

#define MyLock(MyMutex)   CLock mylock(MyMutex)

#endif

