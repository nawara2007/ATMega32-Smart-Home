/*
 * LED.h
 *
 * Created: 8/13/2026 12:26:55 AM
 *  Author: mohamed nawara
 */ 


#ifndef LED_H_
#define LED_H_

#include "../MCAL/DIO.h"

void led_init(u8 port_id, u8 pin_name);

void led_on(u8 port_id, u8 pin_name);

void led_off(u8 port_id, u8 pin_name);

void led_toggle(u8 port_id, u8 pin_name);

#endif /* LED_H_ */