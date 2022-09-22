/*
 * GlobalInterrupt.h
 *
 *  Created on: Sep 1, 2022
 *      Author: ahmad
 */

#ifndef INC_GLOBALINTERRUPT_H_
#define INC_GLOBALINTERRUPT_H_

#define SREG_I 7

void GlobalInterrupt_Enable(void);
void GlobalInterrupt_Disable(void);

#endif /* INC_GLOBALINTERRUPT_H_ */
