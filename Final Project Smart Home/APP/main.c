/*
 * main.c
 *
 * Created: 8/27/2026 2:17:38 PM
 *  Author: mohamed nawara
 */ 
#define F_CPU 16000000UL

#include "../HAL/LED.h"
#include "../HAL/LCD.h"
#include "../HAL/LDR.h"
#include "../HAL/Motor.h"
#include "../HAL/Flame.h"
#include "../HAL/Buzzer.h"
#include "../HAL/LM35.h"

#include <util/delay.h>
#include <stdio.h>
#include <xc.h>

void AlertMode()
{
	Motor_OFF();
	led_off(PORTB_ID, PIN5);
	led_off(PORTB_ID, PIN6);
	led_off(PORTB_ID, PIN7);
	LCD_ClearScreen();
	LCD_SendString(" Critical alert!");
	while(FLAME_PinState())
	{
		BUZZER_ON();
		_delay_ms(100);
		BUZZER_OFF();
		_delay_ms(100);
	}
}

int main(void)
{
	LCD_Init();
	
	led_init(PORTB_ID, PIN5); //red
	led_init(PORTB_ID, PIN6); //green
	led_init(PORTB_ID, PIN7); //blue
	
	LDR_init(ADC_CHANNEL0);
	LM35_init(ADC_CHANNEL1);
	
	BUZZER_init(PORTD_ID, PIN3);
	Flame_init(EXT_INT0_ID, AlertMode);
	
	Motor_init(PORTB_ID, PIN0, PIN1); //enable pin connected to OC0 (PB3)
	
		
	char lcd_buffer1[16];
	char lcd_buffer2[16];
	
	u8 LDR_Precentage = 0;
	u16 TempratureCelsius = 0;
	
    while(1)
    {
		//get the readings
		LDR_Precentage = LDR_u8GetPrecent();
		TempratureCelsius = LM35_u16getCelsius();
		
		//display the data
		sprintf(lcd_buffer1, "Temp=%d LDR=%d% ", TempratureCelsius, LDR_Precentage);
		LCD_SendString_MV_CR(lcd_buffer1, 1, 0);
		
		//controlling the fan
		if (TempratureCelsius >= 40)
		{
			Motor_ON(motor_clockwise_direction, 100);
			sprintf(lcd_buffer2, " Fan is ON 100%  ");
		}
		else if (TempratureCelsius < 40 && TempratureCelsius >= 35)
		{
			Motor_ON(motor_clockwise_direction, 75);
			sprintf(lcd_buffer2, " Fan is ON 75%  ");
		}
		else if (TempratureCelsius < 35 && TempratureCelsius >= 30)
		{
			Motor_ON(motor_clockwise_direction, 50);
			sprintf(lcd_buffer2, " Fan is ON 50%  ");
		}
		else if (TempratureCelsius < 30 && TempratureCelsius >= 25)
		{
			Motor_ON(motor_clockwise_direction, 25);
			sprintf(lcd_buffer2, " Fan is ON 25%  ");
		}
		else
		{
			Motor_OFF();
			sprintf(lcd_buffer2, "   Fan is OFF  ");
		}
		
		//display fan status
		LCD_SendString_MV_CR(lcd_buffer2, 0, 0);
		
		//controlling the leds
		if(LDR_Precentage > 70)
		{
			led_off(PORTB_ID, PIN5);
			led_off(PORTB_ID, PIN6);
			led_off(PORTB_ID, PIN7);
		} else if (LDR_Precentage <= 70 && LDR_Precentage > 50)
		{
			led_on(PORTB_ID, PIN5);
			led_off(PORTB_ID, PIN6);
			led_off(PORTB_ID, PIN7);
		} else if (LDR_Precentage <= 50 && LDR_Precentage > 16)
		{
			led_on(PORTB_ID, PIN5);
			led_on(PORTB_ID, PIN6);
			led_off(PORTB_ID, PIN7);
		} else 
		{
			led_on(PORTB_ID, PIN5);
			led_on(PORTB_ID, PIN6);
			led_on(PORTB_ID, PIN7);
		}
		
	}
			
}