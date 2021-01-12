#include <main.h>
#include <stdint.h>
#include <stdio.h>
#include "pcf8574.h"

void pcf8574_example(){
    // Initilise PCF8574 Handle 
    // I2C address of pcf must be left shifted of actual address
    PCF8574_HandleTypeDef pcf;
    pcf.address = 0x20 << 1;
    pcf.output_value = 0;
    // Write to pin and also check i2c transaction status
    int status;
    status = PCF8574_WritePin(&hi2c1,&pcf,GPIO_PIN_4,GPIO_PIN_SET);
    if(status == HAL_OK); // Yeah! no error
    else{
        switch (status)
        case HAL_TIMEOUT: break; // :( Timeout
        case HAL_ERROR: break;  //  :(( Error
    }
    // Note pcf8574 is 8 bit io expander so max is GPIO_PIN_8
    // Read from pin
    int pin_read;
    status = PCF8574_ReadPin(&hi2c1,&pcf,GPIO_PIN_7,&pin_read);
}