#include "entities/Light.h"
#include "core/GameMap.h"
#include "menu/Settings.h"
#include <random>

Light::Light(GameMap* map, char e) {
    if (!Settings::selectedRender) {
        std::uniform_int_distribution<int> dx(1, map->mapWidth() - 2);
        std::uniform_int_distribution<int> dy(1, map->mapHeight() - 2);
        do {
            entityX = dx(rng);
            entityY = dy(rng);
        } while (map->getCharOfMap(entityY, entityX) == '#');
        entity = e;
    }
}
