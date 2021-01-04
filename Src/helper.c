#include "helper.h"

void delay_us(uint16_t time){
	HAL_TIM_Base_Start(&US_TIMER);
	__HAL_TIM_SET_COUNTER(&US_TIMER,0);
	while(__HAL_TIM_GET_COUNTER(&US_TIMER) < time);
	HAL_TIM_Base_Stop(&US_TIMER);
}