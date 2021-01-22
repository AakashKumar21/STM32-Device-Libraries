#include "mcp4725.h"

#define MCP4725_DAC_WRITE 0x40

HAL_StatusTypeDef
MCP4725_Reset(I2C_HandleTypeDef *i2c, MCP4725_HandleTypeDef *mcp)
{
    uint8_t data = MCP4725_GEN_RST;
    return HAL_I2C_Master_Transmit(i2c, 0x00, &data, 1, 1);
}

HAL_StatusTypeDef
MCP4725_WakeUp(I2C_HandleTypeDef *i2c, MCP4725_HandleTypeDef *mcp)
{
    uint8_t data = MCP4725_GEN_WAKE;
    int stat;
    stat = HAL_I2C_Master_Transmit(i2c, 0x00, &data, 1, 1);
    if (stat == HAL_OK)
    {
        mcp->cmd_pwr = 0x00; // TODO
    }
    return stat;
}

HAL_StatusTypeDef
MCP4725_SetOutput(I2C_HandleTypeDef *i2c, MCP4725_HandleTypeDef *mcp, uint16_t out)
{
    uint8_t data[3] = {mcp->cmd_pwr, (out & 0x0ff0) >> 4, out & 0x000f};
    HAL_I2C_Master_Transmit(i2c, mcp->address, data, sizeof(data), 1);
}

HAL_StatusTypeDef
MCP4725_TestOutput(I2C_HandleTypeDef *i2c, MCP4725_HandleTypeDef *mcp)
{
    uint8_t data[3] = {0x40, 0xff, 0xff};
    HAL_I2C_Master_Transmit(i2c, mcp->address, data, sizeof(data), 1);
    HAL_Delay(2000);
    data[1] = 0;
    HAL_I2C_Master_Transmit(i2c, mcp->address, data, sizeof(data), 1);
    HAL_Delay(2000);
}