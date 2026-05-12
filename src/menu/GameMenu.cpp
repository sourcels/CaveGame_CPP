#include "menu/GameMenu.h"
#include "Platform.h"
#include <cstdio>

GameMenu::GameMenu() {
    width = Platform::getWindowWidth();
    height = Platform::getWindowHeight();
    selectedButton = 0;
}

void GameMenu::showMenuWord() {
    int startX = (width / 2) - 7;
    int startY = (height / 2) - 8;

    for (int i = 0; i < 5; i++) {
        Platform::setCursorPos(startX, startY + i);
        for (int j = 0; j < 14; j++) {
            printf("%s", menus[i][j]);
        }
    }
}

void GameMenu::showMenu() {
    showMenuWord();

    int centerX = width / 2 - 5;
    int centerY = height / 2 - 1;

    Platform::setCursorPos(centerX, centerY);
    printf("%s %s", play.c_str(), (selectedButton == 0 ? symbol.c_str() : "  "));

    Platform::setCursorPos(centerX, centerY + 1);
    printf("%s %s", settings.c_str(), (selectedButton == 1 ? symbol.c_str() : "  "));

    Platform::setCursorPos(centerX, centerY + 2);
    printf("%s %s", redactor.c_str(), (selectedButton == 2 ? symbol.c_str() : "  "));

    Platform::setCursorPos(centerX, centerY + 3);
    printf("%s %s", quit.c_str(), (selectedButton == 3 ? symbol.c_str() : "  "));
    
    fflush(stdout);
}

int GameMenu::getInputMenu() {
    Platform::clearScreen();
    while (true) {
        int currentW = Platform::getWindowWidth();
        int currentH = Platform::getWindowHeight();
        if (currentW != width || currentH != height) {
            width = currentW;
            height = currentH;
            Platform::clearScreen();
        }

        showMenu();

        int key = Platform::readKey();
        if (key >= 'A' && key <= 'Z') key += 32;

        if (key == 13) {
            return selectedButton;
        } 
        else if (key == 'w' || key == 'W') {
            if (selectedButton > 0) {
                selectedButton--;
                Platform::clearScreen();
            }
        } 
        else if (key == 's' || key == 'S') {
            if (selectedButton < 3) {
                selectedButton++;
                Platform::clearScreen();
            }
        }
    }
}