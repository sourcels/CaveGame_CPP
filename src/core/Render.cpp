#include "core/Render.h"
#include "core/GameMap.h"
#include "entities/Person.h"
#include "entities/Light.h"
#include "entities/Monster.h"
#include "entities/ExitSymbol.h"
#include "entities/Cursor.h"
#include "edit/Editor.h"
#include "menu/Settings.h"
#include "Platform.h"
#include <cstdio>
#include <cmath>

Render::Render()
    : visionFlag(Settings::selectedRender),
      fieldOnScreen(false),
      lightEnd(std::chrono::steady_clock::time_point::min())
{}

void Render::cheat() {
    Platform::clearScreen();
    visionFlag = !visionFlag;
    if (visionFlag)
        lightEnd = std::chrono::steady_clock::now() + std::chrono::hours(8760);
    else
        lightEnd = std::chrono::steady_clock::time_point::min();
}

void Render::activateVision() {
    lightEnd = std::chrono::steady_clock::now() + std::chrono::seconds(5);
    visionFlag = true;
}

void Render::draw(GameMap* map, Person* person, std::vector<std::shared_ptr<Entity>>& list) {
    if (!Settings::selectedRender) {
        if (visionFlag && std::chrono::steady_clock::now() > lightEnd) {
            visionFlag = false;
            Platform::clearScreen();
        }
    }

    if (visionFlag) {
        if (!fieldOnScreen) {
            for (int y = 0; y < map->mapHeight(); y++) {
                for (int x = 0; x < map->mapWidth(); x++)
                    putchar(map->getCharOfMap(y, x));
                if (y < map->mapHeight() - 1) putchar('\n');
            }
            fflush(stdout);
        }
        fieldOnScreen = true;

        for (auto& ent : list) {
            if (auto p = std::dynamic_pointer_cast<Person>(ent)) {
                Platform::setCursorPos(person->entityX, person->entityY);
                Platform::colorGreen();
                putchar(person->entity);
                Platform::colorReset();
                fflush(stdout);
                if (person->entityX != person->lastEntityX || person->entityY != person->lastEntityY) {
                    Platform::setCursorPos(person->lastEntityX, person->lastEntityY);
                    putchar(map->getCharOfMap(person->lastEntityY, person->lastEntityX));
                    fflush(stdout);
                }
            } else if (auto light = std::dynamic_pointer_cast<Light>(ent)) {
                if (light->entityX >= 0 && light->entityY >= 0) {
                    Platform::setCursorPos(light->entityX, light->entityY);
                    Platform::colorYellow();
                    putchar(light->entity);
                    Platform::colorReset();
                    fflush(stdout);
                }
            } else if (auto monster = std::dynamic_pointer_cast<Monster>(ent)) {
                Platform::setCursorPos(monster->entityX, monster->entityY);
                Platform::colorDarkRed();
                putchar(monster->entity);
                Platform::colorReset();
                fflush(stdout);
                if (monster->entityX != monster->lastEntityX || monster->entityY != monster->lastEntityY) {
                    Platform::setCursorPos(monster->lastEntityX, monster->lastEntityY);
                    putchar(map->getCharOfMap(monster->lastEntityY, monster->lastEntityX));
                    fflush(stdout);
                }
            } else if (auto exitSym = std::dynamic_pointer_cast<ExitSymbol>(ent)) {
                Platform::setCursorPos(exitSym->entityX, exitSym->entityY);
                Platform::colorRed();
                putchar(exitSym->entity);
                Platform::colorReset();
                fflush(stdout);
            }
        }
    } else {
        fieldOnScreen = false;
        std::vector<std::pair<int,int>> drawnCoords;

        for (auto& ent : list) {
            if (std::abs(ent->entityX - person->entityX) < 4 &&
                std::abs(ent->entityY - person->entityY) < 4) {

                drawnCoords.push_back({ent->entityX, ent->entityY});
                Platform::setCursorPos(ent->entityX, ent->entityY);

                if (std::dynamic_pointer_cast<Person>(ent))      { Platform::colorGreen();   }
                else if (std::dynamic_pointer_cast<Light>(ent))  { Platform::colorYellow();  }
                else if (std::dynamic_pointer_cast<Monster>(ent)){ Platform::colorDarkRed(); }
                else if (std::dynamic_pointer_cast<ExitSymbol>(ent)){ Platform::colorRed();  }

                putchar(ent->entity);
                Platform::colorReset();
                fflush(stdout);
            }
        }

        for (int dy = -4; dy <= 4; dy++) {
            for (int dx = -4; dx <= 4; dx++) {
                int ny = person->entityY + dy;
                int nx = person->entityX + dx;
                if (ny < 0 || ny >= map->mapHeight() || nx < 0 || nx >= map->mapWidth()) continue;

                bool occupied = false;
                for (auto& c : drawnCoords) if (c.first == nx && c.second == ny) { occupied = true; break; }
                if (occupied) continue;

                Platform::setCursorPos(nx, ny);
                if (dy == -4 || dy == 4 || dx == -4 || dx == 4)
                    putchar(' ');
                else
                    putchar(map->getCharOfMap(ny, nx));
            }
        }
        fflush(stdout);
    }
}

void Render::drawOnlyMap(const std::vector<std::string>& mapData, Cursor* cursor, Editor* edit) {
    if (!fieldOnScreen) {
        for (int y = 0; y < (int)mapData.size(); y++) {
            for (int x = 0; x < (int)mapData[y].size(); x++)
                putchar(mapData[y][x]);
            if (y < (int)mapData.size() - 1) putchar('\n');
        }
        fflush(stdout);
    }
    fieldOnScreen = true;

    Platform::setCursorPos(cursor->entityX, cursor->entityY);
    Platform::colorRed();
    putchar(cursor->entity);
    Platform::colorReset();
    fflush(stdout);

    if (cursor->entityX != cursor->lastEntityX || cursor->entityY != cursor->lastEntityY) {
        Platform::setCursorPos(cursor->lastEntityX, cursor->lastEntityY);
        putchar(edit->getCharOfCustomMap(cursor->lastEntityY, cursor->lastEntityX));
        fflush(stdout);
    }
}
