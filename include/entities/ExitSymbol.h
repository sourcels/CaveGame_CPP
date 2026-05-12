#pragma once
#include "Entity.h"

class GameMap;

class ExitSymbol : public Entity {
public:
    bool win = false;
    ExitSymbol(GameMap* map);
    bool endOfGame() const;
};