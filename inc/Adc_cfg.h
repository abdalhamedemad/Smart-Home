/*
 * Adc_cfg.h
 *
 *  Created on: Sep 4, 2022
 *      Author: ahmad
 */

#ifndef INC_ADC_CFG_H_
#define INC_ADC_CFG_H_

#define ADC_REF_AREF        1
#define ADC_REF_AVCC        2
#define ADC_REF_INTERNAL    3

#define ADC_INT_ENABLE      1
#define ADC_INT_DISABLE     2


/*OPTIONS:
-> ADC_REF_SELECTION
        ADC_REF_AREF
        ADC_REF_AVCC
        ADC_REF_INTERNAL
-> ADC_INT_STATE
        ADC_INT_ENABLE
        ADC_INT_DISABLE
-> ADC_PRESCALER
        128
        64
        32
        16
        8
        4
        2
*/

#define ADC_REF_SELECTION   ADC_REF_AREF
#define ADC_INT_STATE       ADC_INT_ENABLE
#define ADC_PRESCALER       128





#endif /* INC_ADC_CFG_H_ */
