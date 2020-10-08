#include"thread.hpp"

#include<oXu/utils/logger.hpp>

namespace oxu
{
    void Thread::calculateDelta()
    {
        m_lastTick = m_startTick;
        m_startTick = m_timer.getEllapsedUs() / 1000.0;
        
        m_delta = (m_startTick - m_lastTick) / 1000.0;
    }

    void Thread::limitFPS()
    {
        if(1000000.0 / m_maxFPS > m_timer.getEllapsedUs() - m_startTick * 1000.0)
        {
            std::this_thread::sleep_for(std::chrono::microseconds(static_cast<uint32_t>(1000000.0 / m_maxFPS - m_timer.getEllapsedUs() + m_startTick * 1000.0)));
        }

        m_FPS = 1 / m_delta;

        calculateDelta();
    }

    void Thread::start(std::function<void()> entryPoint)
    {
        m_thread = std::thread(entryPoint);
        m_timer.start();
    }
    
    void Thread::start()
    {
        m_timer.start();
    }

    void Thread::setMaxFPS(const uint16_t &maxFPS)
    {
        m_maxFPS = maxFPS;
    }

    void Thread::join()
    {
        m_thread.join();
    }

    const double &Thread::getDelta()
    {
        return m_delta;
    }

    uint32_t Thread::getRunningTimeMs()
    {
        return m_timer.getEllapsedMs();
    }
}