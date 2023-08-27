#pragma once

#include <memory>

// A wrapper of a callable object (supporting operator())
class InvokableTask
{
public:
    template<typename FunctionType>
    explicit InvokableTask(FunctionType&& f)
    : m_invokableTaskPtr{ std::make_unique<Task<FunctionType>>(std::move(f)) }
    {}

    InvokableTask(const InvokableTask&) = delete;
    InvokableTask& operator=(const InvokableTask&) = delete;

    InvokableTask(InvokableTask&& other) noexcept
    : m_invokableTaskPtr{ std::move(other.m_invokableTaskPtr) }
    {}

    void operator()()
    {
        m_invokableTaskPtr->invoke();
    }
    void invoke()
    {
        m_invokableTaskPtr->invoke();
    }

private:
    struct Base
    {
        virtual void invoke() = 0;
        virtual ~Base() = default;
    };

    template<typename FunctionType>
    struct Task : Base
    {
        explicit Task(FunctionType&& func) : m_func{ std::move(func) }
        {
            static_assert(std::is_invocable_v<decltype(func)>);
        }
        void invoke() override
        {
            m_func();
        }

        FunctionType m_func;
    };

    std::unique_ptr<Base> m_invokableTaskPtr;
};