/**
 * @author - Ashutosh Singh Parmar
 * @file - LiquidCrystal_driver.c
 * @brief - This file contains definitions for driver APIs.
 * 
 * ************************************************************************************
 * ************************************************************************************
*/

#include "LiquidCrystal_driver.h"





/*
    +-------------------------------------+
    | DRIVER APIs FOR 16X2 I2C LCD MODULE |
    +-------------------------------------+
__________________________________________________________________________________________________________________________________
*/
#ifdef LCD_INTERFACE_I2C

/*
                +--------------------------------+
I2C CHIP ->     | P7  P6  P5  P4  P3  P2  P1  P0 | 
                +--------------------------------+
                  |   |   |   |   |   |   |   |
                  |   |   |   |   |   |   |   |
                  |   |   |   |   |   |   |   |
                +--------------------------------+
LCD MODULE ->   | K  RS  RW   E   D7  D6  D5  D4 |
                +--------------------------------+
*/

static uint8_t DEVICE_ADDRESS = 0X00;

static uint8_t LCD_BACKLIGHT = 0X08;

static uint8_t DISPLAY_EN = 1;

static uint8_t CURSOR = 0;

static uint8_t BLINK = 0;

static uint8_t CURSOR_POSITION_X = 0;

static uint8_t CURSOR_POSITION_Y = 0;


//-----------------------------------------------------------------------------------------------------------------------------------
// THESE ARE HELPER APIs THAT ARE INTERNALLY USED BY DRIVER APIs

/**
 * @brief - This API is used to write 4 bits to LCD module.
 * 
 * @param -
 * 1. LCD_CONTROLLER_REG reg: Register to write to - IR or DR
 * 2. uint8_t data : Data to send to; lower 4 bits are relevant
 * 
 * @return - char
 * 1 : success
 * 0 : failed
*/
static char LCDWrite4Bits(LCD_CONTROLLER_REG reg, uint8_t data)
{
    uint8_t temp = 0;

    temp |= (( data << 4 ) & 0XF0 );
    temp |= LCD_BACKLIGHT;
    temp |= (reg << RS);
    
    LCD_ERROR_CHECK(WriteI2C(DEVICE_ADDRESS, temp));

    temp |= (1<<EN);
    LCD_ERROR_CHECK(WriteI2C(DEVICE_ADDRESS, temp));

    DelayUS(1);

    temp &= ~(1<<EN);
    LCD_ERROR_CHECK(WriteI2C(DEVICE_ADDRESS, temp));

    DelayUS(50);
    
    return 1;
}

/**
 * @brief - This API is used to write 8 bits to LCD module.
 * 
 * @param -
 * 1. LCD_CONTROLLER_REG reg: Register to write to - IR or DR
 * 2. uint8_t data : Data to send to LCD module
 * 
 * @return - char
 * 1 : success
 * 0 : failed
*/
static char LCDWrite8Bits(LCD_CONTROLLER_REG reg, uint8_t data)
{
    LCD_ERROR_CHECK( LCDWrite4Bits(reg, (data >> 4)) );

    LCD_ERROR_CHECK( LCDWrite4Bits(reg, data) );

    return 1;
}

/**
 * @brief - This API is used to write 8 bits commands to LCD module.
 * 
 * @param -
 * 1. uint8_t cmd : Command to send to LCD module
 * 
 * @return - char
 * 1 : success
 * 0 : failed
*/
static char LCDSendCommand(uint8_t cmd)
{
    return LCDWrite8Bits(IR, cmd);
}

/**
 * @brief - This API is used to write 8 bits data to Data Register of LCD module.
 * 
 * @param -
 * 1. uint8_t data : data to send to LCD module
 * 
 * @return - char
 * 1 : success
 * 0 : failed
*/
static char LCDWriteData(uint8_t data)
{
    return LCDWrite8Bits(DR, data);
}

//-----------------------------------------------------------------------------------------------------------------------------------





//-----------------------------------------------------------------------------------------------------------------------------------
// EXTERNALLY AVAILABLE LCD DRIVER APIs

/**
 * @brief - This API is used to initialize LCD module.
 * 
 * @param -
 * 1. uint8_t address : I2C slave address of LCD module
 * 
 * @return - char
 * 1 : success
 * 0 : failed
*/
char InitializeLCD(uint8_t address)
{
    //saving the slave device address
    DEVICE_ADDRESS = address;

    #ifdef LCD_INITIALIZE_I2C
    //initialize the I2C port
    LCD_ERROR_CHECK(InitializeI2C());
    #endif

    DelayMS(20);

    // write nibble 0x3
    LCD_ERROR_CHECK(LCDWrite4Bits(IR, 0X03));

    // Wait for more than 4.1 ms
    DelayMS(5);

    // Write nibble 0x3
    LCD_ERROR_CHECK(LCDWrite4Bits(IR, 0X03));

    // Wait for more than 100us
    DelayUS(120);

    // Write nibble 0x3
    LCD_ERROR_CHECK(LCDWrite4Bits(IR, 0X03));

    // Write nibble 0x2
    LCD_ERROR_CHECK(LCDWrite4Bits(IR, 0X02));

    // Function set command - setting number of lines to 2
    LCD_ERROR_CHECK(LCDSendCommand( LCD_CMD_FUNCTION_SET(0, 1, 0) ));

    // Display control command - turning on the display, cursor off, blinking off
    LCD_ERROR_CHECK(LCDSendCommand( LCD_CMD_DISPLAY_CONTROL(DISPLAY_EN, CURSOR, BLINK) ));

    // Clear the display
    LCD_ERROR_CHECK(LCDClearDisplay());

    // Entry mode command - increment mode and shift off
    LCD_ERROR_CHECK(LCDSendCommand( LCD_CMD_ENTRY_MODE_SET(1, 0) ));
    
    // Returning diplay to default home
    LCD_ERROR_CHECK(LCDDisplayHome());

    return 1;
}

/**
 * @brief - This API is used to clear the LCD display.
 * 
 * @param -
 * NONE
 * 
 * @return - char
 * 1 : success
 * 0 : failed
*/
char LCDClearDisplay()
{
    LCD_ERROR_CHECK(LCDSendCommand( LCD_CMD_CLEAR_DISPLAY ));
    CURSOR_POSITION_X = 0;
    CURSOR_POSITION_Y = 0;
    DelayUS(2000);
    return 1;
}

/**
 * @brief - This API is used to return the LCD display to home position.
 * 
 * @param -
 * NONE
 * 
 * @return - char
 * 1 : success
 * 0 : failed
*/
char LCDDisplayHome()
{
    LCD_ERROR_CHECK(LCDSendCommand( LCD_CMD_RETURN_HOME ));
    CURSOR_POSITION_X = 0;
    CURSOR_POSITION_Y = 0;
    DelayUS(2000);
    return 1;
}

/**
 * @brief - This API is used to turn on the display.
 * 
 * @param -
 * NONE
 * 
 * @return - char
 * 1 : success
 * 0 : failed
*/
char LCDDisplayOn()
{
    DISPLAY_EN = LCDSendCommand(LCD_CMD_DISPLAY_CONTROL(1, CURSOR, BLINK));
    return DISPLAY_EN;
}

/**
 * @brief - This API is used to turn off the display.
 * 
 * @param -
 * NONE
 * 
 * @return - char
 * 1 : success
 * 0 : failed
*/
char LCDDisplayOff()
{
    DISPLAY_EN = !LCDSendCommand(LCD_CMD_DISPLAY_CONTROL(0, CURSOR, BLINK));
    return !DISPLAY_EN;
}

/**
 * @brief - This API is used to enable cursor.
 * 
 * @param -
 * NONE
 * 
 * @return - char
 * 1 : success
 * 0 : failed
*/
char LCDCursorEnable()
{
    CURSOR = LCDSendCommand(LCD_CMD_DISPLAY_CONTROL(DISPLAY_EN, 1, BLINK));
    return CURSOR;
}

/**
 * @brief - This API is used to disable cursor.
 * 
 * @param -
 * NONE
 * 
 * @return - char
 * 1 : success
 * 0 : failed
*/
char LCDCursorDisable()
{
    CURSOR = !LCDSendCommand(LCD_CMD_DISPLAY_CONTROL(DISPLAY_EN, 0, BLINK));
    return !CURSOR;
}

/**
 * @brief - This API is used to enable BackLight.
 * 
 * @param -
 * NONE
 * 
 * @return - char
 * 0X08 : success
 * 0 : failed
*/
char LCDBacklightEnable()
{
    LCD_BACKLIGHT = 0X08;
    LCD_BACKLIGHT &= LCDSendCommand( LCD_CMD_DISPLAY_CONTROL(DISPLAY_EN, CURSOR, BLINK) ) << 3;
    return LCD_BACKLIGHT;
}

/**
 * @brief - This API is used to disable BackLight.
 * 
 * @param -
 * NONE
 * 
 * @return - char
 * 1 : success
 * 0 : failed
*/
char LCDBacklightDisable()
{
    LCD_BACKLIGHT = 0X00;
    LCD_BACKLIGHT = (LCDSendCommand( LCD_CMD_DISPLAY_CONTROL(DISPLAY_EN, CURSOR, BLINK) ) << 3) ^ 0X08;
    return !LCD_BACKLIGHT;
}

/**
 * @brief - This API is used to set cursor position.
 * 
 * @param -
 * 1. uint8_t x : The cursor position in x direction (0-15)
 * 2. uint8_t y : The cursor position in y direction (0,1)
 * 
 * @return - char
 * 1 : success
 * 0 : failed
*/
char LCDCursorPosition(uint8_t x, uint8_t y)
{
    LCD_ERROR_CHECK( (x <= 15 && y <= 1) );
    
    uint8_t pos = 40 * y + x;

    if( LCDSendCommand( LCD_CMD_SET_DDRAM_ADD(pos) ) )
    {
        CURSOR_POSITION_X = x;
        CURSOR_POSITION_Y = y;
        return 1;
    }

    return 0;
}

/**
 * @brief - This API is used to display a character on the LCD.
 * 
 * @param -
 * 1. uint8_t ch_code : Code of the character to be displayed
 * 
 * @return - char
 * 0 : failed to print
 * 1 : success
 * 2 : failed to adjust position after printing, cursor is out of display area
*/
char LCDPrintChar(uint8_t ch_code)
{
    if( LCDWriteData(ch_code) )
    {
        CURSOR_POSITION_X ++;

        if( CURSOR_POSITION_X == 16 && CURSOR_POSITION_Y == 0 )
        {
            if( !LCDCursorPosition(0, 1) ) return 2;
        }
        else if( CURSOR_POSITION_X == 16 && CURSOR_POSITION_Y == 1)
        {
            if( !LCDCursorPosition(0, 0) ) return 2;
        }
        else
        {
            return 1;
        }
    }
    else
    {
        return 0;
    }
    return 1;
}

/**
 * @brief - This API is used to display a character string on the LCD.
 * 
 * @param -
 * 1. uint8_t * ch_code_str : pointer to the string containing codes of characters that are to be displayed
 * 2. uint8_t len : The number of characters to be printed on LCD
 * 
 * @return - char
 * 0 : failed to print
 * 1 : success
 * 2 : failed to adjust position after printing, cursor is out of display area
*/
char LCDPrintStr(uint8_t * ch_code_str, uint8_t len)
{
    uint8_t err;
    for(uint8_t i=0; i<len; i++)
    {
        err = LCDPrintChar( *(ch_code_str + i) );
        if( err == 0 || err == 2 ) return err;
    }
    return 1;
}

/**
 * @brief - This API is used to display one of the user defined characters on the LCD.
 * 
 * @param -
 * 1. uint8_t num : Index of user defined character that is to be displayed (0-7)
 * 
 * @return - char
 * 0 : failed
 * 1 : success
 * 2 : failed to adjust position after printing, cursor is out of display area
*/
char LCDPrintCustomChar(uint8_t num)
{
    LCD_ERROR_CHECK( (num < 8) );
    return LCDPrintChar( num );
}

/**
 * @brief - This API is used to store user defined characters in CGRAM.
 * 
 * @param -
 * 1. uint8_t num : The user defined character number (0-7)
 * 2. char pattern[8] : The array containing user defined pattern
 * 
 * @return - char
 * 1 : success
 * 0 : failed
*/
char LCDStoreCustomCharacter(uint8_t num, uint8_t pattern[8])
{
    LCD_ERROR_CHECK((num < 7));

    LCD_ERROR_CHECK( LCDSendCommand(LCD_CMD_SET_CGRAM_ADD(num << 3)) );

    for( uint8_t i=0; i<8; i++)
    {
        LCD_ERROR_CHECK( LCDWriteData(pattern[i]) );
    }

    LCD_ERROR_CHECK( LCDCursorPosition(CURSOR_POSITION_X, CURSOR_POSITION_Y) );

    return 1;
}
#endif
//--------------------------------------------------------------------------------------------------------------------------------





//________________________________________________________________________________________________________________________________