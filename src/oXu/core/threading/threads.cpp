#include"threads.hpp"

namespace oxu
{
    std::array<Thread,3 > Threads::threads;
    std::mutex Threads::mtx;

    Thread &Threads::get(uint8_t threadEnum)
    {
        return threads[threadEnum];
    }
}