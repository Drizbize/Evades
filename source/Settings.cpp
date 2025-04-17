#include "Settings.h"

#include <chrono>
#include <thread>

namespace Settings {
    void waitByMaxFPS(float dt)
    {
        constexpr float targetFrameTime  = 1.f / Settings::MAX_FPS;  // ≃ 0.01667 seconds
        float sleepTime = targetFrameTime - dt;
        if (sleepTime > 0.f)
        {
            std::this_thread::sleep_for(std::chrono::duration<float>(sleepTime));
        }
    }
}