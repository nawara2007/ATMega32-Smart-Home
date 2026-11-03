/*
 * LM35.h
 *
 * Created: 9/18/2026 10:59:54 PM
 *  Author: mohamed nawara
 */ 


#ifndef LM35_H_
#define LM35_H_

#include "../MCAL/DIO.h"
#include "../MCAL/ADC.h"

void LM35_init(u8 channel_num);
u16 LM35_u16getCelsius();


#endif /* LM35_H_ */