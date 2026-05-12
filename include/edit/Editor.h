#pragma once
#include <string>
#include <vector>

class Editor {
private:
    char symbolList[5] = {'#','@','&','X','*'};

    int playerY = -1, playerX = -1;
    int lightY  = -1, lightX  = -1;
    int exitY   = -1, exitX   = -1;

    int selectedButton = 0;
    std::string exitLabel = "Выйти";
    std::string saveLabel = "Сохранить";
    std::string sym = "<";

public:
    static const int MAP_WIDTH  = 119;
    static const int MAP_HEIGHT = 29;

    int selectedSymbol = 0;
    bool switchActiveInput = true;
    std::vector<std::string> customMap;

    Editor();

    void tryDraw(int y, int x);
    void tryErase(int y, int x);
    char switchSymbol();
    char getCharOfCustomMap(int y, int x) const;

    std::string getFileName();
    std::vector<std::string> getCustomMaps();
    void saveMap(const std::string& fileName);
    void loadMap(const std::string& fileName);
    void clearMap();

    void showRedactorMenu();
    int  getInputRedactor();
};
