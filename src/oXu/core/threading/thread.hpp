#pragma once

#include<cstdint>
#include<thread>
#include<atomic>
#include<functional>

#include<oXu/core/threading/pipeline/pipeline.hpp>
#include<oXu/utils/timer.hpp>

namespace oxu
{
    struct Thread
    {
    private:
        std::thread m_thread;
        double m_startTick = 0.0;
        double m_lastTick = 0.0;
        double m_delta = 0.0;
        uint16_t m_maxFPS = 0;
        std::atomic<uint16_t> m_FPS = 0;
        Timer m_timer;

        void calculateDelta();

    public:
        Pipeline pipeline;
        std::atomic<bool> doneInit = false;

        void start(std::function<void()> entryPoint);
        void start();
        void join();
        void limitFPS();
        void setMaxFPS(const uint16_t &maxFPS);
        const double &getDelta();
        uint32_t getRunningTimeMs();
    };
}