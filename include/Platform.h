#pragma once
#include <string>
#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <conio.h>
#endif

namespace Platform {
    void init();
    void setCursorPos(int x, int y);
    void colorGreen();
    void colorYellow();
    void colorRed();
    void colorDarkRed();
    void colorReset();
    void clearScreen();
    void hideCursor();
    void showCursor();
    void setWindowSize(int w, int h);
    bool isKeyDown(int vKey);
    int readKey();
    bool keyAvailable();
    void flushKeys();
    void sleepMs(int ms);
    int getWindowWidth();
    int getWindowHeight();
    void setTitle(const std::string& title);
}
