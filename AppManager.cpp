#include <iostream>
#include <windows.h>
#include <chrono>
#include <algorithm>
#include "AppManager.h"
#include "Service.h"

AppManager::AppManager() {
    system("cls");
    frequency = Service::getFrequency();
}

void AppManager::run() {

    while (true) {
        curMoment = 0;

        allLineSpawnMoments.clear();
        generateLineSpawnTime();    // точки во времени для начала генерации линии
        startTime = std::chrono::steady_clock::now();

        while (std::chrono::steady_clock::now() - startTime < std::chrono::seconds(1)) {    // цикл в 1 секунду
            timeNow = std::chrono::steady_clock::now();

            if (curMoment < allLineSpawnMoments.size()) {
                if (timeNow - startTime >= std::chrono::milliseconds(allLineSpawnMoments[curMoment])) {   // если настало время генерации линии
                    lines.emplace_back();

                    curMoment++;
                }
            }

            for (auto line = lines.begin(); line != lines.end();) { // проходимся по всем существующим линиям
                if (!line -> isAlive()) {  // линия пропала из терминала или ее размер уменьшился до 0 в результате взрывов
                    line = lines.erase(line);
                }
                else {
                    line -> drawSelf(); // говорим линии отрисовать себя если надо
                    if (line -> getHasMoved()) {    // если линия себе отрисовала один символ
                        if (line -> shouldExplode()) {  // нужно ли взорваться
                            line -> eraseSelfSymbol();  // говорим линии стереть свой первый символ
                            explosions.emplace_back(line -> getPosition()); // получаю координату центра взрыва и создаю объект взрыва
                        }
                    }
                    ++line;
                }
            }

            for (auto explosion = explosions.begin(); explosion != explosions.end();) { // проходимся по всем взрывам
                if (!explosion -> isAlive())
                    explosion = explosions.erase(explosion);
                else {
                    explosion -> drawSelf();
                    ++explosion;
                }
            }
        }
    }
}

std::vector<int> AppManager::generateLineSpawnTime() {
    everyMoment = 0;
    for (size_t i = 0; i < frequency; i++) {
        everyMoment = rand() % 1000;    // генерация случайных промежутков
        allLineSpawnMoments.push_back(everyMoment);
    }

    std::sort(allLineSpawnMoments.begin(), allLineSpawnMoments.end());

    return allLineSpawnMoments;
}