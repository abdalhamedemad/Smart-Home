/*
 * Adc.c

 *
 *  Created on: ??þ/??þ/????
 *      Author: ascom
 */

/*
 * Adc.c
 *
 *  Created on: Sep 4, 2022
 *      Author: ahmad
 */


#include "std_types.h"
#include "macros.h"
#include "Registers.h"
#include "int.h"
#include "Adc.h"
#include "Adc_cfg.h"
#include "GlobalInterrupt.h"

void (*Adc_Callback) (u16 res);

ISR(VECTOR_ADC) {
    Adc_Callback((ADC_DATA_REGISTER & 0b0000001111111111));
}

void Adc_Init(void) {
    /*Reference Selection Bits*/
#if (ADC_REF_SELECTION == ADC_REF_AREF)
    CLR_BIT(ADMUX, ADMUX_REFS1);
    CLR_BIT(ADMUX, ADMUX_REFS0);
#elif (ADC_REF_SELECTION == ADC_REF_AVCC)
    CLR_BIT(ADMUX, ADMUX_REFS1);
    SET_BIT(ADMUX, ADMUX_REFS0);
    // TODO
#elif (ADC_REF_SELECTION == ADC_REF_INTERNAL)
    SET_BIT(ADMUX, ADMUX_REFS1);
    SET_BIT(ADMUX, ADMUX_REFS0);
    // TODO
#else
    #error "Error Ref Selection Choise"
#endif

    /* No Left Adjust */
    CLR_BIT(ADMUX, ADMUX_ADLAR);

    /* ADC Enable */
    SET_BIT(ADCSRA, ADCSRA_ADEN);

    /* ADC Interrupt Enable */
#if (ADC_INT_STATE == ADC_INT_DISABLE)
    CLR_BIT(ADCSRA, ADCSRA_ADIE);
#elif (ADC_INT_STATE == ADC_INT_ENABLE)
    SET_BIT(ADCSRA, ADCSRA_ADIE);
    //GlobalInterrupt_Enable();
#else
    #error "Error Interrupt state choise"
#endif

    /* ADC Prescaler Select */

#if (ADC_PRESCALER == 128)
    SET_BIT(ADCSRA, ADCSRA_ADPS0);
    SET_BIT(ADCSRA, ADCSRA_ADPS1);
    SET_BIT(ADCSRA, ADCSRA_ADPS2);
#elif (ADC_PRESCALER == 64)
    CLR_BIT(ADCSRA, ADCSRA_ADPS0);
    SET_BIT(ADCSRA, ADCSRA_ADPS1);
    SET_BIT(ADCSRA, ADCSRA_ADPS2);
    // TODO
#elif (ADC_PRESCALER == 32)
    SET_BIT(ADCSRA, ADCSRA_ADPS0);
    CLR_BIT(ADCSRA, ADCSRA_ADPS1);
    SET_BIT(ADCSRA, ADCSRA_ADPS2);
    // TODO
#elif (ADC_PRESCALER == 16)
    CLR_BIT(ADCSRA, ADCSRA_ADPS0);
    CLR_BIT(ADCSRA, ADCSRA_ADPS1);
    SET_BIT(ADCSRA, ADCSRA_ADPS2);
    // TODO
#elif (ADC_PRESCALER == 8)
    SET_BIT(ADCSRA, ADCSRA_ADPS0);
    SET_BIT(ADCSRA, ADCSRA_ADPS1);
    CLR_BIT(ADCSRA, ADCSRA_ADPS2);
    // TODO
#elif (ADC_PRESCALER == 4)
    CLR_BIT(ADCSRA, ADCSRA_ADPS0);
    SET_BIT(ADCSRA, ADCSRA_ADPS1);
    CLR_BIT(ADCSRA, ADCSRA_ADPS2);
    // TODO
#elif (ADC_PRESCALER == 2)
    SET_BIT(ADCSRA, ADCSRA_ADPS0);
    CLR_BIT(ADCSRA, ADCSRA_ADPS1);
    CLR_BIT(ADCSRA, ADCSRA_ADPS2);
    // TODO
#else
    #error "Error Prescaler Choise"
#endif
}

void Adc_StartConversion(Adc_ChannelType channel) {
    ADMUX &= 0b11100000;
    ADMUX |= channel;
    SET_BIT(ADCSRA, ADCSRA_ADSC);
}

void Adc_Enable(void) {
    SET_BIT(ADCSRA, ADCSRA_ADEN);
    // TODO
}

void Adc_Disable(void) {
    CLR_BIT(ADCSRA, ADCSRA_ADEN);
    // TODO
}


Adc_ConversionStateType Adc_GetResult(u16* result) {
    Adc_ConversionStateType flag = ADC_CONVERSION_NOT_COMPLETE;
    if (GET_BIT(ADCSRA, ADCSRA_ADIF) == 1) {
        SET_BIT(ADCSRA, ADCSRA_ADIF);
        *result = ADC_DATA_REGISTER & 0b0000001111111111;
        flag = ADC_CONVERSION_COMPLETE;
    }
    return flag;
}

u16 Adc_GetResultPolling(void) {
    while (GET_BIT(ADCSRA, ADCSRA_ADIF) == 0);
    return (ADC_DATA_REGISTER & 0b0000001111111111);
}


void Adc_SetCallback (void (*callback) (u16 res)) {
    Adc_Callback = callback;
	}



