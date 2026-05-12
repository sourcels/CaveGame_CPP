#include "core/GetInput.h"
#include "entities/Person.h"
#include "core/GameMap.h"
#include "core/Render.h"
#include "edit/Editor.h"
#include "entities/Cursor.h"
#include "Platform.h"

GetInput::GetInput()
    : lastMoveTime(std::chrono::steady_clock::now()),
      lastSwitchTime(std::chrono::steady_clock::now())
{}

void GetInput::getGameInput(Person* person, GameMap* map, Render* render) {
    auto now = std::chrono::steady_clock::now();
    if (std::chrono::duration<double>(now - lastMoveTime).count() * 1000 < 100) return;

    person->personLastPosition();
    bool moved = false;

    if (Platform::isKeyDown(0x57)) { person->tryMovePerson(person->entityY-1, person->entityX, map); moved=true; }
    if (Platform::isKeyDown(0x53)) { person->tryMovePerson(person->entityY+1, person->entityX, map); moved=true; }
    if (Platform::isKeyDown(0x41)) { person->tryMovePerson(person->entityY, person->entityX-1, map); moved=true; }
    if (Platform::isKeyDown(0x44)) { person->tryMovePerson(person->entityY, person->entityX+1, map); moved=true; }

    if (Platform::isKeyDown(0x20)) {
        render->cheat();
        Platform::sleepMs(200);
    }

    if (moved) lastMoveTime = std::chrono::steady_clock::now();
    Platform::flushKeys();
}

void GetInput::getEditorInput(Editor* edit, Cursor* cursor) {
    auto now = std::chrono::steady_clock::now();
    if (std::chrono::duration<double>(now - lastMoveTime).count() * 1000 < 100) return;

    cursor->personLastPosition();
    bool moved = false;

    if (Platform::isKeyDown(0x57)) { cursor->tryMoveCursor(cursor->entityY-1, cursor->entityX, edit); moved=true; }
    if (Platform::isKeyDown(0x53)) { cursor->tryMoveCursor(cursor->entityY+1, cursor->entityX, edit); moved=true; }
    if (Platform::isKeyDown(0x41)) { cursor->tryMoveCursor(cursor->entityY, cursor->entityX-1, edit); moved=true; }
    if (Platform::isKeyDown(0x44)) { cursor->tryMoveCursor(cursor->entityY, cursor->entityX+1, edit); moved=true; }

    auto nowSwitch = std::chrono::steady_clock::now();
    if (Platform::isKeyDown(0x51)) {
        if (std::chrono::duration<double>(nowSwitch - lastSwitchTime).count() * 1000 >= 200) {
            cursor->swapChar(edit->switchSymbol());
            lastSwitchTime = nowSwitch;
        }
    }
    if (Platform::isKeyDown(0x45)) {
        if (std::chrono::duration<double>(nowSwitch - lastSwitchTime).count() * 1000 >= 200) {
            cursor->swapChar('\xDB'); // block char (ASCII 219)
            lastSwitchTime = nowSwitch;
        }
    }
    if (Platform::isKeyDown(0x20)) {
        if (cursor->entity == '\xDB') edit->tryErase(cursor->entityY, cursor->entityX);
        else                          edit->tryDraw(cursor->entityY, cursor->entityX);
    }
    if (Platform::isKeyDown(0x09)) {
        edit->switchActiveInput = false;
    }

    if (moved) lastMoveTime = std::chrono::steady_clock::now();
    Platform::flushKeys();
}
