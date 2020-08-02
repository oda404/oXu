#include"thread.hpp"

namespace oxu
{
    void Thread::calculateDelta()
    {
        lastTick = startTick;
        startTick = timer.getEllapsedTime();
        delta = (startTick - lastTick) / 1000.0;
    }

    void Thread::limitFPS()
    {
        if(1000.0 / maxFPS > timer.getEllapsedTime() - startTick)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(1000 / maxFPS - timer.getEllapsedTime() + startTick));
        }
    }
}