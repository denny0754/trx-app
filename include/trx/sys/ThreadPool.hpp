/*
	`transaction-x` allows users to manage their personal expenses.
	Copyright (C) 2024  Diego Vaccher

	This program is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#pragma once

/* Standard Headers */
#include <vector>
#include <thread>
#include <queue>
#include <functional>
#include <future>
#include <mutex>
#include <condition_variable>
#include <atomic>

namespace trx
{

class ThreadPool
{
public:
    using Task = std::function<void()>;

public:
    ThreadPool(size_t thread_count = std::thread::hardware_concurrency())
        : m_poolRunning(true)
    {
        for (size_t i = 0; i < thread_count; ++i)
        {
            m_threads.emplace_back([this]() {
                while (m_poolRunning)
                {
                    Task task;
                    {
                    std::unique_lock<std::mutex> lock(m_mutex);
                    m_condition.wait(lock, [this]() { return !m_poolRunning || !m_tasks.empty(); });

                    if (!m_poolRunning && m_tasks.empty())
                    return;

                    task = std::move(m_tasks.front());
                    m_tasks.pop();
                    }

                    task(); // Execute the task
                }
            });
        }
    }

    // Submit a task to the thread pool and get a future for its result
    template <typename Func, typename... Args>
    auto Submit(Func&& func, Args&&... args)
        -> std::future<std::invoke_result_t<Func, Args...>>
    {
        using ReturnType = std::invoke_result_t<Func, Args...>;

        if constexpr (std::is_void_v<ReturnType>) // Handle void return types
        {
            auto task = std::make_shared<std::packaged_task<void()>>(
                std::bind(std::forward<Func>(func), std::forward<Args>(args)...));

            std::future<void> future = task->get_future();

            {
                std::lock_guard<std::mutex> lock(m_mutex);
                if (!m_poolRunning)
                    throw std::runtime_error("ThreadPool is not running!");

                m_tasks.emplace([task]() { (*task)(); });
            }

            m_condition.notify_one();
            return future;
        }
        else // Handle non-void return types
        {
            auto task = std::make_shared<std::packaged_task<ReturnType()>>(
                std::bind(std::forward<Func>(func), std::forward<Args>(args)...));

            std::future<ReturnType> future = task->get_future();

            {
                std::lock_guard<std::mutex> lock(m_mutex);
                if (!m_poolRunning)
                    throw std::runtime_error("ThreadPool is not running!");

                m_tasks.emplace([task]() { (*task)(); });
            }

            m_condition.notify_one();
            return future;
        }
    }
    ~ThreadPool()
    {
        {
            std::lock_guard<std::mutex> lock(m_mutex);
            m_poolRunning = false;
        }

        m_condition.notify_all();

        for(auto& thread : m_threads)
        {
            if(thread.joinable())
            {
                thread.join();
            }
        }
    }

private:
    std::vector<std::thread> m_threads;

    std::queue<ThreadPool::Task> m_tasks;

    std::mutex m_mutex;

    std::condition_variable m_condition;

    std::atomic<bool> m_poolRunning;
};

} // ns trx