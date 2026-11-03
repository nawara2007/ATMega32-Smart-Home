/*
 * LCD.c
 *
 * Created: 8/17/2026 7:23:39 PM
 *  Author: mohamed nawara
 */ 
#include "LCD.h"

void LCD_Command(u8 comm)
{
	_delay_ms(2);
	
	DIO_voidSetPortDirection(LCD_DATA_PORT, PORT_OUTPUT);
	
	DIO_voidSetPinValue(LCD_CONTROL_PORT, LCD_RS_PIN, PIN_LOW);
	//DIO_voidSetPinValue(LCD_CONTROL_PORT, LCD_RW_PIN, PIN_LOW);
	
	DIO_voidSetPortValue(LCD_DATA_PORT, comm);
	
	DIO_voidSetPinValue(LCD_CONTROL_PORT, LCD_E_PIN, PIN_HIGH);
	_delay_us(1);
	DIO_voidSetPinValue(LCD_CONTROL_PORT, LCD_E_PIN, PIN_LOW);
}

/*void LCD_WaitBusy(void)
{
	DIO_voidSetPortDirection(LCD_DATA_PORT, PORT_INPUT);
	
	DIO_voidSetPinValue(LCD_CONTROL_PORT, LCD_RS_PIN, PIN_LOW); // put to access the DATA register
	DIO_voidSetPinValue(LCD_CONTROL_PORT, LCD_RW_PIN, PIN_HIGH); // put to read mode
	
	u8 is_busy = 1;
	while(is_busy)
	{
		DIO_voidSetPinValue(LCD_CONTROL_PORT, LCD_E_PIN, PIN_HIGH);
		_delay_us(1);
		
		is_busy = DIO_u8GetPinValue(LCD_DATA_PORT, LCD_D7_PIN); // the Busy flag is put on D7
		
		DIO_voidSetPinValue(LCD_CONTROL_PORT, LCD_E_PIN, PIN_LOW);
		_delay_us(1);
	}
	
}*/

void LCD_Data(u8 data)
{
	_delay_ms(2);
	
	DIO_voidSetPortDirection(LCD_DATA_PORT, PORT_OUTPUT);
	
	DIO_voidSetPinValue(LCD_CONTROL_PORT, LCD_RS_PIN, PIN_HIGH);
	//DIO_voidSetPinValue(LCD_CONTROL_PORT, LCD_RW_PIN, PIN_LOW);
	
	DIO_voidSetPortValue(LCD_DATA_PORT, data);
	
	DIO_voidSetPinValue(LCD_CONTROL_PORT, LCD_E_PIN, PIN_HIGH);
	_delay_us(1);
	DIO_voidSetPinValue(LCD_CONTROL_PORT, LCD_E_PIN, PIN_LOW);
}

void LCD_ClearScreen(void)
{
	LCD_Command(LCD_CLR);
}

void LCD_Init(void)
{
	_delay_ms(30);
	DIO_voidSetPinDirection(LCD_CONTROL_PORT, LCD_RS_PIN, PIN_OUTPUT);
	//DIO_voidSetPinDirection(LCD_CONTROL_PORT, LCD_RW_PIN, PIN_OUTPUT);
	DIO_voidSetPinDirection(LCD_CONTROL_PORT, LCD_E_PIN, PIN_OUTPUT);
	DIO_voidSetPortDirection(LCD_DATA_PORT, PORT_OUTPUT);
	
	//send first ever command manually as the wait bus isnot initialized yet
	DIO_voidSetPinValue(LCD_CONTROL_PORT, LCD_RS_PIN, PIN_LOW);
	//DIO_voidSetPinValue(LCD_CONTROL_PORT, LCD_RW_PIN, PIN_LOW);
	
	DIO_voidSetPortValue(LCD_DATA_PORT, LCD_FUN_SET_TWOLINE_5x8);
	
	DIO_voidSetPinValue(LCD_CONTROL_PORT, LCD_E_PIN, PIN_HIGH);
	_delay_us(1);
	DIO_voidSetPinValue(LCD_CONTROL_PORT, LCD_E_PIN, PIN_LOW);
	
	// continue the list of instructions
	_delay_us(40);
	LCD_Command(lcd_DisplayOn_CursorOff);
	_delay_us(40);
	LCD_ClearScreen();
	_delay_ms(1.54);
	LCD_Command(LCD_EntryMode);
}

void LCD_SendString(const u8 *Str)
{
	for(int i = 0;Str[i] != '\0' ; i++)
	{
		LCD_Data(Str[i]);
	}
}

void LCD_MoveCursor(u8 row,u8 col)
{
	if(row < 2 && col < 16)
	{
		LCD_Command(0x80 + row * 0x40 + col);
	}
}

void LCD_SendString_MV_CR (u8 *Str,u8 row,u8 col)
{
	LCD_MoveCursor(row, col);
	LCD_SendString(Str);
}

void LCD_Scroll_RIGHT(u8 no)
{
	for(int i = 0; i<no; i++)
	{
		LCD_Command(LCD_SHIFT_RIGHT);
		_delay_ms(100);
	}
}

void LCD_Scroll_LEFT(u8 no)
{
	for(int i = 0; i<no; i++)
	{
		LCD_Command(LCD_SHIFT_LEFT);
		_delay_ms(300);
	}
}

void LCD_SET_CGRAM (u8 address)
{
	LCD_Command(0X40 + address);
}

void LCD_STORE_CUST_CHAR (u8* arr_char ,u8 slot)
{
	if(slot < 8)
	{
		LCD_SET_CGRAM(slot * 8);
		
		for(int i = 0;i < 8; i++)
		{
			LCD_Data(arr_char[i]);
		}
		
		LCD_MoveCursor(0,0);
	}
}

void LCD_PRINT_CUST_CHAR(u8 slot, u8 row, u8 column)
{
	if(slot < 8)
	{
		LCD_MoveCursor(row,column);
		LCD_Data(slot);
	}
}

void LCD_SHOW_CUST_CHAR(u8 slot)
{
	if(slot < 8)
	{
		LCD_Data(slot);
	}
}
