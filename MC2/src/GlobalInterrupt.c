/*
 * GlobalInterrupt.c
 *
 *  Created on: Sep 1, 2022
 *      Author: ahmad
 */

#include "std_types.h"
#include "macros.h"
#include "Registers.h"
#include "GlobalInterrupt.h"

void GlobalInterrupt_Enable(void) {
	SET_BIT(SREG, SREG_I);
}

void GlobalInterrupt_Disable(void) {
	CLR_BIT(SREG, SREG_I);
}
