#pragma once
#include <vector>
#include <memory>
#include <string>
#include <chrono>

class GameMap;
class Person;
class Entity;
class Cursor;
class Editor;

class Render {
public:
    bool visionFlag;
    bool fieldOnScreen = false;

private:
    std::chrono::steady_clock::time_point lightEnd;

public:
    Render();
    void cheat();
    void activateVision();
    void draw(GameMap* map, Person* person, std::vector<std::shared_ptr<Entity>>& list);
    void drawOnlyMap(const std::vector<std::string>& map, Cursor* cursor, Editor* edit);
};
