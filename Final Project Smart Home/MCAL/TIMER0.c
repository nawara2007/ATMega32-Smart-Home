/*
 * TIMER0.c
 *
 * Created: 9/5/2026 5:35:42 PM
 *  Author: mohamed nawara
 */
#include "TIMER0.h"

void Timer0_vInit(void)
{
	TCCR0 = 0;
	switch (TIMER0_MODE)
	{
		case TIMER0_NORMAL_MODE:
			CLR_BIT(TCCR0, WGM00);
			CLR_BIT(TCCR0, WGM01);
		break;
		case TIMER0_PHASECORRECT_MODE:
			SET_BIT(TCCR0, WGM00);
			CLR_BIT(TCCR0, WGM01);
		break;
		case TIMER0_CTC_MODE:
			CLR_BIT(TCCR0, WGM00);
			SET_BIT(TCCR0, WGM01);
		break;
		case TIMER0_FASTPWM_MODE:
			SET_BIT(TCCR0, WGM00);
			SET_BIT(TCCR0, WGM01);
			SET_BIT(DDRB, OC0_PIN);

			if (TIMER0_OC0_MODE == TIMER_OC0_PWM_NON_INVERTING)
			{
				CLR_BIT(TCCR0, COM00);   // clear on compare match
				SET_BIT(TCCR0, COM01);
			}
			else // inverting 
			{
				SET_BIT(TCCR0, COM00); // set on compare match
				SET_BIT(TCCR0, COM01);
			}
			OCR0 = 0;
		break;
	}
}

void Timer0_vStart(void)
{
	switch (TIMER0_PRESCALER)
	{
		case TIMER0_PRESCALER_1:
			SET_BIT(TCCR0, CS00);
			CLR_BIT(TCCR0, CS01);
			CLR_BIT(TCCR0, CS02);
		break;
		case TIMER0_PRESCALER_8:
			CLR_BIT(TCCR0, CS00);
			SET_BIT(TCCR0, CS01);
			CLR_BIT(TCCR0, CS02);
		break;
		case TIMER0_PRESCALER_64:
			SET_BIT(TCCR0, CS00);
			SET_BIT(TCCR0, CS01);
			CLR_BIT(TCCR0, CS02);
		break;
		case TIMER0_PRESCALER_256:
			CLR_BIT(TCCR0, CS00);
			CLR_BIT(TCCR0, CS01);
			SET_BIT(TCCR0, CS02);
		break;
		case TIMER0_PRESCALER_1024:
			SET_BIT(TCCR0, CS00);
			CLR_BIT(TCCR0, CS01);
			SET_BIT(TCCR0, CS02);
		break;
		case TIMER0_PRESCALER_EXTCLK_FALLEDGE:
			CLR_BIT(TCCR0, CS00);
			SET_BIT(TCCR0, CS01);
			SET_BIT(TCCR0, CS02);
		break;
		case TIMER0_PRESCALER_EXTCLK_RAISEDGE:
			SET_BIT(TCCR0, CS00);
			SET_BIT(TCCR0, CS01);
			SET_BIT(TCCR0, CS02);
		break;
	}
}

void Timer0_vSetDutyCycle(u8 duty_cycle)
{
	if (duty_cycle > 100) duty_cycle = 100;
	OCR0 = (u8)(((u16)duty_cycle * 255U) / 100U);
}

void PWM_Timer0_Start(u8 duty_cycle)
{
	Timer0_vSetDutyCycle(duty_cycle);
	Timer0_vStart();
}

void PWM_Timer0_Stop()
{
	Timer0_vSetDutyCycle(0);
	Timer0_vStop();
}

void Timer0_vStop(void)
{
	CLR_BIT(TCCR0, CS00);
	CLR_BIT(TCCR0, CS01);
	CLR_BIT(TCCR0, CS02);
}

void Timer0_vEnableInt(void)
{
	switch (TIMER0_MODE)
	{
		case TIMER0_NORMAL_MODE:
			SET_BIT(TIMSK, TOIE0);
			CLR_BIT(TIMSK, OCIE0);
		break;
		case TIMER0_CTC_MODE:
			CLR_BIT(TIMSK, TOIE0);
			SET_BIT(TIMSK, OCIE0);
		break;
		
	} 
}

void Timer0_vDisableInt(void)
{
	CLR_BIT(TIMSK, TOIE0);
	CLR_BIT(TIMSK, OCIE0);
}

volatile u32 global_overflow_target = 0;
volatile u8  global_preload_value = 0;

volatile u32 global_ctc_target = 0;

void Timer0_vSetTime(u32 DesiredTime_ms)
{
	u32 prescaler = Timer0_u32GetRealPrescaler();
	u32 total_ticks = (DesiredTime_ms * (F_OSC / 1000)) / prescaler;
	
	if (TIMER0_MODE == TIMER0_NORMAL_MODE)
	{
		global_overflow_target = total_ticks / 256;
		u8 remainder_ticks = total_ticks % 256;
		
		if (remainder_ticks > 0)
		{
			// Add an extra overflow to handle the remainder
			global_overflow_target++; 
			// Calculate what to preload into TCNT0 for the very first cycle
			global_preload_value = 256 - remainder_ticks; 
		}
		else
		{
			global_preload_value = 0;
		}
		
		TCNT0 = global_preload_value;
	}
	else if (TIMER0_MODE == TIMER0_CTC_MODE)
	{
		// Set a fixed compare value, e.g., 255. 
		// The timer will clear and fire interrupt every 201 ticks (OCR0 + 1)
		OCR0 = 200;
		
		// Calculate how many compare matches we need
		global_ctc_target = total_ticks / 201;
	}
}

u32 Timer0_u32GetRealPrescaler(void)
{
	switch (TIMER0_PRESCALER)
	{
		case TIMER0_PRESCALER_1:
			return 1;
		case TIMER0_PRESCALER_8:
			return 8;
		case TIMER0_PRESCALER_64:
			return 64;
		case TIMER0_PRESCALER_256:
			return 256;
		case TIMER0_PRESCALER_1024:
			return 1024;
		default: 
			return 1;
	}
}

static void (*Timer0_pvoidCallBack)(void) = {NULL};


void Timer0_voidSetCallBack( void (*Copy_pvoidCallBack)(void))
{
	Timer0_pvoidCallBack = Copy_pvoidCallBack;
}

ISR(TIMER0_OVF_vect)
{
	static u32 local_overflow_counter = 0;
	local_overflow_counter++;
	
	if (local_overflow_counter >= global_overflow_target)
	{
		// Time has elapsed, reset counter and reload TCNT0 for the next round
		local_overflow_counter = 0;
		TCNT0 = global_preload_value;
		
		// Fire the callback
		if (Timer0_pvoidCallBack != NULL)
		{
			Timer0_pvoidCallBack();
		}
	}
}

ISR(TIMER0_COMP_vect)
{
	static u32 local_ctc_counter = 0;
	local_ctc_counter++;
	
	if (local_ctc_counter >= global_ctc_target)
	{
		// Time has elapsed, reset counter
		local_ctc_counter = 0;
		
		// Fire the callback
		if (Timer0_pvoidCallBack != NULL)
		{
			Timer0_pvoidCallBack();
		}
	}
}