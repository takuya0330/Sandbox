#include <iostream>
#include <chrono>
#include <random>
#include <iomanip>
#include <sstream>
#include <unordered_map>

#include "job.h"

struct JobData
{
    int name;
    std::chrono::high_resolution_clock::time_point start;
    std::chrono::high_resolution_clock::time_point end;
};

void busyWait(std::chrono::nanoseconds duration)
{
    auto start_time = std::chrono::high_resolution_clock::now();
    while (std::chrono::high_resolution_clock::now() - start_time < duration)
    {
        // CPU時間を消費するためのアクティブな待機
        // ループの中で何もしない
    }
}

std::string createTimeline(const std::vector<JobData>& job_data, std::chrono::high_resolution_clock::time_point global_start, int global_duration)
{
    // タイムラインを空白で初期化
    std::string timeline;
    for (const auto& data : job_data)
    {
        timeline = std::string(global_duration, ' ');
    }

    // ジョブ実行中の時刻にインデックスを挿入
    for (const auto& data : job_data)
    {
        auto begin = timeline.begin();
        auto start = std::chrono::duration_cast<std::chrono::milliseconds>(data.start - global_start).count();
        auto end = std::chrono::duration_cast<std::chrono::milliseconds>(data.end - global_start).count();
        std::fill(begin + start, begin + end, data.name);
    }

    return timeline;
}

int generateRandomInt(int min_num, int max_num)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distribution(min_num, max_num);
    return distribution(gen);
}

static std::mutex s_mutex;

#if JOB_SYSTEM_PART2
void func(std::unordered_map<std::thread::id, std::vector<JobData>>& job_data_map, int name)
{
    JobData data;
    data.name = name;
    data.start = std::chrono::high_resolution_clock::now();

    int sleep_time = generateRandomInt(5, 10);
    busyWait(std::chrono::milliseconds(sleep_time));

    data.end = std::chrono::high_resolution_clock::now();

    auto id = std::this_thread::get_id();
    std::lock_guard<std::mutex> lock(s_mutex);
    if (!job_data_map.contains(id))
    {
        job_data_map[id] = {};
    }
    job_data_map[id].push_back(data);
}
#endif

int main(int, char**)
{
    size_t thread_count = 4;
    JobSystem job_system(thread_count);

    // ジョブデータの格納先
    std::unordered_map<std::thread::id, std::vector<JobData>> job_data_map;

    // 開始時間を記録
    auto global_start = std::chrono::high_resolution_clock::now();

#if 0
#elif JOB_SYSTEM_PART2
    // ジョブAをスケジュールする
    std::vector<JobHandle> job_handle_a;
    for (int i = 0; i < 4; ++i)
    {
        auto handle = job_system.Schedule([&job_data_map]()
            {
                func(job_data_map, 'A');
            });

        // ハンドルを保持しておく
        job_handle_a.push_back(handle);

        busyWait(std::chrono::milliseconds(2));
    }

    // ジョブBをスケジュールする
    for (int i = 0; i < 4; ++i)
    {
        // ジョブAを待機するためハンドルを渡す
        job_system.Schedule([&job_data_map]()
            {
                func(job_data_map, 'B');
            }, job_handle_a);

        busyWait(std::chrono::milliseconds(2));
    }
#elif JOB_SYSTEM_PART1
    // いくつかのジョブをスケジュール
    for (int i = 0; i < 20; ++i)
    {
        // ジョブをスケジュール
        job_system.Schedule([i, &job_data_map]()
            {
                auto id = std::this_thread::get_id();

                // 開始時間を記録
                JobData data;
                data.name = 'A' + i;
                data.start = std::chrono::high_resolution_clock::now();

                // ランダムな時間だけ待機する
                int sleep_time = generateRandomInt(5, 10);
                busyWait(std::chrono::milliseconds(sleep_time));

                // 終了時間を記録
                data.end = std::chrono::high_resolution_clock::now();

                // ジョブデータを保存
                std::lock_guard<std::mutex> lock(s_mutex);
                if (!job_data_map.contains(id))
                {
                    job_data_map[id] = {};
                }
                job_data_map[id].push_back(data);
            });

        // 少し待機してから次のジョブをスケジュールする
        busyWait(std::chrono::milliseconds(2));
    }
#endif

    job_system.WaitForAll();

    // 終了時間を記録
    auto global_end = std::chrono::high_resolution_clock::now();
    auto global_duration = std::chrono::duration_cast<std::chrono::milliseconds>(global_end - global_start).count();
    std::cout << "Total duration: " << global_duration << " ms" << std::endl;

    // タイムラインを表示
    for (const auto& [id, data] : job_data_map)
    {
        // スレッドIDを空白埋めして5桁にする
        std::ostringstream ostream;
        ostream << std::setw(5) << std::setfill(' ') << id;
        std::string id_str = ostream.str();

        // タイムラインを表示
        std::string timeline = createTimeline(data, global_start, global_duration);
        std::cout << "Thread " << id_str << " |" << timeline << "| (" << data.size() << " jobs)" << std::endl;
    }

    return 0;
}
