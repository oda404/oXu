#include"timer.hpp"

Timer::Timer():
tIsRunning(false) { }

void Timer::start() {
    tStart = std::chrono::steady_clock::now();
    tIsRunning = true;
}

void Timer::stop() {
    tStop = std::chrono::steady_clock::now();
    tIsRunning = false;
}

void Timer::pause() {
    /* if the timer is not paused set the starting time point of the pause and it's stopping time point */
    if(!tIsPaused) {
        tpStart = std::chrono::steady_clock::now();
        tStop = tpStart;
        tIsPaused = true;
    }
}

void Timer::resume() {
    /* if the timer is paused add the duration of it's pause to that timer's pause time */
    if(tIsPaused) {
        tPausedTime += std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - tpStart).count();
        tIsPaused = false;
    }
}

void Timer::restart() {
    start();
    tIsPaused = false;
    tPausedTime = 0;
}

bool Timer::isTimerPaused() const {
    return tIsPaused ? true : false;
}

bool Timer::isTimerRunning() const {
    return tIsRunning && !tIsPaused ? true : false;
}

uint64_t Timer::getEllapsedTimeAsMs() const {
    /* if the timer is currently running and is not paused return for how long it has been runnning - it's pause time
    else return for how long the timer ran before it was stopped - it's pause time */
    if(tIsRunning && !tIsPaused)
        return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - tStart).count() - tPausedTime;

    return std::chrono::duration_cast<std::chrono::milliseconds>(tStop - tStart).count() - tPausedTime;
}

uint64_t Timer::getPausedTimeAsMs() const {
    /* if the timer is paused return for how long it has been paused 
    else return it's total pause time */
    return tIsPaused ? std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - tpStart).count() : tPausedTime;
}