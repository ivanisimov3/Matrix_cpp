#ifndef LINE_H
#define LINE_H

#include "Symbol.h"
#include "Figure.h"
#include <chrono>

class Line : public Figure
{
private:
    int x, y, iterNum, length, speed, possibility, lineLength, minRadius;
    bool rndmLineDirection, firstSymbolGenerated, justGenerated, hasLineMoved, isLeavingScreen;
    COORD coord{};
    std::chrono::steady_clock::time_point lastSymbolUpdateMoment;
    std::vector<Symbol> symbols;

    void increaseIter();
    void moveLeft();
    void moveRight();
    void incLineLen();
    void decLineLen();
    void goToBoomPosition();
    void returnToOGposition();

public:
    Line();
    void drawSelf() override;
    bool isAlive() override;
    bool shouldExplode();
    void eraseSelfSymbol();
    bool getHasMoved();
    COORD getPosition();
};

#endif