#pragma once

#include<cstdint>
#include<thread>
#include<atomic>
#include<functional>

#include<oXu/core/threading/pipeline/pipeline.hpp>

#include<oXu/utils/timer.hpp>
#include<oXu/utils/logger.hpp>

namespace oxu
{
    struct Thread
    {
    private:
        std::thread thread;

        double startTick = 0.0;
        double lastTick = 0.0;
        double delta = 0.0;
        uint16_t maxFPS = 0;
    
    public:
        std::atomic<uint16_t> FPS = 0;
        std::atomic<bool> doneInit = false;

        Timer timer;
        Pipeline pipeline;

        void init(std::function<bool()> entryPoint, const uint16_t &maxFPS_p);
        // wrapper so i don't have to call Thrad::thread.join()
        void join();
        void calculateDelta();
        void limitFPS();

        const double &getDelta();
    };
}