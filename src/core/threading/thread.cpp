
#include<oxu/core/threading/thread.hpp>

namespace oxu
{
    void Thread::calculateDelta()
    {   
        m_delta = std::chrono::duration_cast<milliseconds>(
            m_next_frame - m_last_frame
        ).count() / 1000.0;
    }

    void Thread::calculateFPS()
    {

    }

    void Thread::capFPS()
    {
        std::this_thread::sleep_until(m_next_frame);
        m_last_frame = m_next_frame;
        m_next_frame += milliseconds(m_max_fps_ratio);

        calculateDelta();
        calculateFPS();
    }

    void Thread::start(std::function<void()> entryPoint)
    {
        m_next_frame = sys_clock::now();
        m_last_frame = m_next_frame;
        m_thread = std::thread(entryPoint);
    }
    
    void Thread::start()
    {
        m_next_frame = sys_clock::now();
        m_last_frame = m_next_frame;
    }

    void Thread::setMaxFPS(const uint16_t &maxFPS)
    {
        m_max_fps = maxFPS;
        m_max_fps_ratio = 1000 / m_max_fps;
    }

    void Thread::join()
    {
        m_thread.join();
    }

    const double &Thread::getDelta() const
    {
        return m_delta;
    }

    const std::uint16_t &Thread::getCurrentFPS() const
    {
        return m_current_fps;
    }

    const std::thread &Thread::getThread() const
    {
        return m_thread;
    }
}