#pragma once

constexpr const char* GAME_NAME = "Evades";

namespace Settings
{
    constexpr float FPS_SHOW_UPDATE = 0.5f; // update fps show in seconds
    constexpr float MAX_FPS = 144.f;

    void waitByMaxFPS(float dt);
}