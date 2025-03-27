#include <windows.h>
#include <iostream>
#include <limits>
#include "Service.h"

int Service::width = 80;
int Service::height = 80;
HANDLE Service::hConsole;
int Service::frequency = 1; // По умолчанию 1 линия в секунду
int Service::speed= 1;
int Service::length = 1;
int Service::possibility = 1;
int Service::minRad = 1;
int Service::maxRad = 1;
bool Service::epilepsyMode = false;

Service::Service() {
    system("cls");

    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 15);
    getConsoleSize();
    hideCursor();
    srand(time(nullptr));
}

void Service::getConsoleSize() {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    height = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
    width = csbi.srWindow.Right - csbi.srWindow.Left + 1;
}

void Service::hideCursor() {
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(hConsole, &cursorInfo);
    cursorInfo.bVisible = FALSE;
    SetConsoleCursorInfo(hConsole, &cursorInfo);
}

bool Service::processArguments(int argc, char* argv[]) {
    if (argc == 8) {
        if (!isValidInteger(argv[1]) || !isValidInteger(argv[2]) || !isValidInteger(argv[3]) || !isValidInteger(argv[4]) || !isValidInteger(argv[5]) || !isValidInteger(argv[6])) {
            errorInput();
            return false;
        }

        frequency = std::stoi(argv[1]);
        speed = std::stoi(argv[2]);
        length = std::stoi(argv[3]);
        possibility = std::stoi(argv[4]);
        minRad = std::stoi(argv[5]);
        maxRad = std::stoi(argv[6]);
        epilepsyArg = argv[7];

        if (frequency < 1 || frequency > 30 || speed < 1 || speed > 30 || length < 1 || length > 30 || possibility < 1 || possibility > 1000 || minRad < 1 || minRad > 10 || maxRad < minRad || maxRad > 10) {
            errorInput();
            return false;
        }

        if (epilepsyArg == "Y") {
            epilepsyMode = true;
        } else if (epilepsyArg == "N") {
            epilepsyMode = false;
        } else {
            errorInput();
            return false;
        }

        return true;
    } else if (argc == 1) {
        return dialogRequest();
    } else if (argc == 2) {
        if (std::string(argv[1]) == "--help" || std::string(argv[1]) == "/?") {
            displayHelp();
            return false;
        } else {
            errorInput();
            return false;
        }
    } else {
        std::cout << "Неверное количество аргументов. Для помощи --help" << std::endl;
        return false;
    }
}

bool Service::dialogRequest() {
    welcomeMessage();

    askFrequency();
    while (frequency < 1 || frequency > 30 || std::cin.fail() || std::cin.peek() != '\n') {
        errorInput();
        clearCin();
        askFrequency();
    }

    askSpeed();
    while (speed < 1 || speed > 30 || std::cin.fail() || std::cin.peek() != '\n') {
        errorInput();
        clearCin();
        askSpeed();
    }

    askLen();
    while (length < 1 || length > 30 || std::cin.fail() || std::cin.peek() != '\n') {
        errorInput();
        clearCin();
        askLen();
    }

    askPosib();
    while (possibility < 1 || possibility > 1000 || std::cin.fail() || std::cin.peek() != '\n') {
        errorInput();
        clearCin();
        askPosib();
    }

    askMinRad();
    while (minRad < 1 || minRad > 10 || std::cin.fail() || std::cin.peek() != '\n') {
        errorInput();
        clearCin();
        askMinRad();
    }

    askMaxRad();
    while (maxRad < minRad || maxRad > 10 || std::cin.fail() || std::cin.peek() != '\n') {
        errorInput();
        clearCin();
        askMaxRad();
    }

    askEp();
    while (epilepsyArg != "Y" && epilepsyArg != "N") {
        errorInput();
        clearCin();
        askEp();
    }

    if (epilepsyArg == "Y") {
        epilepsyMode = true;
    } else if (epilepsyArg == "N") {
        epilepsyMode = false;
    }

    return true;
}

bool Service::isValidInteger(const char* str) {
    while (*str) {
        if (!std::isdigit(*str))
            return false;
        str++;
    }
    return true;
}

void Service::askFrequency() {
    std::cout << "Введите частоту появления линий: ";
    std::cin >> frequency;
}

void Service::askSpeed() {
    std::cout << "Введите количество символов в секунду: ";
    std::cin >> speed;
}

void Service::askLen() {
    std::cout << "Введите количество символов: ";
    std::cin >> length;
}

void Service::askPosib() {
    std::cout << "Введите вероятность взрыва: ";
    std::cin >> possibility;
}

void Service::askMinRad() {
    std::cout << "Введите минимальный радиус взрыва: ";
    std::cin >> minRad;
}

void Service::askMaxRad() {
    std::cout << "Введите максимальный радиус взрыва: ";
    std::cin >> maxRad;
}

void Service::askEp() {
    std::cout << "Хотите включить режим эпилепсии?: ";
    std::cin >> epilepsyArg;
}

void Service::errorInput() {
    std::cout << "Ошибка, введено некорректное значение. Для помощи введите --help" << std::endl;
}

void Service::clearCin() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int Service::getWidth() {
    return width;
}

int Service::getHeight(){
    return height;
}

HANDLE Service::getHandle(){
    return hConsole;
}

int Service::getFrequency() {
    return frequency;
}

int Service::getSpeed() {
    return speed;
}
int Service::getLength() {
    return length;
}

int Service::getPosib() {
    return possibility;
}

int Service::getMinRad() {
    return minRad;
}

int Service::getMaxRad() {
    return maxRad;
}

bool Service::getEpilepsyMode(){
    return epilepsyMode;
}

void Service::displayHelp() {
    std::cout << "Использование: _1.exe <число линий> <скорость линий> <длина линий> <вероятность взрыва> <минимальный радиус> <максимальный радиус> <режим эпилепсии> \n";
    std::cout << "Где:\n";
    std::cout << "  число линий - частота появления линий в секунду (от 1 до 30)\n";
    std::cout << "  скорость линий - количество символов в секунду (от 1 до 30)\n";
    std::cout << "  длина линий - количество символов (от 1 до 30)\n";
    std::cout << "  вероятность взрыва - шанс уничтожения первого символа линии (от 1 до 1000)\n";
    std::cout << "  минимальный радиус - минимальный размер, которой может быть окружность (от 1 до 10)\n";
    std::cout << "  максимальный радиус - максимальный размер, которой может быть окружность (от 1 до 10, НО НЕ МЕНЬШЕ минимального радиуса)\n";
    std::cout << "  режим эпилепсии - включить режим эпилепсии (Y - включить, N - выключить)\n";
    std::cout << "\nПримеры:\n";
    std::cout << "  _1.exe 10 23 8 150 3 8 Y\n";
    std::cout << "  _1.exe /?\n";
    std::cout << "  _1.exe\n";
}

void Service::welcomeMessage() {
    greeting = "Добро пожаловать в программу Matrix!";
    messageLength = greeting.length();
    x = (getWidth() - messageLength / 2) / 2;
    y = getHeight() / 2 - 2;

    // Перемещаем курсор и выводим сообщение
    COORD pos;
    pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(hConsole, pos);
    std::cout << "====================================";

    pos.Y++;
    SetConsoleCursorPosition(hConsole, pos);
    std::cout << "                                    ";

    pos.Y++;
    SetConsoleCursorPosition(hConsole, pos);
    std::cout << greeting;

    pos.Y++;
    SetConsoleCursorPosition(hConsole, pos);
    std::cout << "                                    ";

    pos.Y++;
    SetConsoleCursorPosition(hConsole, pos);
    std::cout << "====================================";

    // Задержка на 3 секунды
    Sleep(3000);

    system("cls");
}