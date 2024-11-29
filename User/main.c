#include "debug.h"
#include <stdbool.h>
#include "function_state.h"
#include "GPIO_USART.h"


u8 statusB = 0;
volatile STATE_t state = stateWait;

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


