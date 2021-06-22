#pragma once

#include<cstdint>
#include<thread>
#include<chrono>
#include<atomic>
#include<functional>
#include<oxu/framework/threading/pipeline.hpp>

namespace oxu::framework::threading
{

struct Thread
{
private:
    std::thread m_thread;
    double m_delta = 0.0;
    std::uint16_t m_max_fps = 0;
    std::uint16_t m_max_fps_ratio = 0;
    std::uint16_t m_fps = 0;
    
    std::chrono::system_clock::time_point m_next_frame;
    std::chrono::system_clock::time_point m_last_frame;

    void calculate_delta();
    void calculate_fps();

public:
    Pipeline pipeline;
    std::atomic<bool> doneInit = false;

    /** Starts the thread using the given entrypoint. */
    void start(std::function<void()> entryPoint);
    /**
     * This function doesn't actually make use of std::thread
     * and doesn't spawn a new thread.
     * It's more of an init for using fps capping/delta.
    */
    void start();
    /**
     * The same as get_native_thread.join().
    */
    void join();
    /**
     * Sleep until maxfps is matched.
    */
    void cap_fps();
    void set_max_fps(const uint16_t &maxfps);
    /**
     * @return the time delta beetwen the current and last frame.
    */
    const double &get_delta() const;
    /**
     * @return the current fps.
    */
    const std::uint16_t &get_fps() const;
    const std::uint16_t &get_max_fps() const;

    /**
     * @return the std::thread object associated with this Thread. 
    */
    std::thread &get_native_thread();
};

}