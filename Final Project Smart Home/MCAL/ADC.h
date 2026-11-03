/*
 * ADC.h
 *  Author: Doha Mohamed
 */ 


#ifndef ADC_H_
#define ADC_H_

#include "../LIB/STD_TYPES.h"
#include "EXT_INTERRUPT.h"
#include "../LIB/BIT_MATH.h"

#define ADMUX				(*((volatile u8*)0x27))		//ADC multiplexer selection register
#define ADCSRA				(*((volatile u8*)0x26))		//ADC control and status register A
#define ADCH				(*((volatile u8*)0x25))		//ADC high register
#define ADCL				(*((volatile u8*)0x24))	
#define ADCLH				(*((volatile u16*)0x24))	//ADC Low register
#define SFIOR				(*((volatile u8 *)0x50))

/* ADMUX Bits   */
#define ADMUX_REFS1         7							//Reference selection bit1
#define ADMUX_REFS0         6							//Reference selection bit0
#define ADMUX_ADLAR         5							//ADC left adjust result

/* ADCSRA Bits   */
#define ADCSRA_ADEN			7							//ADC enable
#define ADCSRA_ADSC			6                           //Start conversion
#define ADCSRA_ADATE	    5                           //Auto trigger enable
#define ADCSRA_ADIF			4                           //Interrupt flag
#define ADCSRA_ADIE			3                           //Interrupt enable
#define ADCSRA_ADPS2	    2                           //Prescaler bit2
#define ADCSRA_ADPS1	    1                           //Prescaler bit1
#define ADCSRA_ADPS0	    0                           //Prescaler bit0

/* SFIOR Bits   */
#define SFIOR_ADTS2			7                          //Trigger Source bit2
#define SFIOR_ADTS1	     	6                          //Trigger Source bit1
#define SFIOR_ADTS0		    5                          //Trigger Source bit0
 

#define ADC_DISABLE             0
#define ADC_ENABLE              1

/*Interrupt*/
#define INT_DISABLE             0
#define INT_ENABLE              1

/*ADC Voltage Reference*/
#define AREF                    0
#define AVCC                    1
#define INTERNAL_2_56           3

/*Adjust Result*/
#define RIGHT_ADJUSTMENT        0
#define LEFT_ADJUSTMENT         1

/*ADC Channels*/
#define ADC_CHANNEL0            0
#define ADC_CHANNEL1            1
#define ADC_CHANNEL2            2
#define ADC_CHANNEL3            3
#define ADC_CHANNEL4            4
#define ADC_CHANNEL5            5
#define ADC_CHANNEL6            6
#define ADC_CHANNEL7            7
#define ADMUX_MASK 0x1F

#define ADC_SINGLE_CONVERSION   0
#define ADC_FREE_RUNNING        1   
#define ADC_ANALOG_COMPARATOR   2
#define ADC_EXTI0               3
#define ADC_TIM0_CTC            4
#define ADC_TIM0_OVF            5
#define ADC_TIM1_CTC_CHANNEL_B  6
#define ADC_TIM1_OVF            7
#define ADC_TIM1_ICU            8

/*Prescaler*/
#define ADC_PRE_2               0
#define ADC_PRE_4               2
#define ADC_PRE_8               3
#define ADC_PRE_16              4
#define ADC_PRE_32              5
#define ADC_PRE_64              6
#define ADC_PRE_128             7

/*******************************************
*			   Definitions				   *
*******************************************/
/* 
 Options:-
 	 1-ADC_ENABLE
 	 2-ADC_DISABLE

 */

#define ADC_STATUS   ADC_ENABLE

/*
 Options:-
 	 1-INT_ENABLE
 	 2-INT_DISABLE

 */

#define INT_STATUS   INT_ENABLE


/*
 Options:-
 	 1-AREF
 	 2-AVCC
 	 3-INTERNAL_2_56

 */

#define ADC_VREF  AVCC
/*
  Options :
 	 1-RIGHT_ADJUSTMENT
 	 2-LEFT_ADJUSTMENT

  */

#define ADC_ADJUSTMENT RIGHT_ADJUSTMENT

/*
 Options:-
 	 1-ADC_CHANNEL0
 	 2-ADC_CHANNEL1
 	 3-ADC_CHANNEL2
 	 4-ADC_CHANNEL3
 	 5-ADC_CHANNEL4
 	 6-ADC_CHANNEL5
 	 7-ADC_CHANNEL6
 	 8-ADC_CHANNEL7


 */

//#define ADC_CHANNEL  ADC_CHANNEL0

/*
 Options:-
 	 1-ADC_SINGLE_CONVERSION
 	 2-ADC_FREE_RUNNING
 	 3-ADC_ANALOG_COMPARATOR
 	 4-ADC_EXTI0
 	 5-ADC_TIM0_CTC
 	 6-ADC_TIM0_OVF
 	 7-ADC_TIM1_CTC_CHANNEL_B
 	 8-ADC_TIM1_OVF
 	 9-ADC_TIM1_ICU

 */

#define ADC_TRIGGERING_SOURCE   ADC_SINGLE_CONVERSION

/*
 Options:-
 	 1-ADC_PRE_2
 	 2-ADC_PRE_4
 	 3-ADC_PRE_8
 	 4-ADC_PRE_16
 	 5-ADC_PRE_32
 	 6-ADC_PRE_64
 	 7-ADC_PRE_128

 */

#define  ADC_PRESCALLER   ADC_PRE_128

#define  ADC_VOLTAGE_REF_mv      5000
#define  ADC_MAX_NO_OF_STEPS	 1024
/*******************************************
*			   Function Prototypes		    *
*******************************************/

/*
*Selecting voltage reference
*Selecting Adjustment
*Selecting ADC Mode
*Enable ADC
*/
void ADC_voidInit             ( void );
/*Select ADC Channel*/
/*Start conversion */

void ADC_voidStartConversion  (u8 Copy_u8Channel_num);
u16 ADC_u16GetResult           (void); 
u16 ADC_u16GetResultSync(u8 Copy_u8Channel_num);   
void ADC_voidSetPrescaler       ();

/*INTERRUPTS*/
void ADC_enableInt             (void);
void ADC_disableInt            (void);
void ADC_setCallBack               (void(*CopyFuncPtr) (void));
#endif /* ADC_H_ */