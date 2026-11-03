/*
 * EXT_INTERRUPT.h
 *  Author: Doha Mohamed
 */ 


#ifndef EXT_INTERRUPT_H_
#define EXT_INTERRUPT_H_


#include "../LIB/BIT_MATH.h"
#include "../LIB/STD_TYPES.h"

#define SREG                 *((volatile u8*) 0x5F)  //Status register ---------- Global Interrupt Enable
#define SREG_I               7

#define GICR                 *((volatile u8*) 0x5B)  //General Interrupt Control Register ------- control the EXTI enable
#define GICR_INT0            6
#define GICR_INT1            7
#define GICR_INT2            5

#define GIFR                 *((volatile u8*) 0x5A)  //General Interrupt Flag Register -------- EXTI flag
#define GIFR_INT0            6
#define GIFR_INT1            7
#define GIFR_INT2            5

#define MCUCR                *((volatile u8*) 0x55)  //MCU Control Register --------- EXTI0,1 status
#define MCUCR_ISC00          0
#define MCUCR_ISC01          1
#define MCUCR_ISC10          2
#define MCUCR_ISC11          3

#define MCUCSR               *((volatile u8*) 0x54)  //MCU Control and Status Register -------- EXTI2 status
#define MCUCSR_ISC2          6



/* Copy_u8Sense_Control */
#define      LOW_LEVEL        0
#define      LOGICAL_CHANGE   1
#define      FALLNG_EDGE      2
#define      RISING_EDGE      3


/* Copy_u8EXT_INT_Number */
#define EXT_INT0_ID     0
#define EXT_INT1_ID     1
#define EXT_INT2_ID     2


#define      ENABLED         1
#define      DISABLED        0

/* */
#define _VECTOR(N)		__vector_ ## N         // ## -> concatinate     if N=1  ->  __vector_1

/* VECT_NO */
#define INT0_vect		_VECTOR(1)
#define INT1_vect		_VECTOR(2)
#define INT2_vect		_VECTOR(3)
#define TIMER2_COMP_vect			_VECTOR(4)
#define TIMER2_OVF_vect				_VECTOR(5)
#define TIMER1_CAPT_vect			_VECTOR(6)
#define TIMER1_COMPA_vect			_VECTOR(7)
#define TIMER1_COMPB_vect			_VECTOR(8)
#define TIMER1_OVF_vect				_VECTOR(9)
#define TIMER0_COMP_vect			_VECTOR(10)
#define TIMER0_OVF_vect				_VECTOR(11)
#define SPI_STC_vect				_VECTOR(12)
#define USART_RXC_vect				_VECTOR(13)
#define USART_UDRE_vect				_VECTOR(14)
#define USART_TXC_vect				_VECTOR(15)
#define ADC_vect					_VECTOR(16)
#define EE_RDY_vect					_VECTOR(17)
#define ANA_COMP_vect				_VECTOR(18)
#define TWI_vect					_VECTOR(19)
#define SPM_RDY_vect				_VECTOR(20)



#define  ISR(VECT_NO)		\
void VECT_NO(void) __attribute__((signal));\
void VECT_NO(void)



#define sei()		__asm__ __volatile__ ("sei")		//Set Global Interrupt Enable
#define cli()		__asm__ __volatile__ ("cli")		//Close Global Interrupt



void EXTI_voidGlobalINT_Enable();                                                           //IMP

void EXTI_voidGlobalINT_Disable();

void EXTI_voidInit(u8 Copy_u8INT_Number, u8 Copy_u8Sense_Control);                          //IMP IMP IMP

void EXTI_voidDisableInterrupt(u8 Copy_u8INT_Number);

void EXTI_voidEnableInterrupt(u8 Copy_u8INT_Number);

u8   EXTI_u8GetFlag(u8 Copy_u8INT_Number);

void EXTI_voidSetCallBack(void (*Copy_pvoidCallBack)(void) , u8 Copy_u8INT_Number);          //IMP



#endif /* EXT_INTERRUPT_H_ */
