#ifndef SYMBOL_H
#define SYMBOL_H

#include <windows.h>

class Symbol {
private:
    int color, xCoord, yCoord;
    char character;
    bool isSymbolForLine;
    COORD symbCoord;
    HANDLE hConsole;

    void setColor();

public:
    Symbol(COORD, bool);
    void drawSelf();
    void eraseSelf();
};

#endif