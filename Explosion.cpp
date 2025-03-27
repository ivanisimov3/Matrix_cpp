#include <iostream>
#include <cmath>
#include "Explosion.h"
#include "Service.h"

Explosion::Explosion(COORD explCenter) {
    width = Service::getWidth();
    height = Service::getHeight();

    centerPos = explCenter;
    calculateRadius();
    lastExplosionUpdateMoment = std::chrono::steady_clock::now();
    curRadius = 0;
    stillExplode = true;
}

void Explosion::drawSelf() {
    auto now = std::chrono::steady_clock::now();
    auto explosionSpawnMoments = std::chrono::milliseconds(500);

    if (now - lastExplosionUpdateMoment >= explosionSpawnMoments) {
        lastExplosionUpdateMoment = now;

        if (curRadius < radius) {
            curRadius++;

            if (curRadius > 1) {    // стираю предыдущий круг
                erasePreviousRadius();
            }

            for (int dx = -curRadius; dx <= curRadius; dx++) {  // генерирую новый круг
                for (int dy = -curRadius; dy <= curRadius; dy++) {
                    if (abs(dx) + abs(dy) == curRadius) {
                        symbPos.X = centerPos.X + dx;
                        symbPos.Y = centerPos.Y + dy;

                        Symbol objSymbol(symbPos, false);
                        objSymbol.drawSelf();

                        symbols.push_back(objSymbol);
                    }
                }
            }
        }
        else {
            erasePreviousRadius();  // стираю последний круг (так как не попали в стерку предыдущего круга)
            stillExplode = false;
        }

    }
}

bool Explosion::isAlive() { // проверка на статус линии
    return stillExplode;
}

void Explosion::erasePreviousRadius() {
    for (auto symbol = symbols.begin(); symbol != symbols.end();) {
        symbol -> eraseSelf();
        symbols.erase(symbol);
    }
}

void Explosion::calculateRadius() { // определяю подходящий радиус для линии
    radius = Service::getMinRad();
    for (int iterRad = Service::getMinRad() + 1; iterRad <= Service::getMaxRad(); iterRad++) {
        if (centerPos.X - iterRad >= 0 && centerPos.X + iterRad <= width - 1 && centerPos.Y - iterRad >= 0 && centerPos.Y + iterRad <= height - 1) {
            radius++;
        }
        else
            break;  // как только условие не выполнится выходим
    }
}

// вариант для выбора случайного размера взрыва из диапазона

/*void Explosion::calculateRadius() { // определяю подходящий радиус для линии
    int minPosRad = Service::getMinRad();
    int maxPosRad = Service::getMinRad();
    for (int iterRad = Service::getMinRad() + 1; iterRad <= Service::getMaxRad(); iterRad++) {
        if (centerPos.X - iterRad >= 0 && centerPos.X + iterRad <= width - 1 && centerPos.Y - iterRad >= 0 && centerPos.Y + iterRad <= height - 1) {
            maxPosRad++;
        }
        else
            break;  // как только условие не выполнится выходим
    }
    radius = rand() % (maxPosRad - minPosRad + 1) + minPosRad;
}*/
