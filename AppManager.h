#ifndef APPMANAGER_H
#define APPMANAGER_H

#include <vector>
#include "Line.h"
#include "Explosion.h"

class AppManager {
private:
    int frequency, length, width, everyMoment;
    size_t curMoment;
    std::vector <Line> lines;
    std::vector <Explosion> explosions;
    std::vector <int> allLineSpawnMoments;
    std::chrono::steady_clock::time_point startTime, timeNow;

    std::vector<int> generateLineSpawnTime();

public:
    AppManager();
    void run();
};

#endif