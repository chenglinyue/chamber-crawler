#include "controller.h"
#include <stdlib.h>
using namespace std;

int main (int argc, char* argv[]) {
    srand (time(NULL));

    if (argc == 2) {
        string filename = argv[1];
        Controller controller(filename);
        controller.initializeControllerNotRandom();
    } else {
        Controller controller;
        controller.initializeControllerRandom();
    }
}
