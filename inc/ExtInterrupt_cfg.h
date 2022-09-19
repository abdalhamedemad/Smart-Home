/*
 * ExtInterrupt_cfg.h
 *
 *  Created on: Sep 1, 2022
 *      Author: ahmad
 */

#ifndef INC_EXTINTERRUPT_CFG_H_
#define INC_EXTINTERRUPT_CFG_H_


#define EXT_INTERRUPT_ENABLE 0
#define EXT_INTERRUPT_DISABLE 1

#define EXT_INTERRUPT_FALLING_EDGE 0
#define EXT_INTERRUPT_RISING_EDGE 1
#define EXT_INTERRUPT_ON_CHANGE 2
#define EXT_INTERRUPT_LOW_LEVE 3


/*
Define the interrupt to initialize
        Options:
            -> EXT_INTERRUPT_INT0
            -> EXT_INTERRUPT_INT1
            -> EXT_INTERRUPT_INT2
Define the interrupt enable state for each interrupt (INT0, INT1, INT2)
        Options:
            -> EXT_INTERRUPT_ENABLE
            -> EXT_INTERRUPT_DISABLE
Define the interrupt sense control
        Options:
            -> EXT_INTERRUPT_FALLING_EDGE
            -> EXT_INTERRUPT_RISING_EDGE
            -> EXT_INTERRUPT_ON_CHANGE (for INT0, INT1 only)
            -> EXT_INTERRUPT_LOW_LEVEL (for INT0, INT1 only)
*/

#define EXT_INTERRUPT_INT0
#define EXT_INTERRUPT_INT1
#define EXT_INTERRUPT_INT2

#define EXT_INTERRUPT_INT0_INT_ENABLE EXT_INTERRUPT_ENABLE
#define EXT_INTERRUPT_INT0_SENSE EXT_INTERRUPT_ON_CHANGE

#define EXT_INTERRUPT_INT1_INT_ENABLE EXT_INTERRUPT_ENABLE
#define EXT_INTERRUPT_INT1_SENSE EXT_INTERRUPT_ON_CHANGE

#define EXT_INTERRUPT_INT2_INT_ENABLE EXT_INTERRUPT_DISABLE
#define EXT_INTERRUPT_INT2_SENSE EXT_INTERRUPT_FALLING_EDGE


#endif /* INC_EXTINTERRUPT_CFG_H_ */
