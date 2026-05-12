#include "entities/Entity.h"
#include "entities/Person.h"
#include "entities/Light.h"
#include "entities/Monster.h"
#include "entities/ExitSymbol.h"
#include "core/GameMap.h"
#include "core/Render.h"
#include "menu/Settings.h"
#include <cmath>
#include <algorithm>
#include <cstdlib>

std::mt19937 Entity::rng(std::random_device{}());

Entity::Entity()
    : entity(' '), entityX(0), entityY(0),
      lastEntityX(0), lastEntityY(0),
      lastMoveTime(std::chrono::steady_clock::now()) 
{}

void Entity::personLastPosition() {
    lastEntityX = entityX;
    lastEntityY = entityY;
}

void Entity::setPosition(int x, int y) {
    entityX = x; entityY = y;
}

bool Entity::vcContains(std::pair<int,int> p) {
    for (auto& c : visitedCells) if (c == p) return true;
    return false;
}

void Entity::updatePosition(Person* player, GameMap* map) {
    auto now = std::chrono::steady_clock::now();
    double elapsed = std::chrono::duration<double>(now - lastMoveTime).count();

    //printf("Elapsed: %.2f | Needed: 0.5\n", elapsed); 

    if (elapsed < 0.5) return; 

    lastMoveTime = now;

    //printf("Monster %c is thinking about moving...\n", entity);

    int distToPlayer = std::abs(entityX - player->entityX) + std::abs(entityY - player->entityY);

    visitedCells.push_back({entityX, entityY});
    if ((int)visitedCells.size() > memorySize) visitedCells.pop_front();

    std::vector<std::pair<int,int>> directions;

    for (int dx = -1; dx <= 1; dx++) {
        for (int dy = -1; dy <= 1; dy++) {
            if (dx == 0 && dy == 0) continue;
            int nx = entityX + dx, ny = entityY + dy;
            if (nx >= 0 && nx < map->mapWidth() && ny >= 0 && ny < map->mapHeight()
                && map->getCharOfMap(ny, nx) != '#') {
                directions.push_back({nx, ny});
            }
        }
    }

    if (directions.empty()) return;

    std::pair<int,int> nextStep = {-1, -1};

    if (distToPlayer <= visionRadius) {
        std::sort(directions.begin(), directions.end(), [&](const auto& a, const auto& b){
            int da = std::abs(a.first - player->entityX) + std::abs(a.second - player->entityY);
            int db = std::abs(b.first - player->entityX) + std::abs(b.second - player->entityY);
            return da < db;
        });
        for (auto& m : directions) {
            if (!vcContains(m)) { nextStep = m; break; }
        }
        if (nextStep.first == -1) nextStep = directions[0];
    } else {
        std::vector<std::pair<int,int>> fresh;
        for (auto& m : directions) if (!vcContains(m)) fresh.push_back(m);
        if (!fresh.empty()) {
            std::uniform_int_distribution<int> d(0, (int)fresh.size()-1);
            nextStep = fresh[d(rng)];
        } else {
            std::uniform_int_distribution<int> d(0, (int)directions.size()-1);
            nextStep = directions[d(rng)];
        }
    }

    entityX = nextStep.first;
    entityY = nextStep.second;
}

void Entity::checkCollisions(std::vector<std::shared_ptr<Entity>>& list, Render* render) {
    for (auto& ent : list) {
        if (ent.get() == this) continue;
        if (ent->entityX != entityX || ent->entityY != entityY) continue;

        if (auto exit = std::dynamic_pointer_cast<ExitSymbol>(ent)) {
            exit->win = true;
        }

        if (auto light = std::dynamic_pointer_cast<Light>(ent)) {
            render->activateVision();
        }

        if (auto monster = std::dynamic_pointer_cast<Monster>(ent)) {
            Person* p = dynamic_cast<Person*>(this);
            if (p) {
                p->isAlive = false;
            } 
        }
    }
}