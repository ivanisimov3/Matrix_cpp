#include <iostream>
#include <windows.h>
#include "Symbol.h"
#include "Service.h"

Symbol::Symbol(COORD position, bool flag) {
    hConsole = Service::getHandle();
    isSymbolForLine = flag;

    character = rand() % 94 + 33;
    symbCoord = position;
}

void Symbol::setColor() {
    if (isSymbolForLine) {
        if (Service::getEpilepsyMode())
            color = (rand() % 15) + 1;
        else
            color = 2;
    }
    else
        color = (rand() % 15) + 1;


    SetConsoleTextAttribute(hConsole, color);
}

void Symbol::drawSelf() {
    setColor();

    SetConsoleCursorPosition(hConsole, symbCoord);

    std::cout << character;
}

void Symbol::eraseSelf() {
    SetConsoleCursorPosition(hConsole, symbCoord);

    character = ' ';
    std::cout << character;
}
