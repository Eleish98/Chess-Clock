/************************************************/
/*	Author		:		Mohamed G. ELeish		*/
/*	Date		:		4 September 2021		*/
/*	Version		:		V01						*/
/************************************************/

/************************************************/
/************************************************/
/*****					LOG					*****/
/*	4/9/2021:	File Created					*/
/************************************************/
/************************************************/

#ifndef BIT_MATH_H_INCLUDED
#define BIT_MATH_H_INCLUDED

#define SET_BIT(VAR,BIT)		(VAR |= (1<<BIT))
#define CLR_BIT(VAR,BIT)		(VAR &= ~(1<<BIT))
#define TOG_BIT(VAR,BIT)		(VAR ^= (1<<BIT))
#define GET_BIT(VAR,BIT)		((VAR>>BIT) & 1)
#define CHK_BIT(VAR,BIT)		(VAR & (1<<BIT))


#endif