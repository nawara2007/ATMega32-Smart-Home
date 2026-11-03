/*
 * Motor.c
 *
 * Created: 9/18/2026 8:41:17 PM
 *  Author: mohamed nawara
 */ 
#include "Motor.h"

static u8 motor_port_id = 0;
static u8 motor_IN1 = 0;
static u8 motor_IN2 = 0;

void Motor_init(u8 copy_port_id, u8 copy_pin_IN1_id, u8 copy_pin_IN2_id)
{
	motor_port_id = copy_port_id;
	motor_IN1 = copy_pin_IN1_id;
	motor_IN2 = copy_pin_IN2_id;
	
	DIO_voidSetPinDirection(motor_port_id, motor_IN1, PIN_OUTPUT);
	DIO_voidSetPinDirection(motor_port_id, motor_IN2, PIN_OUTPUT);
	
	DIO_voidSetPinValue(motor_port_id, motor_IN1, PIN_LOW);
	DIO_voidSetPinValue(motor_port_id, motor_IN2, PIN_LOW);
	
	Timer0_vInit();
}

void Motor_ON(u8 copy_motor_direction, u8 duty_cycle_precentage)
{
	PWM_Timer0_Start(duty_cycle_precentage);
	
	if (copy_motor_direction == motor_clockwise_direction)
	{
		DIO_voidSetPinValue(motor_port_id, motor_IN1, PIN_HIGH);
		DIO_voidSetPinValue(motor_port_id, motor_IN2, PIN_LOW);
	} else if (copy_motor_direction == motor_anticlockwise_direction)
	{
		DIO_voidSetPinValue(motor_port_id, motor_IN1, PIN_LOW);
		DIO_voidSetPinValue(motor_port_id, motor_IN2, PIN_HIGH);
	}
}

void Motor_OFF()
{
	DIO_voidSetPinValue(motor_port_id, motor_IN1, PIN_LOW);
	DIO_voidSetPinValue(motor_port_id, motor_IN2, PIN_LOW);
	Timer0_vSetDutyCycle(0);
	Timer0_vStop();
}