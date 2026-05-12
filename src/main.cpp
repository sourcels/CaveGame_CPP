#include <iostream>
#include <vector>
#include <string>
#include <thread>
#include <chrono>
#include <memory>

#include "Platform.h"
#include "core/GameMap.h"
#include "core/Render.h"
#include "core/GUI.h"
#include "core/GetInput.h"
#include "entities/Entity.h"
#include "entities/Person.h"
#include "entities/Monster.h"
#include "entities/Light.h"
#include "entities/ExitSymbol.h"
#include "entities/Cursor.h"
#include "menu/Settings.h"
#include "menu/GameMenu.h"
#include "menu/ModeSelect.h"
#include "edit/Editor.h"

int main(int argc, char* argv[]) {
    Platform::init();
    Platform::setTitle("CaveGame C++");
    Platform::hideCursor();
    Platform::setWindowSize(122, 30);

    while (true) {
        GameMenu menu;
        Settings set;
        GameMap map; 
        
        auto person = std::make_shared<Person>('@', 1, 1);
        
        GetInput input;
        GUI gui;
        Render render;
        Editor edit;
        ModeSelect mode;

        Platform::clearScreen();
        int menuChoice = menu.getInputMenu();

        if (menuChoice == 0) { // play
            Platform::clearScreen();

            GameMap map; 

            auto person = std::make_shared<Person>('@', 1, 1);
            auto exitSym = std::make_shared<ExitSymbol>(&map);
            auto light = std::make_shared<Light>(&map, '*');
            
            std::vector<std::shared_ptr<Entity>> entities;
            entities.push_back(person);
            entities.push_back(exitSym);
            entities.push_back(light);

            for (int i = 0; i < Settings::selectedQuantity; i++) {
                entities.push_back(std::make_shared<Monster>(&map));
            }

            render.fieldOnScreen = false;
            Platform::flushKeys();

            bool manualExit = false;

            while (!exitSym->endOfGame() && person->isAlive) {
                gui.fpsCounter();

                input.getGameInput(person.get(), &map, &render);
                person->checkCollisions(entities, &render);

                for (auto& ent : entities) {
                    if (auto m = std::dynamic_pointer_cast<Monster>(ent)) {
                        m->updatePosition(person.get(), &map);
                    }
                }

                render.draw(&map, person.get(), entities);
                gui.showFPS();

                if (Platform::isKeyDown(27)) {
                    manualExit = true;
                    break; 
                }
            }
            
            if (!person->isAlive) {
                Platform::clearScreen();
                printf("GAME OVER! MONSTER CAUGHT YOU!");
                Platform::sleepMs(2000);
            } 
            else if (!manualExit && exitSym->endOfGame()) {
                Platform::clearScreen();
                printf("YOU WIN!");
                Platform::sleepMs(2000);
            }
        }
        else if (menuChoice == 1) {
            set.getInputSettings();
        }
        else if (menuChoice == 2) {
            Platform::clearScreen();
            edit.clearMap();
            
            Cursor cursor(0, 0);
            while (true) {
                render.drawOnlyMap(edit.customMap, &cursor, &edit);
                input.getEditorInput(&edit, &cursor);

                if (!edit.switchActiveInput) {
                    int res = edit.getInputRedactor();
                    if (res == 0) {
                        edit.saveMap("map1.txt");
                        Platform::clearScreen();
                        break; 
                    } else if (res == 1) { // exit
                        Platform::clearScreen();
                        break;
                    } else {
                        edit.switchActiveInput = true;
                    }
                }
            }
        }
        else if (menuChoice == 3) { // exit
            break;
        }
    }

    Platform::showCursor();
    return 0;
}