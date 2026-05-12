#include "../include/Platform.h"
#include <cstdio>
#include <string>

#ifdef _WIN32

void Platform::init() {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD mode = 0;
    GetConsoleMode(hOut, &mode);
    mode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, mode);
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
}

void Platform::setCursorPos(int x, int y) {
    COORD coord = { (SHORT)x, (SHORT)y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void Platform::colorGreen()   { printf("\033[32m"); }
void Platform::colorYellow()  { printf("\033[33m"); }
void Platform::colorRed()     { printf("\033[31m"); }
void Platform::colorDarkRed() { printf("\033[31;2m"); }
void Platform::colorReset()   { printf("\033[0m"); }

void Platform::clearScreen() {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD coord = {0,0};
    DWORD written;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hOut, &csbi);
    DWORD size = csbi.dwSize.X * csbi.dwSize.Y;
    FillConsoleOutputCharacterA(hOut, ' ', size, coord, &written);
    FillConsoleOutputAttribute(hOut, csbi.wAttributes, size, coord, &written);
    SetConsoleCursorPosition(hOut, coord);
}

void Platform::hideCursor() {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO ci; GetConsoleCursorInfo(hOut, &ci);
    ci.bVisible = FALSE; SetConsoleCursorInfo(hOut, &ci);
}

void Platform::showCursor() {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO ci; GetConsoleCursorInfo(hOut, &ci);
    ci.bVisible = TRUE; SetConsoleCursorInfo(hOut, &ci);
}

void Platform::setWindowSize(int w, int h) {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SMALL_RECT rect = {0, 0, (SHORT)(w-1), (SHORT)(h-1)};
    COORD bufSize = {(SHORT)w, (SHORT)h};
    SetConsoleScreenBufferSize(hOut, bufSize);
    SetConsoleWindowInfo(hOut, TRUE, &rect);
}

bool Platform::isKeyDown(int vKey) {
    return (GetAsyncKeyState(vKey) & 0x8000) != 0;
}

int Platform::readKey() {
    int ch = _getch();
    if (ch == 0 || ch == 224) { _getch(); return -1; }
    return ch;
}

bool Platform::keyAvailable() { return _kbhit() != 0; }
void Platform::flushKeys()    { while (_kbhit()) _getch(); }
void Platform::sleepMs(int ms){ Sleep(ms); }

int Platform::getWindowWidth() {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    return csbi.srWindow.Right - csbi.srWindow.Left + 1;
}
int Platform::getWindowHeight() {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    return csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
}

void Platform::setTitle(const std::string& title) {
    SetConsoleTitleA(title.c_str());
}

#else
#include <unistd.h>
void Platform::init()            { printf("\033[?25l"); fflush(stdout); }
void Platform::setCursorPos(int x, int y) { printf("\033[%d;%dH", y+1, x+1); fflush(stdout); }
void Platform::colorGreen()      { printf("\033[32m"); }
void Platform::colorYellow()     { printf("\033[33m"); }
void Platform::colorRed()        { printf("\033[31m"); }
void Platform::colorDarkRed()    { printf("\033[31;2m"); }
void Platform::colorReset()      { printf("\033[0m"); }
void Platform::clearScreen()     { printf("\033[2J\033[H"); fflush(stdout); }
void Platform::hideCursor()      { printf("\033[?25l"); fflush(stdout); }
void Platform::showCursor()      { printf("\033[?25h"); fflush(stdout); }
void Platform::setWindowSize(int,int) {}
bool Platform::isKeyDown(int)    { return false; }
int  Platform::readKey()         { return getchar(); }
bool Platform::keyAvailable()    { return false; }
void Platform::flushKeys()       {}
void Platform::sleepMs(int ms)   { usleep(ms * 1000); }
int  Platform::getWindowWidth()  { return 122; }
int  Platform::getWindowHeight() { return 30; }
void Platform::setTitle(const std::string& t) { printf("\033]0;%s\007", t.c_str()); }
#endif
