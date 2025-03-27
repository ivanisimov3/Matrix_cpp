#include <iostream>
#include <windows.h>
#include "Line.h"

#include "Service.h"

Line::Line() {
    width = Service::getWidth();
    height = Service::getHeight();
    length = Service::getLength();
    speed = Service::getSpeed();
    possibility = Service::getPosib();
    minRadius = Service::getMinRad();

    lastSymbolUpdateMoment = std::chrono::steady_clock::now();

    lineLength = 1;
    justGenerated = true;
    hasLineMoved = false;
    isLeavingScreen = false;

    rndmLineDirection = rand() % 2;
    x = width - 1;
    if (rndmLineDirection == 0)
        y = rand() % (height - 1);
    else
        y = rand() % (height- 1) + 1;
    iterNum = 0;
    firstSymbolGenerated = false;

    coord = getPosition();
}

void Line::drawSelf() {
    auto now = std::chrono::steady_clock::now();
    auto symbolSpawnMoments = std::chrono::milliseconds(1000 / speed);

    if (now - lastSymbolUpdateMoment >= symbolSpawnMoments) {
        lastSymbolUpdateMoment = now;

        coord = getPosition();

        if ((width - 1) - coord.X < length) {
            Symbol objSymbol(coord, true);
            objSymbol.drawSelf();

            symbols.push_back(objSymbol);

            if (justGenerated) {    // если линия только сгенерировалась, то ее длина равна 1 уже по умолчанию (такое значение переменной inLineLen), поэтому не увеличиваем счетчик
                justGenerated = false;
            }
            else
                incLineLen();

        } else if (coord.X < 0) {
            isLeavingScreen = true;    // когда линия заходит за границу экрана она не может взорваться

            symbols.front().eraseSelf();
            symbols.erase(symbols.begin());

            decLineLen();

        } else {
            symbols.front().eraseSelf();
            symbols.erase(symbols.begin());

            Symbol objSymbol(coord, true);
            objSymbol.drawSelf();
            symbols.push_back(objSymbol);
        }

        moveLeft();
        increaseIter();
        hasLineMoved = true;
    }
}

COORD Line::getPosition() {
    coord.X = x;

    if (rndmLineDirection == 0){
        if (iterNum % 2 == 0)
            coord.Y = y;
        else
            coord.Y = y + 1;
    }

    else {
        if (iterNum % 2 == 0)
            coord.Y = y;
        else
            coord.Y = y - 1;
    }

    return coord;
}

void Line::increaseIter() {
    iterNum++;
}

void Line::moveLeft() {
    x--;
}

void Line::moveRight() {
    x++;
}

bool Line::isAlive() {
    if (coord.X < -length || lineLength == 0) {
        return false;
    }

    return true;
}

bool Line::shouldExplode() {
    hasLineMoved = false;   // мы попали в этот метод, значит hasLineMoved было True. теперь обнуляем его
    if (!isLeavingScreen) {
        goToBoomPosition();
        getPosition();
        if (coord.X - minRadius >= 0 && coord.X + minRadius <= width - 1 && coord.Y - minRadius >= 0 && coord.Y + minRadius <= height - 1) {    // если есть возможность заспавнить радиус минимального размера
            returnToOGposition();
            getPosition();
            return (rand() % 1000 + 1) < possibility;
        }
        returnToOGposition();
        getPosition();
    }
    return false;
}

void Line::incLineLen() {
    lineLength++;
}

void Line::decLineLen() {
    lineLength--;
}

bool Line::getHasMoved() {
    return hasLineMoved;
}

void Line::goToBoomPosition() {
    increaseIter(); // увеличиваем iter чтобы курсор перешел на другую строку (логика зигзага) - там где был удаленный символ
    moveRight();    // двигаем курсор вправо на 1
}

void Line::returnToOGposition() {
    increaseIter();
    moveLeft();
}


void Line::eraseSelfSymbol() {
    symbols.back().eraseSelf(); // стираем последний добавленный элемент по его координате
    symbols.erase(symbols.end() - 1);   // удаляем последний добавленный элемент из вектора символов
    goToBoomPosition();
    decLineLen();   // длина линии уменьшается на 1
}