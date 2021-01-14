#include "mcp4725.h"

HAL_StatusTypeDef 
MCP4725_Reset(I2C_HandleTypeDef *i2c, MCP4725_HandleTypeDef* mcp){
    uint8_t data = MCP4725_GEN_RST;
    return HAL_I2C_Master_Transmit(i2c,0x00,&data,1,1);
}

HAL_StatusTypeDef 
MCP4725_WakeUp(I2C_HandleTypeDef *i2c, MCP4725_HandleTypeDef* mcp){
    uint8_t data = MCP4725_GEN_WAKE;
    int stat;
    stat = HAL_I2C_Master_Transmit(i2c,0x00,&data,1,1);
    if(stat == HAL_OK){
        mcp->pwr_mode = 0x00;
    }
    return stat;
}

HAL_StatusTypeDef 
MCP4725_SetOutput(I2C_HandleTypeDef *i2c, MCP4725_HandleTypeDef* mcp uint16_t out){
    // HAL_I2C_Master_Transmit(i2c,mcp->address,mcp.)
}