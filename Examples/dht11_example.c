#include <main.h>
#include <stdint.h>
#include <stdio.h>
#include "helper.h"
#include "dht11.h"


// InComplete

void dht11_example{
    // Let Port and Pin where DHT11 data pin is connected be
    // Port = DHT11_GPIO_Port
    // Pin = DHT11_Pin
    // Define variables temp and humidity
    uint8_t temp, hum;
    // Response send by DHT11 = int res
    int res;
    res = DHT11_read(DHT11_GPIO_Port,DHT11_Pin,&temp,&hum);
    // Check for error in reading
    // Also declare variable for string containing ......
    uint8_t buffer[50] = {0};
    if(res != DHT11_OK){
        switch (res)
        {
        case DHT11:
            break;
        
        default:
            break;
        }
        HAL_UART_Transmit("")
    }
    else{
        sprintf(buffer, "Temp:%d,Humidity:%d",temp,hum);
    }
}