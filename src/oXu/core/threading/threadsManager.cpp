#include"threadsManager.hpp"

#include<oXu/utils/logger.hpp>

namespace oxu
{
    std::array<Thread, 3> ThreadsManager::m_threads;
    std::mutex ThreadsManager::mtx;

    Thread &ThreadsManager::get(uint8_t p_threadsEnum)
    {
        if(p_threadsEnum > 2)
        {
            OXU_LOG_WARN("Tried to get a non existen thread, returned last thread in array!");
            return m_threads[m_threads.size() - 1];
        }

        return m_threads[p_threadsEnum];
    }
}