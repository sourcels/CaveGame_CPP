#pragma once
#include <vector>
#include <deque>
#include <memory>
#include <chrono>
#include <random>

class GameMap;
class Render;
class Person;
class Light;
class Monster;
class ExitSymbol;

class Entity {
public:
    char entity;
    int entityX;
    int entityY;
    int lastEntityX;
    int lastEntityY;

protected:
    std::chrono::steady_clock::time_point lastMoveTime;
    std::deque<std::pair<int,int>> visitedCells;
    int visionRadius = 20;
    int memorySize = 50;
    static std::mt19937 rng;

public:
    Entity();
    virtual ~Entity() = default;

    void personLastPosition();
    virtual void updatePosition(Person* player, GameMap* map);
    void checkCollisions(std::vector<std::shared_ptr<Entity>>& list, Render* render);
    void setPosition(int x, int y);

private:
    bool vcContains(std::pair<int,int> p);
};
