#include "debug.h"
#include "main.h"

vu8 val;
uint8_t tempIn;
uint8_t curIn;
u8 i = 0;
volatile STATE_t state = stateWait;

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
  int check = 0;
  while (j<20){
      GPIO_WriteBit(GPIOD, GPIO_Pin_4, (i == 0) ? (i = Bit_SET) : (i = Bit_RESET));
      Delay_Ms(100);
      if (!GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_7)){
          check = 1;
          break;
      }
      j++;
  }
  Delay_Ms(200);
      if (!GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_7)){
          check = 2;
      }
  switch(check){
  case(0):
          state = 0;
  break;
  case(1):
          LEDLow();
  break;
  case(2):
          LEDFast();
  break;

  }

  Delay_Ms(250);
}

void LEDFast(void)
{
  int j = 0;
  int check = 0;
  while (j<80){
      GPIO_WriteBit(GPIOD, GPIO_Pin_4, (i == 0) ? (i = Bit_SET) : (i = Bit_RESET));
      Delay_Ms(50);

      if (!GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_7)){
                check = 1;
                break;
            }
            j++;
        }
        Delay_Ms(200);
        int k = 0;
        while(k<5){
            Delay_Ms(50);
            if (!GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_7)){
                check = 2;
                break;
            }
            k++;
        }
  switch(check){
  case(0):
          state = 0;
  break;
  case(1):
          LEDLow();
  break;
  case(2):
          LEDFast();
  break;
  Delay_Ms(250);
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
    //uint8_t InStatus;
    while(1)
    {
          if (!GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_7)){
              Delay_Ms(200);
              int k = 0;
              while(k<5){
                  Delay_Ms(50);
                  if(!GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_7))
                      state = 2;
                  k++;

              }
              if(state == 0)
                  state = 1;
              /*switch(state){
              case(0):
                      state = 1;
              break;

              case(1):
                      state = 2;
              break;
              case(2):
                      state = 0;
              break;
              }*/
          }

          transition_table[state]();
     }


      /*if(state == stateWait)
          state = state + 1;
      transition_table[state][event]();*/

      /*
      Delay_Ms(500);
      GPIO_WriteBit(GPIOD, GPIO_Pin_4, (i == 0) ? (i = Bit_SET) : (i = Bit_RESET));
      */
    }


