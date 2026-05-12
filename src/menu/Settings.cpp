#include "menu/Settings.h"
#include "Platform.h"
#include <string>
#include <cstdio>

int  Settings::selectedSpeed    = 3;
int  Settings::selectedQuantity = 1;
bool Settings::selectedRender   = true;

std::string Settings::speedString(int sp) {
    if (sp == 1) return "высокая";
    if (sp == 2) return "умеренная";
    return "медленная";
}
std::string Settings::renderString(bool val) {
    return val ? "нет" : "да";
}

Settings::Settings() {
    width  = Platform::getWindowWidth();
    height = Platform::getWindowHeight();
}

void Settings::showSettings() {
    std::string amountMonsters = "Количество монстров: ";
    std::string monstersSpeed  = "Скорость монстров: ";
    std::string render         = "Ограниченная видимость: ";
    std::string back           = "Назад";
    std::string sym            = "<";

    int centerX = Platform::getWindowWidth() / 2 - (int)amountMonsters.size() / 2;
    int centerY = Platform::getWindowHeight() / 2 - 1;

    Platform::setCursorPos(centerX, centerY);
    printf("%s%s%s\n", monstersSpeed.c_str(), speedString(selectedSpeed).c_str(),
           selectedButton == 0 ? (sym+"  ").c_str() : "   ");

    Platform::setCursorPos(centerX, centerY + 1);
    printf("%s%d%s\n", amountMonsters.c_str(), selectedQuantity,
           selectedButton == 1 ? (sym+"  ").c_str() : "   ");

    Platform::setCursorPos(centerX, centerY + 2);
    printf("%s%s%s\n", render.c_str(), renderString(selectedRender).c_str(),
           selectedButton == 2 ? (sym+"  ").c_str() : "   ");

    Platform::setCursorPos(centerX, centerY + 3);
    printf("%s%s\n", back.c_str(),
           selectedButton == 3 ? sym.c_str() : "  ");

    fflush(stdout);
}

int Settings::getInputSettings() {
    Platform::clearScreen();
    while (true) {
        int cw = Platform::getWindowWidth();
        int ch = Platform::getWindowHeight();
        if (cw != width || ch != height) {
            width = cw; height = ch;
            Platform::clearScreen();
        }
        showSettings();

        int key = Platform::readKey();
        int lkey = (key >= 'A' && key <= 'Z') ? key + 32 : key;

        if (lkey == 13) {
            if (selectedButton == 3) return 3;
        } else if (lkey == 'w') {
            if (selectedButton > 0) selectedButton--;
        } else if (lkey == 's') {
            if (selectedButton < 3) selectedButton++;
        } else if (lkey == 'a') {
            if (selectedButton == 0) { if (selectedSpeed < 3) selectedSpeed++; }
            else if (selectedButton == 1) { if (selectedQuantity > 0) selectedQuantity--; }
            else if (selectedButton == 2) selectedRender = !selectedRender;
        } else if (lkey == 'd') {
            if (selectedButton == 0) { if (selectedSpeed > 1) selectedSpeed--; }
            else if (selectedButton == 1) { if (selectedQuantity < 10) selectedQuantity++; }
            else if (selectedButton == 2) selectedRender = !selectedRender;
        }
    }
}
