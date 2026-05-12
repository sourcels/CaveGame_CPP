#pragma once
#include "Entity.h"

class GameMap;

class Monster : public Entity {
public:
    Monster(GameMap* map);
    Monster(GameMap* map, int x, int y);
    void updatePosition(Person* player, GameMap* map) override;
};
