#include "entities/ExitSymbol.h"
#include "core/GameMap.h"
#include <random>

ExitSymbol::ExitSymbol(GameMap* map) {
    this->win = false;
    std::uniform_int_distribution<int> dy(1, map->mapHeight() - 2);
    while (true) {
        entityX = map->mapWidth() - 2;
        entityY = dy(rng);
        if (map->getCharOfMap(entityY, entityX) != '#') {
            entity = 'X'; 
            break;
        }
    }
}

bool ExitSymbol::endOfGame() const {
    return win;
}