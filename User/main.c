#include "debug.h"
#include "main.h"
#include <stdbool.h>

#define DOUBLE_CLICK_TIME_MS 300

volatile uint32_t last_press_time = 0;
volatile int current_time = 0;
volatile uint8_t click_count = 0;

vu8 val;
uint8_t tempIn;
uint8_t curIn;
u8 i = 0;
u8 statusB = 0;
volatile STATE_t state = stateWait;

void (*const transition_table[st])(void);
void LEDWait(void);
void LEDLow(void);
void LEDFast(void);
int process_button(void);
int process_button_inState(int);
bool SysTick_Handler(void);


void USARTx_CFG(void)
{

    GPIO_InitTypeDef  GPIO_InitStructure = {0};
    USART_InitTypeDef USART_InitStructure = {0};

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD | RCC_APB2Periph_USART1, ENABLE);

    /* USART1 TX-->D.5   RX-->D.6 */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_30MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(GPIOD, &GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_Init(GPIOD, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_30MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOD, &GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOD, &GPIO_InitStructure);

    USART_InitStructure.USART_BaudRate = 115200;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;

    USART_Init(USART1, &USART_InitStructure);
    USART_Cmd(USART1, ENABLE);
}


void LEDWait(){
    GPIO_WriteBit(GPIOD, GPIO_Pin_4, (i = Bit_SET));
}
/*void LEDLow(void)
{
  state = 0;
  while (1){
      Delay_Ms(150);
      GPIO_WriteBit(GPIOD, GPIO_Pin_4, (i == 0) ? (i = Bit_SET) : (i = Bit_RESET));
      if (!GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_7)){
          break;
      }
  }
  Delay_Ms(250);
}

void LEDFast(void)
{
  state = 0;
  while (1){
      Delay_Ms(50);
      GPIO_WriteBit(GPIOD, GPIO_Pin_4, (i == 0) ? (i = Bit_SET) : (i = Bit_RESET));
      if (!GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_7)){
          break;
      }
  }
  Delay_Ms(250);
}*/

void LEDLow(void)
{
  int j = 0;
  while (j<30){
      GPIO_WriteBit(GPIOD, GPIO_Pin_4, (i == 0) ? (i = Bit_SET) : (i = Bit_RESET));
      Delay_Ms(100);
      j++;
      statusB = process_button();
      if (statusB != 0)
          break;
  }
  transition_table[statusB]();
}

void LEDFast(void)
{
  int j = 0;
  while (j<60){
      GPIO_WriteBit(GPIOD, GPIO_Pin_4, (i == 0) ? (i = Bit_SET) : (i = Bit_RESET));
      Delay_Ms(50);
      j++;

      statusB = process_button();
      if (statusB != 0)
          break;
  }
  transition_table[statusB]();
}


// §¶§å§ß§Ü§è§Ú§ñ §Õ§Ý§ñ §ã§é§Ú§ä§í§Ó§Ñ§ß§Ú§ñ §ã§à§ã§ä§à§ñ§ß§Ú§ñ §Ü§ß§à§á§Ü§Ú
int process_button(void) {
    int j = 0;

    switch(GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_7)){
        case(0):
            Delay_Ms(200);
                while (j<301 ){

                    j++;
                    printf("CurrenTime:%d\r\n", j);
                    if (!GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_7))
                        break;
                }

                if (j < DOUBLE_CLICK_TIME_MS){
                    Delay_Ms(150);
                    return stateFast;
                }
                else {
                    Delay_Ms(150);
                    return stateLow;
                }
                current_time = 0;


        break;

        default:
                return stateWait;
        break;
    }

}


void (*const transition_table[st])(void)= {
    [stateWait] = LEDWait,
    [stateLow]  = LEDLow,
    [stateFast] = LEDFast,
};
int main(void)
{
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
    SystemCoreClockUpdate();
    Delay_Init();
#if (SDI_PRINT == SDI_PR_OPEN)
    SDI_Printf_Enable();
#else
    USART_Printf_Init(115200);
#endif
    printf("SystemClk:%d\r\n",SystemCoreClock);
    printf( "ChipID:%08x\r\n", DBGMCU_GetCHIPID() );
    USARTx_CFG();

    while (1) {
            statusB = process_button();
            transition_table[statusB]();
       }

    }


