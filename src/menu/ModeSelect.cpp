#include "menu/ModeSelect.h"
#include "Platform.h"
#include <cstdio>

void ModeSelect::showMode() {
    int centerX = (Platform::getWindowWidth() / 2) - ((int)story.length() / 2);
    int centerY = (Platform::getWindowHeight() / 2) - 1;

    Platform::setCursorPos(centerX, centerY);
    printf("%s %s", story.c_str(), (selectedButton == 0 ? sym.c_str() : "  "));

    Platform::setCursorPos(centerX, centerY + 1);
    printf("%s %s", custom.c_str(), (selectedButton == 1 ? sym.c_str() : "  "));
    
    fflush(stdout);
}

int ModeSelect::getInputMode() {
    while (true) {
        showMode();
        int key = Platform::readKey();
        if (key >= 'A' && key <= 'Z') key += 32;

        if (key == 13) return selectedButton;
        if (key == 'w' && selectedButton > 0) selectedButton--;
        if (key == 's' && selectedButton < 1) selectedButton++;
    }
}

void ModeSelect::selectCustomMap(const std::vector<std::string>& maps) {
    for (int i = 0; i < (int)maps.size(); i++) {
        int centerX = (Platform::getWindowWidth() / 2) - ((int)maps.size() / 2);
        int centerY = (Platform::getWindowHeight() / 2 - ((int)maps.size() / 2)) + i;

        Platform::setCursorPos(centerX, centerY);
        printf("%s %s", maps[i].c_str(), (selectedCustomMap == i ? sym.c_str() : "  "));
    }
    fflush(stdout);
}

void ModeSelect::selectAndEditCustomMap(const std::vector<std::string>& maps) {
    selectCustomMap(maps);
    // specific game logic (when needed)
}

int ModeSelect::getInputCustomMap(const std::vector<std::string>& maps, bool flag) {
    while (true) {
        if (flag) selectAndEditCustomMap(maps);
        else selectCustomMap(maps);

        int key = Platform::readKey();
        if (key >= 'A' && key <= 'Z') key += 32;

        if (key == 13) return selectedCustomMap;
        if (key == 'w' && selectedCustomMap > 0) selectedCustomMap--;
        if (key == 's') {
            int limit = flag ? (int)maps.size() : (int)maps.size() - 1;
            if (selectedCustomMap < limit) selectedCustomMap++;
        }
    }
}