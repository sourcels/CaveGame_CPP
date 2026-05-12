#include "core/GUI.h"
#include "Platform.h"
#include <cstdio>

GUI::GUI() : lastTime(std::chrono::steady_clock::now()) {}

void GUI::fpsCounter() { frames++; }

void GUI::showFPS() {
    auto now = std::chrono::steady_clock::now();
    if (std::chrono::duration<double>(now - lastTime).count() >= 1.0) {
        fps = frames; frames = 0; lastTime = now;
        Platform::setCursorPos(0, 29);
        printf("FPS: %d  ", fps);
        fflush(stdout);
    }
}
