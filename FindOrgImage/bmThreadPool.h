#pragma once
#include <mutex>
#include <queue>
#include <map>
#include <thread>

#define USE_CPP11_FUNCTION
#ifdef USE_CPP11_FUNCTION
#include <functional>
typedef std::function<void(void)> ThreadPoolTask;
#else
struct ThreadPoolTask
{
	void(*run)(void *arg);
	void *arg;

	ThreadPoolTask() : run(nullptr), arg(nullptr) {};
	ThreadPoolTask(const ThreadPoolTask& Task) { run = Task.run; arg = Task.arg; };

	void operator=(const ThreadPoolTask &D)
	{
		run = D.run;
		arg = D.arg;
	}
};
#endif

class CbmThreadPool
{
public:
	CbmThreadPool(int ThreadCount = 3);
	~CbmThreadPool();

#ifdef USE_CPP11_FUNCTION
// example for PushTask with c++11
// 	ThreadPoolTask Task = std::bind(TaskFunc);
// 	Task = std::bind(TaskFunc, (void*)1);
// 	Task = std::bind(TaskFunc, 1, 2.0, "string");
// 	Task = std::bind(&Class::TaskFunc, ClassObject, 1, 2.0, "string class");
// 	ThreadPool.PushTask(Task);
#endif
	int PushTask(const ThreadPoolTask& Task, const ThreadPoolTask& Exception = ThreadPoolTask());
	int GetTaskCount();

private:
	static void* RunThread(void* arg);
	void DoRun();
	
	void CreatThreads(int ThreadCount);
	void DestoryThreads();

private:
	std::mutex m_mutex;
	std::condition_variable m_condition;

	//std::queue<ThreadPoolTask> m_Tasks;
	std::queue<std::pair<ThreadPoolTask, ThreadPoolTask> > m_Tasks;

	std::map<std::thread::id, std::thread*> m_IdleThreads;
	std::map<std::thread::id, std::thread*> m_RunThreads;

	std::map<std::thread::id, std::thread*> m_Threads;

	bool m_isQuit;
};

