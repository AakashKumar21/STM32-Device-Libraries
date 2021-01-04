#ifndef INC_HELPER_H_
#define INC_HELPER_H_

#include "main.h"
// set correct timer handle here
extern TIM_HandleTypeDef htim1;
#define US_TIMER htim1

void delay_us(uint16_t time);

#endif