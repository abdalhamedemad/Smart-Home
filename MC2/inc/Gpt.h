/*
 * Gpt.h
 *
 *  Created on: Sep 5, 2022
 *      Author: ahmad
 */

#ifndef INC_GPT_H_
#define INC_GPT_H_



typedef enum {
    GPT_ERROR,
    GPT_OK
} Gpt_ReturnType;


typedef enum {
    GPT_CHANNEL_TIMER0,
    GPT_CHANNEL_TIMER1A,
    GPT_CHANNEL_TIMER1B,
    GPT_CHANNEL_TIMER2
} Gpt_ChannelType;

typedef enum {
    GPT_MODE_NORMAL,
    GPT_MODE_CTC
} Gpt_ModeType;

typedef enum {
    GPT_OUTPUT_NORMAL,
    GPT_OUTPUT_TOGGLE,
    GPT_OUTPUT_SET,
    GPT_OUTPUT_CLEAR
} Gpt_OutputModeType;


typedef enum {
    GPT_PRESCALER_0,
    GPT_PRESCALER_1,
    GPT_PRESCALER_8,
    GPT_PRESCALER_32,
    GPT_PRESCALER_64,
    GPT_PRESCALER_128,
    GPT_PRESCALER_256,
    GPT_PRESCALER_1024,
    GPT_PRESCALER_EXT_FALLING,
    GPT_PRESCALER_EXT_RISING
} Gpt_PrescalerType;


typedef struct {
    Gpt_ChannelType channel;
    Gpt_ModeType mode;
    Gpt_OutputModeType output;
    Gpt_PrescalerType prescaler;
} Gpt_ConfigType;


Gpt_ReturnType Gpt_Init(Gpt_ConfigType* config);
Gpt_ReturnType Gpt_StartTimer (Gpt_ChannelType channel, u16 value);
void Gpt_EnableNotification (Gpt_ChannelType channel, Gpt_ModeType, void (*callback) (void));
void Gpt_DisableNotification (Gpt_ChannelType channel, Gpt_ModeType);
u16 Gpt_GetTimeElapsed (Gpt_ChannelType channel);
u16 Gpt_GetTimeRemaining (Gpt_ChannelType channel, Gpt_ModeType mode);

#endif /* INC_GPT_H_ */
