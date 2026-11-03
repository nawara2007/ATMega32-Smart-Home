/*
 * Flame.h
 *
 * Created: 9/18/2026 9:01:28 PM
 *  Author: mohamed nawara
 */ 


#ifndef FLAME_H_
#define FLAME_H_

#include "../MCAL/DIO.h"
#include "../MCAL/EXT_INTERRUPT.h"

void Flame_init(u8 Copy_u8INT_Number, void (*Copy_pvoidCallBack)(void));
u8 FLAME_PinState();

#endif /* FLAME_H_ */