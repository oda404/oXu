#pragma once

#include<mutex>
#include<oXu/core/threading/thread.hpp>

#define MAIN_THREAD 0
#define GRAPHICS_THREAD 1
#define SOUND_THREAD 2

namespace oxu
{
    struct Threads
    {
    public:
        static Threads &instance();
        Threads(Threads const&) = delete;
        void operator=(Threads const&) = delete;

        Thread threads[3];

        std::mutex mtx;

    private:
        Threads();
    };
}
