#pragma once
#include "Entity.h"

class GameMap;

class Person : public Entity {
public:
    bool isAlive = true;
    Person(char entity, int x, int y);
    void tryMovePerson(int newY, int newX, GameMap* map);
};
