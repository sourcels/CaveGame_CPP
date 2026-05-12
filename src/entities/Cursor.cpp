#include "entities/Cursor.h"
#include "edit/Editor.h"

Cursor::Cursor(int x, int y) {
    entity = '#'; entityX = x; entityY = y;
}

void Cursor::swapChar(char ch) {
    entity = ch;
}

void Cursor::tryMoveCursor(int newY, int newX, Editor* edit) {
    if (newX >= 0 && newX < edit->MAP_WIDTH && newY >= 0 && newY < edit->MAP_HEIGHT) {
        entityX = newX; entityY = newY;
    }
}
