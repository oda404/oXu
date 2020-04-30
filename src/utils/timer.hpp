#pragma once

#include<chrono>
#include<cstdint>

class Timer {
private:
    std::chrono::steady_clock::time_point tStart, tStop, tpStart;
    bool tIsRunning, tIsPaused = false;
    uint64_t tPausedTime = 0; // as milliseconds

public:
    Timer();
    ~Timer() = default;

    void start();

    void stop ();

    void pause();

    void resume();

    void restart();

    bool isTimerRunning() const;

    bool isTimerPaused() const;

    uint64_t getEllapsedTimeAsMs() const;

    uint64_t getPausedTimeAsMs() const;
};
