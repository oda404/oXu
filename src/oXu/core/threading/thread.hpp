#pragma once

#include<cstdint>
#include<thread>
#include<atomic>

#include<oXu/utils/timer.hpp>
#include<oXu/utils/logger.hpp>

namespace oxu
{
    struct Thread
    {
        std::thread thread;

        double startTick = 0.0;
        double lastTick = 0.0;
        double delta = 0.0;
        std::atomic<uint16_t> FPS = 0;
        std::atomic<bool> doneInit = false;
        uint16_t maxFPS = 0;

        Timer timer;

        //maybe implement pipeline later if needed

        void calculateDelta();

        void limitFPS();
    };
}