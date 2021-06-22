
#include<oxu/framework/threading/thread.hpp>

namespace oxu::framework::threading
{

/* I realy hate using namespace std. */
namespace chrono = std::chrono;

void Thread::calculate_delta()
{   
    m_delta = chrono::duration_cast<chrono::milliseconds>(
        m_next_frame - m_last_frame
    ).count() / 1000.0;
}

void Thread::calculate_fps()
{

}

void Thread::cap_fps()
{
    std::this_thread::sleep_until(m_next_frame);
    m_last_frame = m_next_frame;
    m_next_frame += chrono::milliseconds(m_max_fps_ratio);

    calculate_delta();
    calculate_fps();
}

void Thread::start(std::function<void()> entryPoint)
{
    start();
    m_thread = std::thread(entryPoint);
}

void Thread::start()
{
    m_next_frame = chrono::system_clock::now();
    m_last_frame = m_next_frame;
}

void Thread::set_max_fps(const uint16_t &maxfps)
{
    m_max_fps = maxfps;
    m_max_fps_ratio = 1000 / m_max_fps;
}

void Thread::join()
{
    m_thread.join();
}

const double &Thread::get_delta() const
{
    return m_delta;
}

const std::uint16_t &Thread::get_fps() const
{
    return m_fps;
}

const std::uint16_t &Thread::get_max_fps() const
{
    return m_max_fps;
}

std::thread &Thread::get_native_thread()
{
    return m_thread;
}

}