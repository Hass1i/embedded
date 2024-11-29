#include "fsm_table.h"

void (*const transition_table[st])(void) = {
    [stateWait] = LEDWait,
    [stateLow]  = LEDLow,
    [stateFast] = LEDFast,
};
