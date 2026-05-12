#include "entities/Monster.h"
#include "entities/Person.h"
#include "core/GameMap.h"
#include <random>

Monster::Monster(GameMap* map) {
    entity = '&';
    std::uniform_int_distribution<int> dx(50, map->mapWidth() - 2);
    std::uniform_int_distribution<int> dy(1,  map->mapHeight() - 2);
    do {
        entityX = dx(rng);
        entityY = dy(rng);
    } while (map->getCharOfMap(entityY, entityX) == '#');
}

Monster::Monster(GameMap* map, int x, int y) {
    entity = '&'; entityX = x; entityY = y;
    (void)map;
}

void Monster::updatePosition(Person* player, GameMap* map) {
    personLastPosition();
    Entity::updatePosition(player, map);
}
