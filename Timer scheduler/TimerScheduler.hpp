#pragma once

#include "SchedulableTask.hpp"
#include "TaskPool.hpp"

#include <map>

class TimerScheduler
{
public:
	explicit TimerScheduler(unsigned threadsCount = std::thread::hardware_concurrency())
    : m_taskPool{ threadsCount }
	{}

	~TimerScheduler()
	{
        m_isRunning = false;
        m_thereAreTasksToExec.notify_all();
        m_schedulerThread.join();
	}

	TimerScheduler(const TimerScheduler&) = delete;
	TimerScheduler& operator=(const TimerScheduler&) = delete;
	TimerScheduler(TimerScheduler&&) = delete;
	TimerScheduler& operator=(TimerScheduler&&) = delete;

    size_t currentlyScheduled() const
    {
        std::scoped_lock<std::mutex> lock(m_executeTasksMutex);
        return m_tasks.size();
    }

    bool updateInterval(const std::string& id, std::chrono::steady_clock::duration newInterval)
    {
        std::unique_lock<std::mutex> lock(m_executeTasksMutex);

        auto taskToBeUpdatedIter = taskIterator(id);
        if (taskToBeUpdatedIter == m_tasks.end() || !taskToBeUpdatedIter->second.interval().has_value())
        {
            return false;
        }
        
        auto taskToBeUpdatedOldInterval = taskToBeUpdatedIter->second.interval().value();
        auto taskNextStartTime = taskToBeUpdatedIter->first - taskToBeUpdatedOldInterval;
        auto now = std::chrono::steady_clock::now();
        while (now > taskNextStartTime)
        {
            taskNextStartTime += newInterval; // keep the scheduling with a fixed sample rate
        }

        taskToBeUpdatedIter->second.setInterval(newInterval);
        m_tasks.emplace(std::move(taskNextStartTime), std::move(taskToBeUpdatedIter->second));
        m_tasks.erase(taskToBeUpdatedIter);

        lock.unlock();

        m_thereAreTasksToExec.notify_one();
        return true;
    }

    bool cancelTimer(const std::string& id)
    {
        std::scoped_lock<std::mutex> lock(m_executeTasksMutex);

        auto currentTaskIter = taskIterator(id);
        if (currentTaskIter == m_tasks.end()) // the task has already finished or just doesn't exist
        {
            return false;
        }
        m_tasks.erase(currentTaskIter);
        return true;
    }

	void start()
	{
        try
        {
            m_schedulerThread = std::thread([this]
                {
                    while (m_isRunning)
                    {
                        std::unique_lock lock(m_executeTasksMutex);
                        m_thereAreTasksToExec.wait(lock, [this] { return !m_tasks.empty() || !m_isRunning; });

                        if (!m_isRunning)
                        {
                            return;
                        }

                        auto nextTaskTimepoint = m_tasks.begin()->first;
                        if (m_thereAreTasksToExec.wait_until(lock, nextTaskTimepoint) == std::cv_status::no_timeout)
                        {
                            continue;
                        }

                        executeTasks();
                    }
                });
        }
        catch (...)
        {
            m_isRunning = false;
            m_thereAreTasksToExec.notify_all();
            throw;
        }
	}

    template <typename TaskFunction>
    std::future<std::invoke_result_t<TaskFunction>> scheduleSingle(std::chrono::steady_clock::duration&& timeout, TaskFunction&& func)
    {
        auto invokableTask = [t = std::forward<TaskFunction>(func)] { return t(); };

        std::packaged_task<std::invoke_result_t<TaskFunction>()> taskWrapper(invokableTask);
        std::future<std::invoke_result_t<TaskFunction>> future = taskWrapper.get_future();

        addTask(std::move(std::chrono::steady_clock::now() + timeout), SchedulableTask(std::move(taskWrapper)));
        return future;
    }

    template <typename TaskFunction, typename... Args>
    std::future<std::invoke_result_t<TaskFunction, Args...>> scheduleSingle(std::chrono::steady_clock::duration&& timeout, TaskFunction&& func, Args&&... args)
    {
        auto invokableTask = [t = std::forward<TaskFunction>(func), params = std::make_tuple(std::forward<Args>(args)...)]
        {
            return std::apply(t, params);
        };

        std::packaged_task<std::invoke_result_t<TaskFunction, Args...>()> taskWrapper(invokableTask);
        std::future<std::invoke_result_t<TaskFunction, Args...>> future = taskWrapper.get_future();

        addTask(std::move(std::chrono::steady_clock::now() + timeout), SchedulableTask(std::move(taskWrapper)));
        return future;
    }

    template <typename TaskFunction, typename... Args>
    std::future<std::invoke_result_t<TaskFunction, Args...>> scheduleSingle(std::string&& id, std::chrono::steady_clock::duration&& timeout, TaskFunction&& func, Args&&... args)
    {
        auto invokableTask = [t = std::forward<TaskFunction>(func), params = std::make_tuple(std::forward<Args>(args)...)]
        {
            return std::apply(t, params);
        };

        std::packaged_task<std::invoke_result_t<TaskFunction, Args...>()> taskWrapper(invokableTask);
        std::future<std::invoke_result_t<TaskFunction, Args...>> future = taskWrapper.get_future();

        addTask(std::move(std::chrono::steady_clock::now() + timeout), SchedulableTask(std::move(taskWrapper), m_hasher(id)));
        return future;
    }

    struct IntervalReps
    {
        std::chrono::steady_clock::duration interval;
        size_t maxReps = 0;
    };

    template <typename TaskFunction>
    void scheduleRepeat(IntervalReps&& intervalReps, TaskFunction&& func)
    {
        auto invokableTask = [t = std::forward<TaskFunction>(func)] { return t(); };
        addTask(std::move(std::chrono::steady_clock::now()), SchedulableTask(std::move(invokableTask), intervalReps.interval, intervalReps.maxReps));
    }

    template <typename TaskFunction, typename... Args>
    void scheduleRepeat(IntervalReps&& intervalReps, TaskFunction&& func, Args&&... args)
    {
        auto invokableTask = [t = std::forward<TaskFunction>(func), params = std::make_tuple(std::forward<Args>(args)...)]
        {
            return std::apply(t, params);
        };
        addTask(std::move(std::chrono::steady_clock::now()), SchedulableTask(std::move(invokableTask), intervalReps.interval, intervalReps.maxReps));
    }

    template <typename TaskFunction, typename... Args>
    void scheduleRepeat(std::string&& id, IntervalReps&& intervalReps, TaskFunction&& func, Args&&... args)
    {
        auto invokableTask = [t = std::forward<TaskFunction>(func), params = std::make_tuple(std::forward<Args>(args)...)]
        {
            return std::apply(t, params);
        };
        addTask(std::move(std::chrono::steady_clock::now()), SchedulableTask(std::move(invokableTask), m_hasher(id), intervalReps.interval, intervalReps.maxReps));
    }

private:
	TaskPool m_taskPool;
    std::map<std::chrono::steady_clock::time_point, SchedulableTask> m_tasks;
    std::thread m_schedulerThread;
	std::atomic_bool m_isRunning = true;
    std::hash<std::string> m_hasher;
    std::condition_variable m_thereAreTasksToExec;
    mutable std::mutex m_executeTasksMutex;

    void addTask(std::chrono::steady_clock::time_point&& timepoint, SchedulableTask&& st)
    {
        if (!m_isRunning)
        {
            return;
        }

        std::unique_lock<std::mutex> lock(m_executeTasksMutex);
        if (exists(st.hash()))
        {
            return;
        }
        m_tasks.emplace(std::move(timepoint), std::move(st));
        lock.unlock();

        m_thereAreTasksToExec.notify_one();
    }

    void executeTasks()
    {
        decltype(m_tasks) repeatingTasks;
        std::vector<std::chrono::steady_clock::time_point> keysToRemove;

        auto lastTaskToExecuteIter = m_tasks.upper_bound(std::chrono::steady_clock::now());
        for (auto it = m_tasks.begin(); it != lastTaskToExecuteIter; ++it)
        {
            std::shared_ptr<SchedulableTask> toInvoke = it->second.clone();
            if (it->second.isEnabled())
            {
                keysToRemove.push_back(it->first);
                m_taskPool.run([toInvoke] { toInvoke->invoke(); });

                if (it->second.interval().has_value())
                {
                    if (it->second.maxReps().has_value())
                    {
                        size_t remainingReps = it->second.maxReps().value() - 1;
                        it->second.decrementMaxReps();
                        if (remainingReps == 0)
                        {
                            continue;
                        }
                    }

                    auto taskInterval = it->second.interval().value();
                    auto taskNextStartTime = it->first + taskInterval;
                    auto now = std::chrono::steady_clock::now();
                    while (now > taskNextStartTime) // keep the scheduling with a fixed sample rate
                    {
                        taskNextStartTime += taskInterval;
                    }

                    repeatingTasks.emplace(std::move(taskNextStartTime), std::move(it->second));
                }
            }
        }
        for (const auto& key : keysToRemove)
        {
            auto it = m_tasks.find(key);
            if (it != m_tasks.end())
            {
                m_tasks.erase(it);
            }
        }
        m_tasks.merge(repeatingTasks);
    }

    bool exists(std::optional<size_t> hash) const
    {
        if (!hash.has_value())
        {
            return false;
        }

        return std::any_of(m_tasks.begin(), m_tasks.end(), [hash = hash.value()](auto&& it) {
            if (it.second.hash().has_value())
            {
                return hash == it.second.hash().value();
            }
            return false;
            });
    }

    decltype(m_tasks)::iterator taskIterator(const std::string& id)
    {
        return std::find_if(m_tasks.begin(), m_tasks.end(), [hash = m_hasher(id)](auto&& it) {
            if (it.second.hash().has_value())
            {
                return hash == it.second.hash().value();
            }
            return false;
        });
    }
};