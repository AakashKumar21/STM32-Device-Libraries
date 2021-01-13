/**
******************************************************************************
* @brief   MAX7219 8x8 LED Driver
* @author  Aakash Kumar
* @ref https://datasheets.maximintegrated.com/en/ds/MAX7219-MAX7221.pdf
******************************************************************************
*/ 


#ifndef __max7219
#define __max7219

#include <main.h>
#include <stdint.h> 

// #define USE_HAL_DELAY
#if defined(USE_HAL_DELAY)
#define DELAY HAL_Delay(1)
#endif
#if !defined(USE_HAL_DELAY)
#define DELAY delay_us(1)
#include "helper.h"
#endif

/* MAX7219 Register Addresses -----------------------------------------------------------*/
#define MAX7219_NO_OP 0x0
#define MAX7219_DIGIT_0 0x1
#define MAX7219_DIGIT_1 0x2
#define MAX7219_DIGIT_2 0x3
#define MAX7219_DIGIT_3 0x4
#define MAX7219_DIGIT_4 0x5
#define MAX7219_DIGIT_5 0x6
#define MAX7219_DIGIT_6 0x7
#define MAX7219_DIGIT_7 0x8
#define MAX7219_DECODE_MODE 0x9
#define MAX7219_INTENSITY 0xA
#define MAX7219_SCAN_LIM 0xB
#define MAX7219_SHUTDOWN 0xC
#define MAX7219_DIS_TEST 0xF


/* MAX7219 Register Data Values ------------------------------------------------*/
#define SHUTDOWN_TRUE 0x0
#define SHUTDOWN_FALSE 0x1
#define DECODE_ON 0x1
#define DECODE_OFF 0x0


// Using struct is not efficient but it will make functions look good 
// by reducing number of params.
typedef struct
{
  GPIO_TypeDef* port;
  uint16_t din;
  uint16_t cs;
  uint16_t clk;
}MAX7219_HandleTypeDef;

void MAX7219_SetIntensity(MAX7219_HandleTypeDef *handle,uint8_t intensity);
/** 
* @brief Sets the intensity of led brightness
* @param handle pointer to max7219 handle
* @param intensity 4 bit intensity value
* @return void
*/

void MAX7219_Shutdown(MAX7219_HandleTypeDef *handle,uint8_t shut);
/** 
* @brief Sets the intensity of led brightness
* @param handle pointer to max7219 handle
* @param shut 1 to shutdown, 0 to turn on
* @return void
*/

void MAX7219_DisplayTest(MAX7219_HandleTypeDef *handle,uint8_t test);
/** 
* @brief Turn on or off display test function
* @param handle pointer to max7219 handle
* @param test 1 for diplay test, 0 for normal operation
* @return void
*/


void MAX7219_NoDecode(MAX7219_HandleTypeDef *handle, uint8_t decode);
/** 
* @brief Turn on/off decode mode
* @param handle pointer to max7219 handle
* @param decode 1 for no decode mode, 0 for decode mode
* @return void
*/

void MAX7219_WritePattern(MAX7219_HandleTypeDef *handle, uint8_t *pattern);
/** 
* @brief Display pattern
* @param handle pointer to max7219 handle
* @param pattern array of 8 uints, each representing row from top to bottom
* @return void
*/

void MAX7219_ScanLimit(MAX7219_HandleTypeDef *handle, uint8_t limit);
/** 
* @brief Display pattern
* @param handle pointer to max7219 handle
* @param limit scan limit
* @return void
*/

static void MAX7219_write_to_reg(MAX7219_HandleTypeDef *handle, uint8_t address, uint8_t data);
/** 
* @brief Write data to register
* @param handle pointer to max7219 handle
* @param array array of uint8_t of size 2, {address,data}
* @return void
*/

#endif