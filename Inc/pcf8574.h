/**
  ******************************************************************************
  * @file    mcp23017.h
  * @brief   MCP23017 Driver.
  * @author  Aakash Kumar
  ******************************************************************************
  */

#ifndef __PCF8574
#define __PCF8574

#include <main.h>
#include <stdint.h>

typedef struct 
{
  uint8_t address;
  uint8_t output_value;
}PCF8574_HandleTypeDef;

void PCF8574_test_write(I2C_HandleTypeDef *i2c_handle,PCF8574_HandleTypeDef *pcf_handle);
/**
* @brief To test working of i2c and pcf8574 by blinking each pin for 150 ms once. 
* @param i2c_handle pointer to i2c handle
* @param pcf_handle pointer to pcf handle
* @return void
*/


HAL_StatusTypeDef 
PCF8574_WritePin(I2C_HandleTypeDef *i2c_handle, PCF8574_HandleTypeDef *pcf_handle, uint8_t pin, uint8_t val);
/**
* @brief Write to pin without affecting status of other pins. 
* @param i2c_handle pointer to i2c handle
* @param pcf_handle pointer to pcf handle
* @param pin pin number
* @param val pin value or output value
* @return HAL_StatusTypeDef of i2c transmit operation
*/

HAL_StatusTypeDef 
PCF8574_ReadPin(I2C_HandleTypeDef *i2c_handle, PCF8574_HandleTypeDef *pcf_handle, uint8_t pin, uint8_t* val);
/**
* @brief Read from pin.
* @param i2c_handle pointer to i2c handle
* @param pcf_handle pointer to pcf handle
* @param pin pin number
* @param val pointer to uint8 where value of pin will be stored
* @return HAL_StatusTypeDef of i2c read operation
*/


#endif