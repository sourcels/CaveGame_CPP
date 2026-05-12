#include "entities/Person.h"
#include "core/GameMap.h"

Person::Person(char e, int x, int y) {
    entity = e; entityX = x; entityY = y;
}

void Person::tryMovePerson(int newY, int newX, GameMap* map) {
    if (newX >= 0 && newX < map->mapWidth() && newY >= 0 && newY < map->mapHeight()) {
        if (map->getCharOfMap(newY, newX) != '#') {
            entityX = newX; entityY = newY;
        }
    }
}
