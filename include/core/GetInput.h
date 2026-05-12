#pragma once
#include <chrono>

class Person;
class GameMap;
class Render;
class Editor;
class Cursor;

class GetInput {
private:
    std::chrono::steady_clock::time_point lastMoveTime;
    std::chrono::steady_clock::time_point lastSwitchTime;

public:
    GetInput();
    void getGameInput(Person* person, GameMap* map, Render* render);
    void getEditorInput(Editor* edit, Cursor* cursor);
};
