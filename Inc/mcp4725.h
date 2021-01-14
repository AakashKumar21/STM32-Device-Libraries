/**
******************************************************************************
* @brief   MCP4725 DAC Driver
* @author  Aakash Kumar
******************************************************************************
*/ 


#ifndef __mcp4725
#define __mcp4725

#include <main.h>
#include <stdint.h>
 
/* MCP4725 Register Values -------------------------------------------------*/
// Power Down Modes
#define MCP4725_PWR_DOWN_0 0x00
#define MCP4725_PWR_DOWN_1 0x01
#define MCP4725_PWR_DOWN_2 0x02
#define MCP4725_PWR_DOWN_3 0x03
// Write to EEPROM or DAC Register
#define MCP4725_WRITE_EEPROM 0x06
#define MCP4725_WRITE_DAC 0x06
// Write Command Types
#define MCP4725_CMD_DAC 0x00 // Fast
#define MCP4725_CMD_EEPROM 0x02
#define MCP4725_CMD_BOTH 0x03
// General Call 
#define MCP4725_GEN_RST 0x06
#define MCP4725_GEN_WAKE 0x09

/* Write DAC Register using Fast Mode Write Command (From Datasheet)--------*/
// msb - - - - lsb
// Address | R/W | 3bit mode | 2bit power down mode| Lower adc 4bit ||| higer adc 4 bit
// ||| -> start i2c tx again

/* Type Defs ---------------------------------------------------------*/
typedef struct 
{
    uint8_t address;  // address with write mode, << 1
    uint8_t cmd_pwr;  // Command type and power mode is combined into one and << 4
}MCP4725_HandleTypeDef;

// TODO, maybe add init function

/* Function Prototypes ---------------------------------------------------------*/
HAL_StatusTypeDef 
MCP4725_Reset(I2C_HandleTypeDef *i2c, MCP4725_HandleTypeDef* mcp);
/** 
* @brief Reset device using General Reset Call
* @param i2c pointer to i2c handle
* @param mcp pointer mcp4275 handle
* @return HAL_StatusTypeDef for i2c transaction
*/

HAL_StatusTypeDef 
MCP4725_WakeUp(I2C_HandleTypeDef *i2c, MCP4725_HandleTypeDef* mcp);
/** 
* @brief Reset device using General WakeUp Call
* @param i2c pointer to i2c handle
* @param mcp pointer mcp4275 handle
* @return HAL_StatusTypeDef for i2c transaction
*/

HAL_StatusTypeDef 
MCP4725_SetOutput(I2C_HandleTypeDef *i2c, MCP4725_HandleTypeDef* mcp uint16_t out);
/** 
* @brief Set output voltage
* @param i2c pointer to i2c handle
* @param mcp pointer mcp4275 handle
* @param out output value (12 bit)
* @return HAL_StatusTypeDef for i2c transaction
*/


#endif