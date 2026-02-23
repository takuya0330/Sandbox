#include "Job/Include/Job.h"

JobSystem::JobSystem(size_t thread_count)
    : m_mutex()
    , m_job_queue()
    , m_workers()
    , m_condition()
    , m_job_count(0)
#if JOB_SYSTEM_FIX
#else
    , m_is_complete(false)
#endif
    , m_is_stop_worker(false)
{
    for (size_t i = 0; i < thread_count; ++i)
    {
        m_workers.emplace_back([this] { wokerThread(); });
    }
}

JobSystem::~JobSystem()
{
#if JOB_SYSTEM_FIX
	// 全てのジョブが完了するのを待つ
	WaitForAll();
#endif

    // 全てのワーカースレッドに停止信号を送る
#if JOB_SYSTEM_FIX
	m_is_stop_worker.store(true, std::memory_order_release);
#else
    m_is_stop_worker.store(true);
#endif
    // 全てのワーカースレッドを起こす
    m_condition.notify_all();

    // 全てのワーカースレッドが完了するのを待つ
    for (auto& worker : m_workers)
    {
        if (worker.joinable())
        {
            worker.join();
        }
    }
}

#if 0
#elif JOB_SYSTEM_PART2
JobHandle JobSystem::Schedule(const JobFunction& job)
#elif JOB_SYSTEM_PART1
void JobSystem::Schedule(const JobFunction& job)
#endif
{
#if JOB_SYSTEM_PART2
    JobItem item(job);
    auto handle = item.get_future().share();
#endif
    {
        std::lock_guard<std::mutex> lock(m_mutex);
#if JOB_SYSTEM_FIX
		m_job_count.fetch_add(1, std::memory_order_relaxed);
#else
        // インクリメント
        m_job_count.fetch_add(1);
        // 未完了状態にする
        m_is_complete.store(false);
#endif
#if 0
#elif JOB_SYSTEM_PART2
        m_job_queue.push(std::move(item));
#elif JOB_SYSTEM_PART1
        m_job_queue.push(job);
#endif
    }
    // 待機中のワーカースレッドを一つ起こす
    m_condition.notify_one();

#if JOB_SYSTEM_PART2
    return handle;
#endif
}

#if JOB_SYSTEM_PART2
JobHandle JobSystem::Schedule(const JobFunction& job, const std::vector<JobHandle>& dependencies)
{
    return Schedule([job, dependencies]()
        {
            // 全ての依存ジョブが終わるまで待機する
            for (auto& it : dependencies)
            {
                if (it.valid())
                {
                    it.wait();
                }
            }
            job();
        });
}
#endif

void JobSystem::WaitForAll()
{
#if JOB_SYSTEM_FIX
	while (true)
	{
		int job_count = m_job_count.load(std::memory_order_acquire);
		if (job_count <= 0)
			break;

		m_job_count.wait(job_count, std::memory_order_acquire);
	}
#else
    // trueになるまで待機する
    m_is_complete.wait(false);
#endif
}

void JobSystem::wokerThread()
{
    while (true)
    {
#if 0
#elif JOB_SYSTEM_PART2
        JobItem job;
#elif JOB_SYSTEM_PART1
        JobFunction job;
#endif
        {
            // ジョブキューにジョブが追加されるor停止フラグが有効になるまで待機する
            std::unique_lock<std::mutex> lock(m_mutex);
#if JOB_SYSTEM_FIX
			m_condition.wait(lock, [this]
			    {
				    return !m_job_queue.empty() || m_is_stop_worker.load(std::memory_order_relaxed);
			    });
#else
			m_condition.wait(lock, [this]
			    {
				    return !m_job_queue.empty() || m_is_stop_worker;
			    });
#endif

            // キューが空かつ停止フラグが有効な場合終了する
#if JOB_SYSTEM_FIX
			if (m_is_stop_worker.load(std::memory_order_relaxed) && m_job_queue.empty())
#else
			if (m_job_queue.empty() && m_is_stop_worker)
#endif
			{
                break;
            }

            // ジョブキューからジョブを取得する
            job = std::move(m_job_queue.front());
            m_job_queue.pop();
        }

        // ジョブの実行
        job();

        // デクリメント
#if JOB_SYSTEM_FIX
		if (m_job_count.fetch_sub(1, std::memory_order_acq_rel) == 1)
		{
			m_job_count.notify_all();
		}
#else
		m_job_count.fetch_sub(1);
        if (m_job_count.load() == 0)
        {
            // カウントが0になったら完了フラグを立てて通知
            m_is_complete.store(true);
            m_is_complete.notify_all();
        }
#endif
	}
}
