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

HAL_StatusTypeDef 
PCF8574_WritePin(I2C_HandleTypeDef *i2c_handle, PCF8574_HandleTypeDef *pcf_handle, uint8_t pin, uint8_t val);

HAL_StatusTypeDef 
PCF8574_TogglePin(I2C_HandleTypeDef *i2c_handle, PCF8574_HandleTypeDef *pcf_handle, uint8_t pin);
#endif