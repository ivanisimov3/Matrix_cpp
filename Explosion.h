#ifndef EXPLOSION_H
#define EXPLOSION_H

#include "Figure.h"
#include "Symbol.h"
#include <windows.h>
#include <chrono>

class Explosion : public Figure
{
private:
    COORD centerPos, symbPos;
    int radius, curRadius;
    bool stillExplode;
    std::chrono::steady_clock::time_point lastExplosionUpdateMoment;
    std::vector<Symbol> symbols;

    void calculateRadius();
    void erasePreviousRadius();

public:
    Explosion(COORD);
    void drawSelf() override;
    bool isAlive() override;
};



#endif //EXPLOSION_H
