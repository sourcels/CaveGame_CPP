#pragma once
#include <chrono>

class GUI {
private:
    int frames = 0;
    int fps = 0;
    std::chrono::steady_clock::time_point lastTime;

public:
    GUI();
    void fpsCounter();
    void showFPS();
};
