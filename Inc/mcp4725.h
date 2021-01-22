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
#define MCP4725_PWR_DOWN_1 0x02
#define MCP4725_PWR_DOWN_2 0x04
#define MCP4725_PWR_DOWN_3 0x06
// Write Command Types
#define MCP4725_CMD_FAST 0x00 // Fast, TODO
#define MCP4725_CMD_DAC  0x40
#define MCP4725_CMD_BOTH 0x60
// General Call , // TODO
#define MCP4725_GEN_RST 0x06
#define MCP4725_GEN_WAKE 0x09

/* Protocol (From Datasheet)--------*/
// msb - - - - lsb
//| Ad.RW | C2.C1.C0.X.X.PD1.PD0.X | msb byte | lsb 4 bits.X.X.X.X |

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
MCP4725_SetOutput(I2C_HandleTypeDef *i2c, MCP4725_HandleTypeDef* mcp, uint16_t out);
/** 
* @brief Set output voltage
* @param i2c pointer to i2c handle
* @param mcp pointer mcp4275 handle
* @param out output value (12 bit)
* @return HAL_StatusTypeDef for i2c transaction
*/

HAL_StatusTypeDef 
MCP4725_TestOutput(I2C_HandleTypeDef *i2c, MCP4725_HandleTypeDef* mcp);
/** 
* @brief Test i2c and mcp4725 by outputting sinwave
* @param i2c pointer to i2c handle
* @param mcp pointer mcp4275 handle
* @return HAL_StatusTypeDef
*/


#endif