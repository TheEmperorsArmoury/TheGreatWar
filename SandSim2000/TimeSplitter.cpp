#include "TimeSplitter.h"
#include <chrono>
#include <thread>

TimeSplitter::TimeSplitter() {}

TimeSplitter::~TimeSplitter() {}

void TimeSplitter::SixtyFramesOfDeath() {
    const long long frameTimeMicros = 16666;
    auto startTime = std::chrono::high_resolution_clock::now();

    // AnimationManager and other rendering here

    auto endTime = std::chrono::high_resolution_clock::now();
    auto timeDelta = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime).count();

    long long sleepTimeMicros = frameTimeMicros - timeDelta;
    if (sleepTimeMicros > 0) {
        std::this_thread::sleep_for(std::chrono::microseconds(sleepTimeMicros));
    }
}

