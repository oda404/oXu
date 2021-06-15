#pragma once

#include<cstdint>
#include<thread>
#include<chrono>
#include<atomic>
#include<functional>
#include<oxu/core/threading/pipeline/pipeline.hpp>

namespace oxu
{
    using sys_clock = std::chrono::system_clock;
    using sys_clock_time_point = std::chrono::system_clock::time_point;
    using milliseconds = std::chrono::milliseconds;

    struct Thread
    {
    private:
        std::thread m_thread;
        double m_delta = 0.0;
        std::uint16_t m_max_fps = 0;
        std::uint16_t m_max_fps_ratio = 0;
        std::uint16_t m_current_fps = 0;
        
        sys_clock_time_point m_next_frame;
        sys_clock_time_point m_last_frame;

        void calculateDelta();
        void calculateFPS();

    public:
        Pipeline pipeline;
        std::atomic<bool> doneInit = false;

        void start(std::function<void()> entryPoint);
        void start();
        void join();
        /* cap the fps to whatever was set with setMaxFPS */
        void capFPS();
        void setMaxFPS(const uint16_t &maxFPS);
        const double &getDelta() const;
        const std::uint16_t &getCurrentFPS() const;
        /* returns the std::thread */
        const std::thread &getThread() const;
    };
}