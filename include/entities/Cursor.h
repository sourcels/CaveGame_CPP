#pragma once
#include "Entity.h"

class Editor;

class Cursor : public Entity {
public:
    Cursor(int x, int y);
    void swapChar(char ch);
    void tryMoveCursor(int newY, int newX, Editor* edit);
};
