#ifndef __gu
#define __gu

#include "debug.h"

#define DOUBLE_CLICK_TIME_MS 300

#define LED_BUT_PORT GPIOD
#define LED_PIN GPIO_Pin_4

#define BUT_PIN GPIO_Pin_7

#define RX_PIN GPIO_Pin_5
#define TX_PIN GPIO_Pin_6

#define GPIO_BUTTON GPIO_ReadInputDataBit(LED_BUT_PORT, BUT_PIN)
#define GPIO_OFF(i) GPIO_WriteBit(LED_BUT_PORT, LED_PIN, (i = Bit_SET))
#define GPIO_CLCK(i) GPIO_WriteBit(LED_BUT_PORT, LED_PIN, (i == 0) ? (i = Bit_SET) : (i = Bit_RESET))

void USARTx_CFG(void);
#endif
