/*
 * DIO.h
 */ 

#ifndef DIO_H_
#define DIO_H_

#include <avr/io.h>
#include "../LIB/STD_TYPES.h"
#include "../LIB/BIT_MATH.h"

//PORT A REGISTERS:
/*
#define PORTA  *((volatile u8*)0x00)
#define DDRA   *((volatile u8*)0x00)
#define PINA   *((volatile u8*)0x00)

//PORT B REGISTERS:
#define PORTB  *((volatile u8*)0x38)
#define DDRB   *((volatile u8*)0X37)
#define PINB   *((volatile u8*)0X36)

//PORT C REGISTERS:
#define PORTC  *((volatile u8*)0x26)
#define DDRC   *((volatile u8*)0x27)
#define PINC   *((volatile u8*)0x28)

//PORT D REGISTERS
#define PORTD  *((volatile u8*)0x32)
#define DDRD   *((volatile u8*)0x31)
#define PIND   *((volatile u8*)0x30)
*/
/*******************************************
*			   Definitions				   *
*******************************************/

#define NUM_OF_PORTS			4
#define NUM_OF_PINS_PER_PORT	8

#define PORTA_ID			0
#define PORTB_ID			1
#define PORTC_ID			2
#define PORTD_ID			3

#define PIN0		0
#define PIN1		1
#define PIN2		2
#define PIN3		3
#define PIN4		4
#define PIN5		5
#define PIN6		6
#define PIN7		7


/*******************************************
*			   Types Declaration		    *
*******************************************/

#define PIN_LOW			0
#define PIN_HIGH		1

#define PIN_INPUT		0
#define PIN_OUTPUT		1

#define PORT_LOW		0
#define PORT_HIGH		0xFF

#define PORT_INPUT		0
#define PORT_OUTPUT		0xFF

/*******************************************
*			   Function Prototypes		    *
*******************************************/

/*
 * Description :
 * Setup the direction of the required port all pins input/output.
 * If the direction value is PORT_INPUT all pins in this port should be input pins.
 * If the direction value is PORT_OUTPUT all pins in this port should be output pins.
 * If the input port number is not correct, The function will not handle the request.
 */
void DIO_voidSetPortDirection(u8 Copy_u8PORT, u8 Copy_u8Direction);

void DIO_voidTogglePortValue(u8 Copy_u8PORT);
/*
 * Description :
 * Write the value on the required port.
 * If any pin in the port is output pin the value will be written.
 * If any pin in the port is input pin this will activate/deactivate the internal pull-up resistor.
 * If the input port number is not correct, The function will not handle the request.
 */
void DIO_voidSetPortValue(u8 Copy_u8PORT, u8 Copy_u8Value);/*Write*/

/*
 * Description :
 * Read and return the value of the required port.
 * If the input port number is not correct, The function will return ZERO value.
 */
u8 DIO_u8GetPortValue(u8 Copy_u8PORT);/*Read*/

/*
 * Description :
 * Setup the direction of the required pin input/output.
 * If the input port number or pin number are not correct, The function will not handle the request.
 */
void DIO_voidSetPinDirection(u8 Copy_u8PORT, u8 Copy_u8Pin, u8 Copy_u8Direction);

/*
 * Description :
 * Write the value Logic High or Logic Low on the required pin.
 * If the input port number or pin number are not correct, The function will not handle the request.
 * If the pin is input, this function will enable/disable the internal pull-up resistor.
 */
void DIO_voidSetPinValue(u8 Copy_u8PORT, u8 Copy_u8Pin, u8 Copy_u8Value);/*Write*/

/*
 * Description :
 * Read and return the value for the required pin, it should be Logic High or Logic Low.
 * If the input port number or pin number are not correct, The function will return Logic Low.
 */
u8 DIO_u8GetPinValue(u8 Copy_u8PORT, u8 Copy_u8Pin); /*Read*/

void DIO_voidTogglePinValue(u8 Copy_u8PORT, u8 Copy_u8Pin);

#endif /* DIO_H_ */