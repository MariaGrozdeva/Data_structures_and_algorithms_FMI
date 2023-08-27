#pragma once

#include "InvokableTask.hpp"

#include <atomic>
#include <condition_variable>
#include <future>
#include <mutex>
#include <optional>
#include <queue>
#include <thread>
#include <utility>
#include <vector>

class TaskPool
{
public:
	explicit TaskPool(unsigned threadsCount = std::thread::hardware_concurrency())
	{
		try
		{
			for (size_t i = 0; i < threadsCount; i++)
			{
				m_threads.emplace_back(&TaskPool::workerThread, this);
			}
		}
		catch (...)
		{
			m_isRunning = false;
			m_haveWorkEvent.notify_all();
			throw;
		}
	}

	~TaskPool()
	{
		m_isRunning = false;
		m_haveWorkEvent.notify_all();
		for (auto&& t : m_threads)
		{
			t.join();
		}
	}

	TaskPool(const TaskPool&) = delete;
	TaskPool& operator=(const TaskPool&) = delete;
	TaskPool(TaskPool&&) = delete;
	TaskPool& operator=(TaskPool&&) = delete;

	template<typename FunctionType>
	void run(FunctionType&& f)
	{
		std::unique_lock lock(m_workMutex);
		m_tasksQueue.emplace(std::move(f));
		lock.unlock();

		m_haveWorkEvent.notify_one();
	}

private:
	std::atomic_bool m_isRunning = true;
	std::vector<std::thread> m_threads;
	std::queue<InvokableTask> m_tasksQueue;
	std::condition_variable m_haveWorkEvent;
	std::mutex m_workMutex;

	void workerThread()
	{
		while (m_isRunning)
		{
			std::unique_lock<std::mutex> lock(m_workMutex);
			m_haveWorkEvent.wait(lock, [this] { return !m_tasksQueue.empty() || !m_isRunning; });

			if (!m_isRunning)
			{
				return;
			}

			InvokableTask toExecute = std::move(m_tasksQueue.front()); 

			m_tasksQueue.pop();
			lock.unlock();

			toExecute();
		}
	}
};