#pragma once

#include<mutex>
#include<oXu/core/threading/thread.hpp>

#define MAIN 0
#define GRAPHICS 1
#define SOUND 2

namespace oxu::Threading
{
    inline Thread threads[3];
    inline std::mutex mtx;
}
