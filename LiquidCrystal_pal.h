/**
 * @author - Ashutosh Singh Parmar
 * @file - LiquidCrystal_pal.h
 * @brief - This file contains declarations for platform abstraction layer APIs that will be used by the driver APIs.
 * 
 * ************************************************************************************
 * ************************************************************************************
*/

#include "LiquidCrystal_common.h"

#include <Arduino.h>
#include <Wire.h>

/**
 * @brief - Enumeration defining different GPIO modes
*/
typedef enum GPIO_MODE_PAL { input = 0, input_pullup = 1, input_pulldown = 2, output = 3} GPIO_MODE_PAL;

/**
 * @brief - Enumeration defining different GPIO states
*/
typedef enum GPIO_STATE_PAL { high = 1, low = 0} GPIO_STATE_PAL;

char InitializeGPIO(uint8_t, GPIO_MODE_PAL);

char SetStateGPIO(uint8_t, GPIO_STATE_PAL);

char InitializeI2C();

char WriteI2C(uint8_t, uint8_t);

char ReadI2C(uint8_t, uint8_t *);

void DelayMS(unsigned int);

void DelayUS(unsigned int);