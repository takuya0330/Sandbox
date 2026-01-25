#pragma once

// https://zenn.dev/nishiki/articles/01ff1417f0b85f

#include <queue>
#include <mutex>
#include <functional>
#include <thread>
#include <vector>
#include <condition_variable>
#include <atomic>
#include <future>

#define JOB_SYSTEM_PART1 1
#define JOB_SYSTEM_PART2 1

#if JOB_SYSTEM_PART2
using JobItem = std::packaged_task<void()>;
using JobHandle = std::shared_future<void>;
#endif

using JobFunction = std::function<void()>;

class JobSystem
{
public:
    explicit JobSystem(size_t thread_count);

    ~JobSystem();

#if 0
#elif JOB_SYSTEM_PART2
    JobHandle Schedule(const JobFunction& job);

    JobHandle Schedule(const JobFunction& job, const std::vector<JobHandle>& dependencies);
#elif JOB_SYSTEM_PART1
    void Schedule(const JobFunction& job);
#endif

    void WaitForAll();

private:
    void wokerThread();

private:
    //! \brief 排他制御用
    std::mutex m_mutex;

    //! \brief ジョブキュー
#if 0
#elif JOB_SYSTEM_PART2
    std::queue<JobItem> m_job_queue;
#elif JOB_SYSTEM_PART1
    std::queue<JobFunction> m_job_queue;
#endif

    //! \brief ワーカースレッド
    std::vector<std::thread> m_workers;

    //! \brief 条件変数
    std::condition_variable m_condition;

    //! \brief ジョブ数
    std::atomic<int> m_job_count;

    //! \brief ジョブ完了フラグ
    std::atomic<bool> m_is_complete;

    //! \brief ワーカースレッド終了フラグ
    std::atomic<bool> m_is_stop_worker;
};
