#pragma once

#include "InvokableTask.hpp"

#include <chrono>
#include <memory>
#include <optional>

class SchedulableTask
{
public:
    template<typename FunctionType>
    explicit SchedulableTask(FunctionType&& f)
    : m_task{ std::make_shared<InvokableTask>(std::forward<FunctionType>(f)) }
    {}

    template<typename FunctionType>
    explicit SchedulableTask(FunctionType&& f, size_t hash)
        : m_task{ std::make_shared<InvokableTask>(std::forward<FunctionType>(f)) }
        , m_hash{ hash }
    {}

    template<typename FunctionType>
    explicit SchedulableTask(FunctionType&& f, std::chrono::steady_clock::duration interval, size_t maxReps)
        : m_task{ std::make_shared<InvokableTask>(std::forward<FunctionType>(f)) }
        , m_interval{ interval }
    {
        if (maxReps > 0)
        {
            m_maxReps = maxReps;
        }
    }

    template<typename FunctionType>
    explicit SchedulableTask(FunctionType&& f, size_t hash, std::chrono::steady_clock::duration interval, size_t maxReps)
        : m_task{ std::make_shared<InvokableTask>(std::forward<FunctionType>(f)) }
        , m_hash{ hash }
        , m_interval{ interval }
    {
        if (maxReps > 0)
        {
            m_maxReps = maxReps;
        }
    }

    SchedulableTask(const SchedulableTask&) = delete;
    SchedulableTask& operator=(const SchedulableTask&) = delete;

    SchedulableTask(SchedulableTask&& other) noexcept
        : m_task{ std::move(other.m_task) }
        , m_isEnabled{ std::move(other.m_isEnabled) }
        , m_interval{ std::move(other.m_interval) }
        , m_maxReps{ std::move(other.m_maxReps) }
        , m_hash{ std::move(other.m_hash) }
    {
    }

    std::shared_ptr<SchedulableTask> clone()
    {
        return std::shared_ptr<SchedulableTask>(new SchedulableTask(this));
    }

    void invoke()
    {
        setEnabled(false);
        m_task->invoke();
        setEnabled(true);
    }

    void setEnabled(bool isEnabled)
    {
        *m_isEnabled = isEnabled;
    }
    bool isEnabled() const
    {
        return *m_isEnabled;
    }

    void setInterval(std::chrono::steady_clock::duration interval)
    {
        m_interval = interval;
    }
    std::optional<std::chrono::steady_clock::duration> interval() const
    {
        return m_interval;
    }

    void decrementMaxReps()
    {
        if (m_maxReps == 0)
        {
            return;
        }
        m_maxReps = m_maxReps.value() - 1;
    }
    std::optional<size_t> maxReps() const
    {
        return m_maxReps;
    }

    std::optional<size_t> hash() const
    {
        return m_hash;
    }

private:
    std::shared_ptr<InvokableTask> m_task;
    std::shared_ptr<bool> m_isEnabled = std::make_shared<bool>(true);
    std::optional<std::chrono::steady_clock::duration> m_interval;
    std::optional<size_t> m_maxReps;
    std::optional<size_t> m_hash;

    SchedulableTask(SchedulableTask* st)
        : m_task{ st->m_task }
        , m_isEnabled{ st->m_isEnabled }
        , m_interval{ st->m_interval }
        , m_maxReps{ st->m_maxReps }
        , m_hash{ st->m_hash }
    {}
};