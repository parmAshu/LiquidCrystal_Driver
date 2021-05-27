/**
 * @author - Ashutosh Singh Parmar
 * @file - LiquidCrystal_pal.c
 * @brief - This file contains definitions for platform abstraction layer APIs that will be used by the driver APIs.
 * 
 * ************************************************************************************
 * ************************************************************************************
*/
#include "LiquidCrystal_pal.h"

/**
 * @brief - This API is used to initialize GPIO pins.
 * 
 * @param 
 * 1. uint8_t pin : The pin number
 * 2. GPIO_MODE_PAL mode : GPIO mode
 * 
 * @return : char
 * 1 : GPIO initialized successfully
 * 0 : GPIO initialization failed
*/
char InitializeGPIO(uint8_t pin, GPIO_MODE_PAL mode)
{
    /*
    Put the platform specific code over here
    */
   return 1;
}

/**
 * @brief - This API is used to set the state of GPIO pins.
 * 
 * @param -
 * 1. uint8_t pin : The pin number
 * 2. GPIO_STATE_PAL state : GPIO state
 * 
 * @return - char
 * 1 : success
 * 0 : failed
*/
char SetStateGPIO(uint8_t pin, GPIO_STATE_PAL state)
{
    /*
    Put the platform specific code over here
    */
   return 1;
}

/**
 * @brief - This API is used to initialize I2C port.
 * 
 * @param -
 * NONE
 * 
 * @return - char
 * 1 : success
 * 0 : failed
*/
char InitializeI2C()
{
    /*
    Put the platform specific code over here
    */
   return 1;
}

/**
 * @brief - This API is used to write one byte to I2C slave device.
 * 
 * @param -
 * 1. uint8_t data : The 8 bits data to send to I2C slave device.
 * 
 * @return - char
 * 1 : success
 * 0 : failed
*/
char WriteI2C(uint8_t address, uint8_t data)
{
    /*
    Put the platform specific code over here
    */
   return 1;
}

/**
 * @brief - This API is used to read one byte from I2C slave device.
 * 
 * @param -
 * 1. uint8_t * data : Pointer to variable where data read from I2C slave device is stored into.
 * 
 * @return - char
 * 1 : success
 * 0 : failed
*/
char ReadI2C(uint8_t address, uint8_t * data)
{
    /*
    Put the platform specific code over here
    */
   return 1;
}

/**
 * @brief - This API is used to delay execution for given number of milli-seconds.
 * 
 * @param -
 * 1. unsigned int delay : The delay in milliseconds
 * 
 * @return -
 * NOTHING
*/
void DelayMS(unsigned int dl)
{
    /*
    Put the platform specific code over here
    */
}

/**
 * @brief - This API is used to delay execution for given number of micro-seconds.
 * 
 * @param -
 * 1. unsigned int delay : The delay in microseconds
 * 
 * @return -
 * NOTHING
*/
void DelayUS(unsigned int dl)
{
    /*
    Put the platform specific code over here
    */
}