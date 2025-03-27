#include <iostream>
#include "AppManager.h"
#include "Service.h"

int main(int argc, char* argv[]) {
    Service service;
    if (service.processArguments(argc, argv)) {
        AppManager app;
        app.run();
    } else {
        return 1;
    }
}