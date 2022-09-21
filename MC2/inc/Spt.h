/*
 * Spt.h
 *
 *  Created on: ??�/??�/????
 *      Author: ascom
 */

#ifndef INC_SPT_H_
#define INC_SPT_H_
#include "std_types.h"

typedef enum {
    SPT_ERROR,
    SPT_OK
} Spt_ReturnType;

typedef enum {
    SPT_CHANNEL_TIMER0,
    SPT_CHANNEL_TIMER1A,
    SPT_CHANNEL_TIMER1B,
    SPT_CHANNEL_TIMER2
} Spt_ChannelType;

typedef enum {
    SPT_MODE_FAST_PWM,
    SPT_MODE_PWM_PHASE_CORRECT
} Spt_ModeType;

typedef enum {
    SPT_OUTPUT_NORMAL,
    SPT_OUTPUT_TOGGLE,
    SPT_OUTPUT_SET,
    SPT_OUTPUT_CLEAR
} Spt_OutputModeType;

typedef enum {
    SPT_PRESCALER_0,
    SPT_PRESCALER_1,
    SPT_PRESCALER_8,
    SPT_PRESCALER_32,
    SPT_PRESCALER_64,
    SPT_PRESCALER_128,
    SPT_PRESCALER_256,
    SPT_PRESCALER_1024,
    SPT_PRESCALER_EXT_FALLING,
    SPT_PRESCALER_EXT_RISING
} Spt_PrescalerType;

typedef struct {
    Spt_ChannelType channel;
    Spt_ModeType mode;
    Spt_OutputModeType output;
    Spt_PrescalerType prescaler;
} Spt_ConfigType;


Spt_ReturnType Spt_Init(Spt_ConfigType* config);
Spt_ReturnType Spt_StartTimer(Spt_ChannelType channel, u16 value);
void Spt_Set_ICR1(u16 value);
u16 Get_OCR_Value (u8 angle);

#endif /* INC_SPT_H_ */
