#pragma once
#include "Entity.h"

class GameMap;

class Light : public Entity {
public:
    Light(GameMap* map, char entity);
};
