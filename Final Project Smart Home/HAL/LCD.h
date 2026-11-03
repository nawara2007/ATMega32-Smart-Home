#define F_CPU 16000000UL
#include <util/delay.h>
#include "../MCAL/DIO.h"
#include "../LIB/STD_TYPES.h"
#include "../LIB/BIT_MATH.h"


#ifndef LCD_H_
#define LCD_H_
// we will define in this file the pins of LCD and commands registers
#define LCD_CONTROL_PORT  PORTD_ID
#define LCD_DATA_PORT     PORTC_ID

#define LCD_RS_PIN  PIN0
//#define LCD_RW_PIN  PIN1
#define LCD_E_PIN   PIN1

#define LCD_D0_PIN   PIN0
#define LCD_D1_PIN   PIN1
#define LCD_D2_PIN   PIN2
#define LCD_D3_PIN   PIN3
#define LCD_D4_PIN   PIN4
#define LCD_D5_PIN   PIN5
#define LCD_D6_PIN   PIN6
#define LCD_D7_PIN   PIN7


#define HIGH 1
#define LOW 0



/******************************************COMMANDS************************************************************/

#define LCD_CLR                   0x01   //replace all characters with ASCII 'space'
#define LCD_HOME                  0x02  // return cursor to first position on first line 
#define LCD_SHIFT_RIGHT           0X1C
#define LCD_SHIFT_LEFT            0X18 
#define LCD_FUN_SET_TWOLINE_5x8   0x38  //8 bits mode initialization (8-bit data, 2-line display, 5 x 8 font )
#define LCD_FUN_SET_TWOLINE_5x11  0x3C  //8 bits mode initialization (8-bit data, 2-line display, 5 x 11 font )
#define LCD_DIS_ON_SETUP          0x0F
#define lcd_DisplayOn_CursorOff   0x0c  // display on, cursor off, don't blink character
#define lcd_DisplayOn_CursorOn    0x0e  // display on, cursor on, don't blink character
#define lcd_DisplayOff_CursorOff  0x08  // turn display off
#define LCD_EntryMode             0x06  // shift cursor from left to right on read/write




/*****************************************FUNCTIONS*************************************************************/
void LCD_Command(u8 comm);

void LCD_Data(u8 data);
/*
* This Function clear LCD [send clear command]
* Parameters : nothing
* return : nothing
*/

void LCD_ClearScreen(void);

/*
*  This Function Apply initialization sequence for LCD module
* Parameters : nothing
* return : nothing

steps:
1- must wait more than 30 ms before any action (VDD rises to 4.5 v)
2- All Pins as OutPut pins
3- Return cursor to the first position on the first line
4- FUNCTION SET Command : 2 lines , 5*8 font size  
5- DISPLAY & Cursor (ON / OFF) Control
6- DISPLAY CLEAR
7- ENTRY MODE  SET
*/
void LCD_Init(void);

//void LCD_WaitBusy(void);

void LCD_SendString(const u8 *Str); // this func may write in DDRAM unseen part of it

void LCD_MoveCursor(u8 row,u8 col); // you are not allowed to use the un visible part of the DDRAM

void LCD_SendString_MV_CR (u8 *Str,u8 row,u8 col); // more professional func write in visible region only

void LCD_Scroll_RIGHT(u8 no);

void LCD_Scroll_LEFT(u8 no);

void LCD_SET_CGRAM (u8 address);

void LCD_STORE_CUST_CHAR (u8* arr_char ,u8 slot); // slot ranges only from 0 to 7

void LCD_PRINT_CUST_CHAR (u8 slot,u8 row, u8 column);

void LCD_SHOW_CUST_CHAR (u8 slot);


//void create_custome(u8 *Str,u8 custom_number);
//void show_custome(u8 custom_number);


#endif /* LCD_H_ */