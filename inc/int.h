/*
 * int.h
 *
 *  Created on: Sep 4, 2022
 *      Author: ahmad
 */

#ifndef INC_INT_H_
#define INC_INT_H_

#define VECTOR_EXT_INT0     __vector_1
#define VECTOR_EXT_INT1     __vector_2
#define VECTOR_EXT_INT2     __vector_3
#define VECTOR_ADC          __vector_16
#define VECTOR_TIMER0_NORM  __vector_11
#define VECTOR_TIMER0_CTC   __vector_10
#define VECTOR_TIMER1_NORM  __vector_9
#define VECTOR_TIMER1A_CTC  __vector_7
#define VECTOR_TIMER1B_CTC  __vector_8
#define VECTOR_TIMER2_NORM  __vector_5
#define VECTOR_TIMER2_CTC   __vector_4


#  define ISR(vector)            \
    void vector (void) __attribute__ ((signal)); \
    void vector (void)


#endif /* INC_INT_H_ */
