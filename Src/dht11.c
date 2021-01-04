#include "dht11.h"

DHT11_Status DHT11_read(GPIO_TypeDef* port, uint16_t pin, 
                        uint8_t* temp, uint8_t *hum){
    // REQUEST SIGNAL
	_set_as_output(port,pin);
    HAL_GPIO_WritePin(port, pin, GPIO_PIN_RESET);
    delay_us(19000);
    HAL_GPIO_WritePin(port, pin, GPIO_PIN_SET);
    delay_us(20);
    _set_as_input(port,pin);

	// READ RESPONSE
	delay_us(40);
	if (! HAL_GPIO_ReadPin(port, pin)){ // If 0 is read
		delay_us(80);
		if(! HAL_GPIO_ReadPin(port, pin)) // If its still 0 means no response from dht11
		return DHT11_Timeout;
	}
	else return DHT11_Timeout;

	// Timer for timeout management
	HAL_TIM_Base_Start(&US_TIMER);
	__HAL_TIM_SET_COUNTER(&US_TIMER, 0);
	// wait for the pin to go low
	while (HAL_GPIO_ReadPin(port, pin) &&
		   __HAL_TIM_GET_COUNTER(&US_TIMER) < TIMEOUT);
	if(__HAL_TIM_GET_COUNTER(&US_TIMER) > TIMEOUT){
		return DHT11_Timeout;
	}
	HAL_TIM_Base_Stop(&US_TIMER);

	// READ DATA
	*temp = _read_byte(port,pin);
	_read_byte(port,pin); // ignore decimal part
	*hum = _read_byte(port,pin);
	_read_byte(port,pin); // ignore decimal part
	uint8_t checksum =  _read_byte;
	if(checksum == *temp+*hum) return DHT11_OK;
	else DHT11_Checksum_Error;

	// Set pin as output and high
	_set_as_output(port,pin);
	HAL_GPIO_WritePin(port,pin,GPIO_PIN_SET);
}

static uint8_t _read_byte(GPIO_TypeDef* port, uint16_t pin){
	volatile uint8_t byte;
	HAL_TIM_Base_Start(&US_TIMER);
	__HAL_TIM_SET_COUNTER(&US_TIMER,0);
	for (int i=0; i<8; i++)
	{
		// wait for the pin to go high
		while (!(HAL_GPIO_ReadPin (port, pin)) &&
				__HAL_TIM_GET_COUNTER(&US_TIMER) < LONG_TIMEOUT );
		if(__HAL_TIM_GET_COUNTER(&US_TIMER) > LONG_TIMEOUT) return DHT11_Timeout;
		// wait for 40 us
		delay_us (40);
		if (!(HAL_GPIO_ReadPin (port, pin)) && // if the pin is low
			__HAL_TIM_GET_COUNTER(&US_TIMER) < LONG_TIMEOUT ){ 
			byte&= ~(1<<(7-i)); // write 0
		}
		else byte|= (1<<(7-i)); // if the pin is high, write 1
		while (HAL_GPIO_ReadPin (port, pin) && // wait for the pin to go low 
				__HAL_TIM_GET_COUNTER(&US_TIMER) < LONG_TIMEOUT);  
		if(__HAL_TIM_GET_COUNTER(&US_TIMER) > LONG_TIMEOUT) return DHT11_Timeout;
	}
	HAL_TIM_Base_Stop(&US_TIMER);
	return byte;
}

static void _set_as_input(GPIO_TypeDef* port, uint16_t pin){
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin = pin;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    HAL_GPIO_Init(port, &GPIO_InitStruct);
}
static void _set_as_output(GPIO_TypeDef* port, uint16_t pin){
    GPIO_InitTypeDef GPIO_InitStruct = {0};
	GPIO_InitStruct.Pin = pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(port, &GPIO_InitStruct);
}