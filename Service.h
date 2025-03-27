#ifndef SERVICE_H
#define SERVICE_H

#include <windows.h>
#include <string>

class Service {
private:
    static HANDLE hConsole;
    std::string epilepsyArg, greeting;
    static bool epilepsyMode;
    static int frequency, speed, length, possibility, minRad, maxRad, height, width;
    int x, y, messageLength;

    void getConsoleSize();
    void hideCursor();
    bool isValidInteger(const char*);
    void displayHelp();
    void askFrequency();
    void askSpeed();
    void askLen();
    void askPosib();
    void askMinRad();
    void askMaxRad();
    void askEp();
    void errorInput();
    void clearCin();
    bool dialogRequest();
    void welcomeMessage();

public:
    Service();
    bool processArguments(int argc, char* argv[]);
    static int getWidth();
    static int getHeight();
    static int getFrequency(); // Геттер для частоты
    static int getSpeed();
    static int getLength();
    static int getPosib();
    static int getMinRad();
    static int getMaxRad();
    static bool getEpilepsyMode();
    static HANDLE getHandle();
};

#endif