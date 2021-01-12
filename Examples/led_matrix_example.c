#include <main.h>
#include <stdint.h>
#include <stdio.h>
#include "max7219.h"

void led_mastrix_example(){
    // Variable names
    // Port -> DIN_GPIO_Port
    // DIN Pin -> DIN_Pin
    // CS Pin -> CS_Pin
    // CLK Pin -> CS_Pin
    // Initilise MAX7219 Handle Type Structure
    MAX7219_HandleTypeDef matrix;
    matrix.port = DIN_GPIO_Port;
    matrix.din = DIN_Pin;
    matrix.cs = CS_Pin;
    matrix.clk = CLK_Pin;

    // Initilise MAX7219 Registers
    // Datasheet of MAX7219 states
    // Initial Power-Up
    // On initial power-up, all control registers are reset, the
    // display is blanked, and the MAX7219/MAX7221 enter
    // shutdown mode. Program the display driver prior to
    // display use. Otherwise, it will initially be set to scan one
    // digit, it will not decode data in the data registers, and
    // the intensity register will be set to its minimum value.

    // Disable shutdown mode
    MAX7219_Shutdown(&matrix,SHUTDOWN_FALSE); // where SHUTDOWN_FALSE = 1
    // Set intensity, intensity value must be of 4 bit (representable in 4 bit).
    MAX7219_SetIntensity(&matrix,16); // Highest intensity
    // Disable decode mode
    MAX7219_NoDecode(&matrix,0);
    // Set led scan limit to 8
    MAX7219_ScanLimit(&matrix,0x7);
    // Let's Write 'A'
    uint8_t pattern[8] = {0x18,0x24,0x42,0x42,0x7E,0x42,0x42,0x42};
    MAX7219_WritePattern(&matrix,pattern);
    // Also test the display to test working of all LED's
    MAX7219_DisplayTest(&matrix,1);
    // This will force turn on all LED's at full brightness
    // Turn this off to restore previous state
    // But wait for some time to see effect of this function
    HAL_Delay(500);
    // Now turn it off
    MAX7219_DisplayTest(&matrix,0);
}
