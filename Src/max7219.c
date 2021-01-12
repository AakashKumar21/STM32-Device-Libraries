#include <main.h>
#include <stdint.h>
#include "max7219.h"


static void MAX7219_write_to_reg(MAX7219_HandleTypeDef *handle, uint8_t address, uint8_t data){
    HAL_GPIO_WritePin(handle->port, handle->cs, GPIO_PIN_RESET); // Chip select enable
    HAL_GPIO_WritePin(handle->port, handle->clk, GPIO_PIN_RESET);
    uint8_t array[2] = {address,data};
    // Send address and data
    // Send address then data
    for(int array_index=0; array_index<2;array_index++){
        for(int i=0; i<8;i++){
            if(array[array_index] & 0x80){ // msb
                HAL_GPIO_WritePin(handle->port, handle->din, GPIO_PIN_SET);   
            }
            else{
                HAL_GPIO_WritePin(handle->port, handle->din, GPIO_PIN_RESET);   
            }
            array[array_index] = array[array_index] << 1;
            HAL_GPIO_WritePin(handle->port, handle->clk, GPIO_PIN_SET);
            DELAY;
            HAL_GPIO_WritePin(handle->port, handle->clk, GPIO_PIN_RESET);
            DELAY;
        }
    }
    HAL_GPIO_WritePin(handle->port, handle->cs, GPIO_PIN_SET);
}

void MAX7219_DisplayTest(MAX7219_HandleTypeDef *handle,uint8_t test){
    uint8_t address = MAX7219_DIS_TEST;
    uint8_t data;
    if(test == 1){
        data = 1;
    }
    else {
        data = 0;
    }
    MAX7219_write_to_reg(handle,address,data);
    HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
}

void MAX7219_SetIntensity(MAX7219_HandleTypeDef *handle,uint8_t intensity){
    uint16_t address = MAX7219_INTENSITY;
    MAX7219_write_to_reg(handle,address,intensity);
}