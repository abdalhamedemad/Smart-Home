/*
 * ExtInterrupt.h
 *
 *  Created on: Sep 1, 2022
 *      Author: ahmad
 */

#ifndef INC_EXTINTERRUPT_H_
#define INC_EXTINTERRUPT_H_

#define MCUCR_ISC00 0
#define MCUCR_ISC01 1
#define MCUCR_ISC10 2
#define MCUCR_ISC11 3
#define MCUCSR_ISC2 6
#define GICR_INT0 6
#define GICR_INT1 7
#define GICR_INT2 5

void ExtInterrupt_Init(void);
void ExtInterrupt_SetINT0Callback (void (*callback) (void));
void ExtInterrupt_SetINT1Callback (void (*callback) (void));
void ExtInterrupt_SetINT2Callback (void (*callback) (void));
#endif /* INC_EXTINTERRUPT_H_ */
