#include"thread.hpp"

namespace oxu
{
    void Thread::calculateDelta()
    {
        lastTick = startTick;
        startTick = timer.getEllapsedTimeMicro() / 1000.0;
        
        delta = (startTick - lastTick) / 1000.0;
    }

    void Thread::limitFPS()
    {
        if(1000000.0 / maxFPS > timer.getEllapsedTimeMicro() - startTick * 1000.0)
        {
            std::this_thread::sleep_for(std::chrono::microseconds(static_cast<uint32_t>(1000000.0 / maxFPS - timer.getEllapsedTimeMicro() + startTick * 1000.0)));
        }

        FPS = 1 / delta;
    }
}