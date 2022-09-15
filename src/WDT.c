/*
 * WDT.c
 *
 *  Created on: ??�/??�/????
 *      Author: ascom
 */

#include "std_types.h"
#include "macros.h"
#include "Registers.h"
#include "WDT.h"

void WDT_Enable (void) {
    SET_BIT(WDTCR,3);
}
void WDT_Disable (void) {
    WDTCR=0b00011000;
    //WDTCR=0;
}
void WDT_SleepTime (void) {
    //WDTCR=0b0001000;
    #if (TIME_OUT == 16) 
    CLR_BIT(WDTCR,0);
    CLR_BIT(WDTCR,1);
    CLR_BIT(WDTCR,2);
    #elif (TIME_OUT == 32) 
    SET_BIT(WDTCR,0);
    CLR_BIT(WDTCR,1);
    CLR_BIT(WDTCR,2);
    #elif (TIME_OUT == 65)
    CLR_BIT(WDTCR,0);
    SET_BIT(WDTCR,1);
    CLR_BIT(WDTCR,2);
    #elif (TIME_OUT == 130)
    SET_BIT(WDTCR,0);
    SET_BIT(WDTCR,1);
    CLR_BIT(WDTCR,2);
    #elif (TIME_OUT == 260)
    CLR_BIT(WDTCR,0);
    CLR_BIT(WDTCR,1);
    SET_BIT(WDTCR,2);
    #elif (TIME_OUT == 520)
    SET_BIT(WDTCR,0);
    CLR_BIT(WDTCR,1);
    SET_BIT(WDTCR,2);
    #elif (TIME_OUT == 1000)
    CLR_BIT(WDTCR,0);
    SET_BIT(WDTCR,1);
    SET_BIT(WDTCR,2);
    #elif (TIME_OUT == 2100)
    SET_BIT(WDTCR,0);
    SET_BIT(WDTCR,1);
    SET_BIT(WDTCR,2);
    #endif
}
