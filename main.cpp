#include "state_machine.h"
#include <iostream>

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cout << "ERROR" << std::endl;
        return 1;
    }
    runStateMachine(argv[1]);
    return 0;
}
