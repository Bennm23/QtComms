#include <iostream>

#include "RadarController.h"

// #include "ZeroChannel.cpp"
#include "ZeroChannel.h"

int main() {

    ZeroChannel zc;
    zc.runInBackground();

    std::cout << "Hello Backend" << std::endl;

    RadarController rc;
    rc.start();

}