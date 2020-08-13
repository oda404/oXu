#pragma once

#include<mutex>
#include<array>

#include<oXu/core/threading/thread.hpp>

namespace oxu
{
    struct Threads
    {
    private:
        static std::array<Thread, 3> threads;

    public:
        static Thread &get(uint8_t threadEnum);
        static std::mutex mtx;

        enum
        {
            MAIN = 0,
            GRAPHICS = 1,
            SOUND = 2,
        };
    };
}
