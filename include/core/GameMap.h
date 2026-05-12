#pragma once
#include <vector>
#include <string>
#include <utility>

class GameMap {
private:
    std::vector<std::string> map;

public:
    GameMap();
    GameMap(const std::vector<std::string>& customMap);

    int mapWidth() const;
    int mapHeight() const;

    std::pair<int,int> findSymbol(char symbol) const;
    void eraseSymbol(int x, int y);
    char getCharOfMap(int y, int x) const;
};
