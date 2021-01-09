/**
  * @file           : dht11.h
  * @brief          : Header for dht11.c file.
**/
#ifndef __DHT11_H
#define __DHT11_H

#include "main.h"
#include "main.h"
#include "helper.h"
#include <stdint.h>

typedef enum{
    DHT11_OK,
    DHT11_Timeout,
    DHT11_Checksum_Error,
    DHT11_No_Response
}DHT11_Status;

#define TIMEOUT 150 // 150 us
#define LONG_TIMEOUT 5000 // 5 ms, 
// Static to make this func inaccessible(private) from other source files
static void _set_as_input(GPIO_TypeDef* port, uint16_t pin);
static void _set_as_output(GPIO_TypeDef* port, uint16_t pin);
static uint8_t _read_byte(GPIO_TypeDef* port, uint16_t pin);

DHT11_Status DHT11_read(GPIO_TypeDef* port, uint16_t pin, 
                        uint8_t* temp, uint8_t *hum);

#endif