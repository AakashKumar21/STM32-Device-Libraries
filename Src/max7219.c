#include <main.h>
#include <stdint.h>
#include "max7219.h"

void MAX7219_send_byte(MAX7219_HandleTypeDef *handle, uint8_t byte){
    HAL_GPIO_WritePin(handle->port, handle->clk, GPIO_PIN_RESET);
    for(int i=0; i<8;i++){
        if(byte & 0x80){ // msb
            HAL_GPIO_WritePin(handle->port, handle->din, GPIO_PIN_SET);   
        }
        else{
            HAL_GPIO_WritePin(handle->port, handle->din, GPIO_PIN_RESET);   
        }
        byte = byte << 1;
        HAL_GPIO_WritePin(handle->port, handle->clk, GPIO_PIN_SET);
        DELAY;
        HAL_GPIO_WritePin(handle->port, handle->clk, GPIO_PIN_RESET);
        DELAY;
    } 
}

void MAX7219_DisplayTest(MAX7219_HandleTypeDef *handle,uint8_t test){
    HAL_GPIO_WritePin(handle->port, handle->cs, GPIO_PIN_RESET);
    uint8_t address = MAX7219_DIS_TEST;
    // Register Address
    MAX7219_send_byte(handle,address);
    // Send Register data
    if(test == 1){
        MAX7219_send_byte(handle, 1);
    }
    else {
        MAX7219_send_byte(handle, 0);
    }
    HAL_GPIO_WritePin(handle->port, handle->cs, GPIO_PIN_SET);
}