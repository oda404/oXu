// Copyright (c) Olaru Alexandru <olarualexandru404@gmail.com>
// Licensed under the MIT license found in the LICENSE file in the root of this repository.

#pragma once

#include<chrono>
#include<cstdint>

namespace oxu::framework
{
    class Timer
    {
    private:
        std::chrono::steady_clock::time_point startPoint, stopPoint;
        bool running = false;

    public:
        void start();

        /* as milliseconds */
        uint32_t getEllapsedMs();

        uint32_t getEllapsedUs();
    };
}
