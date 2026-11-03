/*
 * Buzzer.h
 *
 * Created: 9/18/2026 8:24:54 PM
 *  Author: mohamed nawara
 */ 


#ifndef BUZZER_H_
#define BUZZER_H_
#include "../MCAL/DIO.h"

void BUZZER_init(u8 copy_port_id, u8 copy_pin_id);
void BUZZER_ON();
void BUZZER_OFF();



#endif /* BUZZER_H_ */