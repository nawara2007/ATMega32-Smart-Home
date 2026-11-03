/*
 * TIMER0.h
 *  Author: Shamci
 */ 


#ifndef TIMER0_H_
#define TIMER0_H_

#include "EXT_INTERRUPT.h"

/*
 * choose from:
 * TIMER0_NORMAL_MODE        
 * TIMER0_CTC_MODE           
 * TIMER0_PHASECORRECT_MODE  
 * TIMER0_FASTPWM_MODE       
 */
#define TIMER0_MODE     TIMER0_FASTPWM_MODE 

/*
 * choose from:
 *   TIMER0_PRESCALER_1
 *   TIMER0_PRESCALER_8
 *   TIMER0_PRESCALER_64
 *   TIMER0_PRESCALER_256
 *   TIMER0_PRESCALER_1024
 *   TIMER0_PRESCALER_EXTCLK_FALLEDGE
 *   TIMER0_PRESCALER_EXTCLK_RAISEDGE
 */
#define TIMER0_PRESCALER     TIMER0_PRESCALER_1024

/*
 * choose from :
 *  Non PWM:
 *   TIMER0_OC0_DISCONNECTED
 *   TIMER0_OC0_TOG
 *   TIMER0_OC0_CLEAR
 *   TIMER0_OC0_SET
 *	PWM:
 *   TIMER_OC0_PWM_NON_INVERTING
 *   TIMER_OC0_PWM_INVERTING
 */
#define TIMER0_OC0_MODE  TIMER_OC0_PWM_NON_INVERTING

/*
 * select F_OSC
 */
#define F_OSC 16000000UL

#define TCCR0     (*((volatile u8*)0x53))
#define TIMSK     (*((volatile u8*)0x59))
#define TCNT0     (*((volatile u8*)0x52))
#define OCR0      (*((volatile u8*)0x5C))
#define DDRB      (*((volatile u8*)0x37))
#define OC0_PIN    3

// TCCR0 BITS
#define FOC0		   7
#define WGM00          6
#define COM01          5
#define COM00          4
#define WGM01          3
#define CS02           2
#define CS01           1
#define CS00           0

// TIMSK BITS
#define TOIE0          0
#define OCIE0          1

/*Timer Mode*/
#define   TIMER0_NORMAL_MODE        0
#define   TIMER0_CTC_MODE           1
#define   TIMER0_PHASECORRECT_MODE  2
#define   TIMER0_FASTPWM_MODE       3

/*Timer prescaler*/
#define    TIMER0_PRESCALER_1                   0
#define    TIMER0_PRESCALER_8                   1
#define    TIMER0_PRESCALER_64                  2
#define    TIMER0_PRESCALER_256                 3
#define    TIMER0_PRESCALER_1024                4
#define    TIMER0_PRESCALER_EXTCLK_FALLEDGE     5
#define    TIMER0_PRESCALER_EXTCLK_RAISEDGE     6

/*Timer OC0 Mode */
#define   TIMER0_OC0_DISCONNECTED        0
#define   TIMER0_OC0_TOG                 1
#define   TIMER0_OC0_CLEAR               2
#define   TIMER0_OC0_SET                 3	

#define	  TIMER_OC0_PWM_NON_INVERTING    4
#define	  TIMER_OC0_PWM_INVERTING	 	 5

#define TIMER0_OVF_INT_ID          0
#define TIMER0_COMP_MATCH_INT_ID   1

void Timer0_vInit(void);
void Timer0_vStop(void);
void Timer0_vStart(void);
void Timer0_vEnableInt(void);
void Timer0_vDisableInt(void);
void Timer0_vSetTime(u32 DesiredTime_ms);
u32 Timer0_u32GetRealPrescaler(void);

void Timer0_voidSetCallBack( void (*Copy_pvoidCallBack)(void));

void Timer0_vSetDutyCycle(u8 duty_cycle);
void PWM_Timer0_Start(u8 duty_cycle);
void PWM_Timer0_Stop();     


#endif /* TIMER0_H_ */