/*
 * LDR.h
 *
 * Created: 9/18/2026 7:56:57 PM
 *  Author: mohamed nawara
 */ 


#ifndef LDR_H_
#define LDR_H_

#include "../MCAL/ADC.h"
#include "../MCAL/DIO.h"
#include "../LIB/STD_TYPES.h"


void LDR_init(u8 channel_num);
u8 LDR_u8GetPrecent();

#endif /* LDR_H_ */