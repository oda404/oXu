// Copyright (c) Olaru Alexandru <olarualexandru404@gmail.com>
// Licensed under the MIT license found in the LICENSE file in the root of this repository.

#include"timer.hpp"

namespace oxu
{
    void Timer::start()
    {
        startPoint = std::chrono::steady_clock::now();
        running = true;
    }

    uint32_t Timer::getEllapsedMs()
    {
        return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - startPoint).count();
    }

    uint32_t Timer::getEllapsedUs()
    {
        return std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now() - startPoint).count();
    }
}
