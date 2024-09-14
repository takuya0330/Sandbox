#include <iostream>
#include <chrono>
#include <thread>
#include <algorithm>

struct Time
{
    //! \brief 経過時間の最小値
    float min_delta_time;

    //! \brief 経過時間の最大値
    float max_delta_time;

    //! \brief 経過時間
    //!
    //! \note 1フレームの経過時間が max_delta_time より大きい場合、max_delta_time にスケールされます。
    float delta_time;

    //! \brief 経過時間
    //!
    //! \note この変数は max_delta_time によってスケールされません。
    float unscaled_delta_time;

    //! \brief 経過時間の合計値
    //!
    //! \note この変数はアプリケーションが起動してからの delta_time の合計値です。
    float total_time;

    //! \brief 経過時間の合計値
    //!
    //! \note この変数はアプリケーションが起動してからの unscaled_delta_time の合計値です。
    float unscaled_total_time;

    //! \brief 固定経過時間
    float fixed_delta_time;

    //! \brief 固定経過時間の合計値
    //!
    //! \note この変数はアプリケーションが起動してからの fixed_delta_time の合計値です。
    float fixed_total_time;

    //! \brief 時間スケール
    float time_scale;

    //! \brief 経過フレーム
    int frame_count;

    Time()
        : min_delta_time(1.0f / 240)
        , max_delta_time(1.0f / 10)
        , delta_time(0.0f)
        , unscaled_delta_time(0.0f)
        , total_time(0.0f)
        , unscaled_total_time(0.0f)
        , fixed_delta_time(0.02f)
        , fixed_total_time(0.0f)
        , time_scale(1.0f)
        , frame_count(0)
    {
    }
};

void FixedUpdate(const Time& time)
{
    std::cout << "FixedUpdate" << std::endl;
}

void Update(const Time& time)
{
    std::cout << "Update" << std::endl;
}

int main(int, char**)
{
    Time time;

    using system_clock_t = std::chrono::high_resolution_clock;
    using duration_t = std::chrono::duration<double>;

    system_clock_t::time_point time_start = system_clock_t::now();
    system_clock_t::time_point time_end;
    duration_t delta_time(0.0);
    duration_t sleep_time(0.0);
    duration_t frame_interval(0.0);
    int fixed_update_total_count = 0;
    while (time.frame_count < 60)
    {
        // 経過時間を保存
        time.unscaled_delta_time = static_cast<float>(delta_time.count());
        time.delta_time = std::clamp(time.unscaled_delta_time, time.min_delta_time, time.max_delta_time);

        // 経過時間を加算
        time.unscaled_total_time += time.unscaled_delta_time;
        time.total_time += time.delta_time;

        // 固定更新
        while (time.total_time >= time.fixed_total_time + time.fixed_delta_time)
        {
            time.fixed_total_time += time.fixed_delta_time;
            ++fixed_update_total_count;
            FixedUpdate(time);
        }

        // 更新
        Update(time);

        // 待機
        while (true)
        {
            // 計測終了
            time_end = system_clock_t::now();

            // 経過時間
            delta_time = time_end - time_start;

            // 待機時間
            sleep_time = frame_interval - delta_time;
            if (sleep_time.count() > 0)
            {
                std::this_thread::yield();
                continue;
            }
            break;
        }

        // フレーム値加算
        ++time.frame_count;

        // 計測開始
        time_start = time_end;
    }

    std::cout << "FixedUpdate Count: " << fixed_update_total_count << std::endl;
    std::cout << "Update Count: " << time.frame_count << std::endl;

    return 0;
}
