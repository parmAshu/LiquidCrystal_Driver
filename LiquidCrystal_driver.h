/**
 * @author - Ashutosh Singh Parmar
 * @file - LiquidCrystal_driver.h
 * @brief - This file contains declarations for driver APIs.
 * 
 * ************************************************************************************
 * ************************************************************************************
*/

#include "LiquidCrystal_pal.h"

#define LCD_CMD_CLEAR_DISPLAY 0X01

#define LCD_CMD_RETURN_HOME 0X02

#define LCD_CMD_ENTRY_MODE_SET(ID,S) ( 0X04 | (ID<<1) | (S) )

#define LCD_CMD_DISPLAY_CONTROL(D, C, B) ( 0X08 | (D<<2) | (C<<1) | (B) )

#define LCD_CMD_CUR_DISP_SHIFT(SC, RL) ( 0X00 | (SC<<3) | (RL<<2) )

#define LCD_CMD_FUNCTION_SET(DL, N, F) ( 0X20 | (DL<<4) | (N<<3) | (F<<2) )

#define LCD_CMD_SET_CGRAM_ADD( add ) ( 0X40 | (add & 0X3F) )

#define LCD_CMD_SET_DDRAM_ADD( add ) ( 0X80 | (add & 0X7F) )

#define LCD_ERROR_CHECK(err) if(!err)return 0

#define RS 0
#define EN 2
#define RW 1

typedef enum LCD_CONTROLLER_REG { IR = 0, DR = 1 }LCD_CONTROLLER_REG;

char InitializeLCD(uint8_t);

char LCDClearDisplay();

char LCDDisplayHome();

char LCDDisplayOn();

char LCDDisplayOff();

char LCDCursorEnable();

char LCDCursorDisable();

char LCDBacklightEnable();

char LCDBacklightDisable();

char LCDCursorPosition(uint8_t, uint8_t);

char LCDPrintChar(uint8_t);

char LCDPrintStr(uint8_t * ch_code_str, uint8_t len);

char LCDPrintCustomChar(uint8_t num);

char LCDStoreCustomCharacter(uint8_t, uint8_t [8]);