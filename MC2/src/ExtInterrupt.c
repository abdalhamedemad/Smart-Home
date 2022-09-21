/*
 * ExtInterrupt.c
 *
 *  Created on: Sep 1, 2022
 *      Author: ahmad
 */


#include "std_types.h"
#include "macros.h"
#include "Registers.h"
#include "GlobalInterrupt.h"
#include "ExtInterrupt.h"
#include "ExtInterrupt_cfg.h"

void (*ExtInterrupt_INT0Callback) (void);
void (*ExtInterrupt_INT1Callback) (void);
void (*ExtInterrupt_INT2Callback) (void);

void __vector_1 (void) __attribute__ ((signal));
void __vector_1 (void) {
	ExtInterrupt_INT0Callback();
}
void __vector_2 (void) __attribute__ ((signal));
void __vector_2 (void) {
	ExtInterrupt_INT1Callback();
}
void __vector_3 (void) __attribute__ ((signal));
void __vector_3 (void) {
	ExtInterrupt_INT2Callback();
}

//void __vector_1 (void) __attribute__ ((signal));
//void __vector_1 (void) {
//	// TODO
//}

//void __vector_1 (void) __attribute__ ((signal));
//void __vector_1 (void) {
//	// TODO
//}

void ExtInterrupt_Init(void) {

    /*************************** Interrupt 0 Init ***************************/
#ifdef EXT_INTERRUPT_INT0
    /* Interrupt Enable */
#if EXT_INTERRUPT_INT0_INT_ENABLE == EXT_INTERRUPT_ENABLE
    //SET_BIT(GICR, GICR_INT0); // External Interrupt Request 0 Enable
    //GlobalInterrupt_Enable(); // Global Interrupt Enable
#elif EXT_INTERRUPT_INT0_INT_ENABLE == EXT_INTERRUPT_DISABLE
    CLR_BIT(GICR, GICR_INT0); // External Interrupt Request 0 Disable
    GlobalInterrupt_Disable(); // Global Interrupt Disable
#endif

    /* Sense Control */
#if EXT_INTERRUPT_INT0_SENSE == EXT_INTERRUPT_FALLING_EDGE
    /* The falling edge of INT0 generates an interrupt request. */
    CLR_BIT(MCUCR, MCUCR_ISC00);
    SET_BIT(MCUCR, MCUCR_ISC01);
#elif EXT_INTERRUPT_INT0_SENSE == EXT_INTERRUPT_RISING_EDGE
    SET_BIT(MCUCR, MCUCR_ISC00);
    SET_BIT(MCUCR, MCUCR_ISC01);
    // TODO
#elif EXT_INTERRUPT_INT0_SENSE == EXT_INTERRUPT_ON_CHANGE
    /* Any logical change on INT0 generates an interrupt request. */
    SET_BIT(MCUCR, MCUCR_ISC00);
    CLR_BIT(MCUCR, MCUCR_ISC01);
#elif (EXT_INTERRUPT_INT0_SENSE == EXT_INTERRUPT_LOW_LEVEL)
    CLR_BIT(MCUCR, MCUCR_ISC00);
    CLR_BIT(MCUCR, MCUCR_ISC01);
    // TODO
#else
    #error "Wrong Sense Control for INT0"
#endif
#endif



    /*************************** Interrupt 1 Init ***************************/

#ifdef EXT_INTERRUPT_INT1
    /* Interrupt Enable */
#if EXT_INTERRUPT_INT1_INT_ENABLE == EXT_INTERRUPT_ENABLE
   SET_BIT(GICR, GICR_INT0); // External Interrupt Request 1 Enable
    //GlobalInterrupt_Enable(); // Global Interrupt Enable
    // TODO
#elif EXT_INTERRUPT_INT1_INT_ENABLE == EXT_INTERRUPT_DISABLE
    CLR_BIT(GICR, GICR_INT1); // External Interrupt Request 0 Disable
    GlobalInterrupt_Disable(); // Global Interrupt Disable
    // TODO
#endif

    /* Sense Control */
#if EXT_INTERRUPT_INT1_SENSE == EXT_INTERRUPT_FALLING_EDGE
    CLR_BIT(MCUCR, MCUCR_ISC10);
    SET_BIT(MCUCR, MCUCR_ISC11);
    // TODO
#elif EXT_INTERRUPT_INT1_SENSE == EXT_INTERRUPT_RISING_EDGE
    SET_BIT(MCUCR, MCUCR_ISC10);
    SET_BIT(MCUCR, MCUCR_ISC11);
    // TODO
#elif EXT_INTERRUPT_INT1_SENSE == EXT_INTERRUPT_ON_CHANGE
    SET_BIT(MCUCR, MCUCR_ISC10);
    CLR_BIT(MCUCR, MCUCR_ISC11);
    // TODO
#elif EXT_INTERRUPT_INT1_SENSE == EXT_INTERRUPT_LOW_LEVEL
    CLR_BIT(MCUCR, MCUCR_ISC10);
    CLR_BIT(MCUCR, MCUCR_ISC11);
    // TODO
#else
    #error "Wrong Sense Control for INT1"
#endif
#endif


    /*************************** Interrupt 2 Init ***************************/
#ifdef EXT_INTERRUPT_INT2
    /* Interrupt Enable */
#if EXT_INTERRUPT_INT2_INT_ENABLE == EXT_INTERRUPT_ENABLE
    SET_BIT(GICR, GICR_INT2); // External Interrupt Request 1 Enable
   // GlobalInterrupt_Enable(); // Global Interrupt Enable
    // TODO
#elif EXT_INTERRUPT_INT2_INT_ENABLE == EXT_INTERRUPT_DISABLE
     CLR_BIT(GICR, GICR_INT2); // External Interrupt Request 0 Disable
    GlobalInterrupt_Disable(); // Global Interrupt Disable
    // TODO
#endif

    /* Sense Control */
#if EXT_INTERRUPT_INT2_SENSE == EXT_INTERRUPT_FALLING_EDGE
    CLR_BIT(MCUCR, MCUCSR_ISC2);
    // TODO
#elif EXT_INTERRUPT_INT2_SENSE == EXT_INTERRUPT_RISING_EDGE
    SET_BIT(MCUCR, MCUCSR_ISC2);
    // TODO
#else
    #error "Wrong Sense Control for INT2"
#endif
#endif



}

void ExtInterrupt_SetINT0Callback (void (*callback) (void)) {
    ExtInterrupt_INT0Callback = callback;
}

void ExtInterrupt_SetINT1Callback (void (*callback) (void)) {
    ExtInterrupt_INT1Callback = callback;
   // TODO
}

void ExtInterrupt_SetINT2Callback (void (*callback) (void)) {
    ExtInterrupt_INT2Callback = callback;
   // TODO
}

