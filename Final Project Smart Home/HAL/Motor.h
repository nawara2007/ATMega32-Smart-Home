/*
 * Motor.h
 *
 * Created: 9/18/2026 8:41:49 PM
 *  Author: mohamed nawara
 */ 


#ifndef MOTOR_H_
#define MOTOR_H_

#include "../MCAL/DIO.h"
#include "../LIB/STD_TYPES.h"
#include "../MCAL/TIMER0.h"

#define motor_clockwise_direction 0
#define motor_anticlockwise_direction 1

void Motor_init(u8 copy_port_id, u8 copy_pin_IN1_id, u8 copy_pin_IN2_id);
void Motor_ON(u8 copy_motor_direction, u8 duty_cycle_precentage);
void Motor_OFF();

#endif /* MOTOR_H_ */