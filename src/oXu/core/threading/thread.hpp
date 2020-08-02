#pragma once

#include<memory>
#include<cstdint>
#include<thread>
#include<atomic>

#include<oXu/utils/timer.hpp>

namespace oxu
{
    struct Thread
    {
        std::shared_ptr<std::thread> thread;

        uint32_t startTick = 0;
        uint32_t lastTick = 0;
        std::atomic<double> delta = 0.0;
        uint16_t maxFPS = 0;

        Timer timer;

        //maybe implement pipeline later if needed

        void calculateDelta();

        void limitFPS();
    };
}