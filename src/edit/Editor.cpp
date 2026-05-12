#include "edit/Editor.h"
#include "Platform.h"
#include <iostream>
#include <fstream>
#include <cstdio>

Editor::Editor() {
    selectedButton = 0;
    switchActiveInput = true;
    selectedSymbol = 0;

    customMap.resize(MAP_HEIGHT, std::string(MAP_WIDTH, ' '));
}

void Editor::tryDraw(int y, int x) {
    char symChar = symbolList[selectedSymbol];

    // Логика замены уникальных объектов (игрок, свет, выход)
    if (symChar == '@') {
        if (playerY != -1) tryErase(playerY, playerX);
        playerY = y; playerX = x;
    } else if (symChar == '*') {
        if (lightY != -1) tryErase(lightY, lightX);
        lightY = y; lightX = x;
    } else if (symChar == 'X') {
        if (exitY != -1) tryErase(exitY, exitX);
        exitY = y; exitX = x;
    }
    
    if (y >= 0 && y < MAP_HEIGHT && x >= 0 && x < MAP_WIDTH) {
        customMap[y][x] = symChar;
    }
}

void Editor::tryErase(int y, int x) {
    if (y >= 0 && y < MAP_HEIGHT && x >= 0 && x < MAP_WIDTH) {
        customMap[y][x] = ' ';
        Platform::setCursorPos(x, y);
        printf(" ");
    }
}

char Editor::switchSymbol() {
    selectedSymbol = (selectedSymbol + 1) % 5; 
    return symbolList[selectedSymbol];
}

char Editor::getCharOfCustomMap(int y, int x) const {
    if (y >= 0 && y < MAP_HEIGHT && x >= 0 && x < MAP_WIDTH) {
        return customMap[y][x];
    }
    return ' ';
}

void Editor::showRedactorMenu() {
    // Используем метки из Editor.h: saveLabel и exitLabel
    Platform::setCursorPos(0, MAP_HEIGHT);
    printf("%s%s   ", saveLabel.c_str(), (selectedButton == 0 ? sym.c_str() : " "));
    
    Platform::setCursorPos((int)saveLabel.length() + 5, MAP_HEIGHT);
    printf("%s%s", exitLabel.c_str(), (selectedButton == 1 ? sym.c_str() : " "));
}

int Editor::getInputRedactor() {
    while (true) {
        showRedactorMenu();
        int key = Platform::readKey();
        
        if (key == 27) return 2; // ESC
        if (key == 'a' || key == 'A') {
            if (selectedButton > 0) selectedButton--;
        }
        if (key == 'd' || key == 'D') {
            if (selectedButton < 1) selectedButton++;
        }
        if (key == 13) { // Enter
            return selectedButton; 
        }
    }
}

void Editor::saveMap(const std::string& fileName) {
    std::ofstream file("maps/" + fileName);
    if (file.is_open()) {
        for (const auto& line : customMap) {
            file << line << "\n";
        }
        file.close();
    }
}

void Editor::clearMap() {
    for (auto& line : customMap) {
        line = std::string(MAP_WIDTH, ' ');
    }
    playerX = playerY = lightX = lightY = exitX = exitY = -1;
}

void Editor::loadMap(const std::string& fileName) {
    std::ifstream file("maps/" + fileName);
    if (file.is_open()) {
        customMap.clear();
        std::string line;
        while (std::getline(file, line) && customMap.size() < MAP_HEIGHT) {
            if (line.length() > MAP_WIDTH) line = line.substr(0, MAP_WIDTH);
            customMap.push_back(line);
        }
        file.close();
    }
}