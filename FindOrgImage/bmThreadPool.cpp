#include <windows.h>
#include "bmThreadPool.h"
#include <limits>

#define THREAD_POOL_LOG_INFO KEL_LOG_INFO
#define THREAD_POOL_LOG_DEBUG C_LOG_DEBUG
#define THREAD_POOL_LOG_ERROR KEL_LOG_ERROR
#define THREAD_POOL_LOG_WARN KEL_LOG_WARN

#define lock() m_mutex.lock()
#define unlock() m_mutex.unlock()

CbmThreadPool::CbmThreadPool(int ThreadCount) :
	m_isQuit(false)
{
	CreatThreads(ThreadCount);
}


CbmThreadPool::~CbmThreadPool()
{
	DestoryThreads();
}

void CbmThreadPool::CreatThreads(int ThreadCount)
{
	for (int i = 0; i < ThreadCount; i++)
	{
		std::thread* p_Thread = new std::thread(RunThread, this);
		if (nullptr == p_Thread)
		{
			printf("p_Thread null at %d / %d\r\n", i, ThreadCount);
			continue;
		}
		
		std::thread::id ThreadId = p_Thread->get_id();
//		::SetThreadPriority(p_Thread->native_handle(), THREAD_PRIORITY_BELOW_NORMAL);
		m_Threads[ThreadId] = p_Thread;

		//printf("creat ThreadId %u p_Thread %p\r\n", ThreadId, p_Thread);
	}
	m_IdleThreads = m_Threads;
	if (m_Threads.size() != ThreadCount)
	{
		printf("m_Threads count %d != %d\r\n", m_Threads.size(), ThreadCount);
	}
	else
	{
		printf("m_Threads count %d completed\r\n", ThreadCount);
	}
}

void CbmThreadPool::DestoryThreads()
{
	std::unique_lock<std::mutex> tlock(m_mutex);

	if (true == m_isQuit)
	{
		printf("m_isQuit true\r\n");
		return;
	}
	m_isQuit = true;

	while (true != m_Tasks.empty())
	{
		printf("m_Tasks size %d\r\n", m_Tasks.size());
		//ThreadPoolTask task = m_Tasks.front();
		std::pair<ThreadPoolTask, ThreadPoolTask> task = m_Tasks.front();
		m_Tasks.pop();

		unlock();
#ifdef USE_CPP11_FUNCTION
		if (task.second)
		{
			task.second();
		}
#else
		if (nullptr != task.second.run)
		{
			task.second.run(task.second.arg);
		}
		//task.exception(task.arg);
#endif
		lock();
	}

	if (true != m_IdleThreads.empty() || true != m_RunThreads.empty())
	{
		m_condition.notify_all();
		while (true != m_IdleThreads.empty() || true != m_RunThreads.empty())
		{
			m_condition.wait(tlock);
		}
	}

	for (auto i : m_Threads)
	{
		i.second->join();
	}
	m_Threads.clear();

	printf("destory Thread completed\r\n");
}

int CbmThreadPool::GetTaskCount()
{
	printf("M_task size [%d]",m_Tasks.size());
	return m_Tasks.size();
}

int CbmThreadPool::PushTask(const ThreadPoolTask& Task, const ThreadPoolTask& Exception)
{
#ifdef USE_CPP11_FUNCTION
	//printf("push task\r\n");
#else
	if (nullptr == Task.run)
	{
		THREAD_POOL_LOG_ERROR("Task.run null\r\n");
		return -1;
	}
	THREAD_POOL_LOG_INFO("push task %p, %p\r\n", Task.run, Task.arg);
#endif

	lock();
	if (true == m_isQuit)
	{
		printf("m_isQuit true\r\n");
		unlock();
		return -1;
	}

	static int s_TaskId = 1;
	int Task_id = s_TaskId;
	s_TaskId++;
	if (s_TaskId >= INT_MAX)
	{
		s_TaskId = 1;
	}

	//m_Tasks.push(Task);
	m_Tasks.push(std::pair<ThreadPoolTask, ThreadPoolTask>(Task, Exception));
	m_condition.notify_one();

	unlock();
	return Task_id;
}

void* CbmThreadPool::RunThread(void* arg)
{
	CbmThreadPool* pThis = (CbmThreadPool *)arg;

	pThis->DoRun();

	return nullptr;
}

void CbmThreadPool::DoRun()
{
	std::thread::id ThreadId = std::this_thread::get_id();
	//printf("Threads %u running ...\r\n", ThreadId);
	
	std::unique_lock<std::mutex> tlock(m_mutex);
	while (1)
	{
		while (true != m_isQuit && true == m_Tasks.empty())
		{
			m_condition.wait(tlock);
			//m_condition_timedwait
		}

		if (true == m_isQuit)
		{
			printf("quit Threads %u\r\n", ThreadId);

			m_IdleThreads.erase(ThreadId);
			
			if (true == m_RunThreads.empty() && true == m_IdleThreads.empty())
			{
				printf("quit all Threads completed in %u\r\n", ThreadId);
				m_condition.notify_one();
			}

			break;
		}

		//printf("ThreadPoolTask size [%u]\r\n", m_Tasks.size());
		//ThreadPoolTask task = m_Tasks.front();
		std::pair<ThreadPoolTask, ThreadPoolTask> task = m_Tasks.front();
		m_Tasks.pop();

		m_RunThreads[ThreadId] = m_IdleThreads[ThreadId];
		m_IdleThreads.erase(ThreadId);

		unlock();
#ifdef USE_CPP11_FUNCTION
		if (task.first)
		{
			//printf("run task in thread %u\r\n", ThreadId);
			task.first();
		}
		else
		{
			//printf("task false in thread %u\r\n", ThreadId);
		}
#else
		if (nullptr != task.first.run)
		{
			THREAD_POOL_LOG_INFO("run task %p, %p in thread %u\r\n", task.first.run, task.first.arg, ThreadId);
			task.first.run(task.first.arg);
		}
		else
		{
			THREAD_POOL_LOG_ERROR("task false in thread %u\r\n", ThreadId);
		}
#endif
		lock();

		m_IdleThreads[ThreadId] = m_RunThreads[ThreadId];
		m_RunThreads.erase(ThreadId);
	}

	printf("Threads %u close ...\r\n", ThreadId);
}

