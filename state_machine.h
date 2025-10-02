#ifndef STATE_MACHINE_H
#define STATE_MACHINE_H

enum class State {
    INIT,
    PARSE,
    CALCULATE,
    PRINT,
    EXIT,
    ERROR
};

void runStateMachine(const char* filepath);

#endif
