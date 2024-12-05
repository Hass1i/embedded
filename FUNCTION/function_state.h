#ifndef __fs
#define __fs

#include "GPIO_USART.h"
#include "fsm_table.h"

int process_button(void);

void LEDTest(void);
void LEDWait(void);
void LEDLow(void);
void LEDFast(void);

#endif
