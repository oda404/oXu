#include"threads.hpp"

namespace oxu
{
    Threads::Threads()
    {

    }

    Threads &Threads::instance()
    {
        static Threads threadsInstance;
        return threadsInstance;
    }
}