
#include<oxu/framework/threading/thread.hpp>

namespace oxu::framework::threading
{

/* I realy hate using namespace std. */
namespace chrono = std::chrono;

void Thread::cap_fps()
{
    std::this_thread::sleep_until(m_nextframe);

    auto now = chrono::system_clock::now();

    m_delta = chrono::duration<double, std::ratio<1>>(
        now - m_lastframe
    ).count();

    m_lastframe = now;
    m_nextframe = now + m_sleep_frames;
}

void Thread::start(std::function<void()> entryPoint)
{
    start();
    m_thread = std::thread(entryPoint);
}

void Thread::start()
{
    m_nextframe = chrono::system_clock::now();
    m_lastframe = m_nextframe - m_sleep_frames;
}

void Thread::set_max_fps(const uint16_t &maxfps)
{
    m_max_fps = maxfps;
    m_sleep_frames = chrono::duration<uint64_t, std::milli>(1000 / maxfps);
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