#include "pcf8574.h"
#include <main.h>
#include <stdint.h>

PCF8574_test_write(I2C_HandleTypeDef *i2c_handle,PCF8574_HandleTypeDef *pcf_handle)
{
    uint8_t pin_val = 1;
    for (int i = 0; i < 8; i++)
    {
        HAL_I2C_Master_Transmit(i2c_handle, pcf_handle->address, &pin_val, 1, 1);
        pin_val = pin_val << 1;
        HAL_Delay(150);
    }
}

HAL_StatusTypeDef
PCF8574_WritePin(I2C_HandleTypeDef *i2c_handle, PCF8574_HandleTypeDef *pcf_handle, uint8_t pin, uint8_t val)
{
    if (val == GPIO_PIN_SET)
    {
        pcf_handle->output_value |= pin;
    }
    else
    {
        pcf_handle->output_value &= ~pin;
    }

    return HAL_I2C_Master_Transmit(i2c_handle, pcf_handle->address, &(pcf_handle->output_value), 1, 1);
}