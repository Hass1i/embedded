#include "function_state.h"

uint8_t fl = 0;
u8 statBut = 0;
uint8_t current_time = 0;

void LEDWait(){
    GPIO_OFF(fl);
}

/*void LEDTest(){
    GPIO_OFF(fl);
}*/
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
      GPIO_CLCK(fl);
      Delay_Ms(100);
      j++;
      statBut = process_button();
      if (statBut != 0)
          break;
  }
  transition_table[statBut]();
}
//comment
void LEDFast(void)
{
  int j = 0;
  while (j<60){
      GPIO_CLCK(fl);
      Delay_Ms(50);
      j++;

      statBut = process_button();
      if (statBut != 0)
          break;
  }
  transition_table[statBut]();
}

int process_button(void) {
    int j = 0;

    switch(GPIO_BUTTON){
        case(0):
            Delay_Ms(200);
                while (j<301 ){

                    j++;
                    printf("CurrenTime:%d\r\n", j);
                    if (!GPIO_BUTTON)
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
