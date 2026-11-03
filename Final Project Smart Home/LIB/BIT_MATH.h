/*
 * BIT_MATH.h
 */ 


#ifndef BIT_MATH_H_
#define BIT_MATH_H_

#define SET_BIT(reg,pin) reg |= (1<<pin) // set 
#define CLR_BIT(reg,pin) reg &= (~(1<<pin)) // clear
#define GET_BIT(reg,pin) (reg>>pin) & 1 // get
#define TOGGLE_BIT(reg, pin) reg ^= (1<<pin) // toggle

#endif /* BIT_MATH_H_ */