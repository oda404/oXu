#pragma once

#include<array>
#include<mutex>

#include<oXu/core/threading/thread.hpp>

namespace oxu
{
    class ThreadsManager
    {
    private:
        static std::array<Thread, 3> m_threads;

    public:
        static Thread &get(uint8_t p_threadsEnum);
        static std::mutex mtx;
    };

    enum Threads
    {
        MAIN = 0,
        GRAPHICS = 1,
        AUDIO = 2
    };
}