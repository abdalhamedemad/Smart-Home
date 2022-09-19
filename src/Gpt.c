/*
 * Gpt.c
 *
 *  Created on: Sep 5, 2022
 *      Author: ahmad
 */

#include "std_types.h"
#include "macros.h"
#include "Registers.h"
#include "int.h"
#include "Gpt.h"

/************ TIMER 0 Bits ************/
#define TCCR0_WGM00 6
#define TCCR0_WGM01 3
#define TCCR0_COM00 4
#define TCCR0_COM01 5
#define TCCR0_CS00 0
#define TCCR0_CS01 1
#define TCCR0_CS02 2
#define TIMSK_OCIE0 1
#define TIMSK_TOIE0 0

/************ TIMER 1 Bits ************/
#define TCCR1A_WGM10 0
#define TCCR1A_WGM11 1
#define TCCR1A_COM1B0 4
#define TCCR1A_COM1B1 5
#define TCCR1A_COM1A0 6
#define TCCR1A_COM1A1 7
#define TCCR1A_FOC1A 3
#define TCCR1A_FOC1B 2
#define TCCR1B_CS10 0
#define TCCR1B_CS11 1
#define TCCR1B_CS12 2
#define TCCR1B_WGM12 3
#define TCCR1B_WGM13 4
#define TCCR1B_ICES1 6
#define TCCR1B_ICNC1 7
#define TIMSK_OCIE1A 4
#define TIMSK_OCIE1B 3
#define TIMSK_TOIE1 2
#define TIMSK_OCIE2 7
#define TIMSK_TOIE2 6
// TODO

/************ TIMER 2 Bits ************/
#define TCCR2_WGM20 6
#define TCCR2_WGM21 3
#define TCCR2_COM20 4
#define TCCR2_COM21 5
#define TCCR2_CS20 0
#define TCCR2_CS21 1
#define TCCR2_CS22 2
// TODO

/************ ISR Callbacks ************/
void (*Gpt_Timer0_Callback_Ctc)(void);
void (*Gpt_Timer0_Callback_Normal)(void);
void (*Gpt_Timer1A_Callback_Ctc)(void);
void (*Gpt_Timer1B_Callback_Ctc)(void);
void (*Gpt_Timer1_Callback_Normal)(void);
void (*Gpt_Timer2_Callback_Ctc)(void);
void (*Gpt_Timer2_Callback_Normal)(void);

/************ ISR ************/
ISR(VECTOR_TIMER0_CTC)
{
    Gpt_Timer0_Callback_Ctc();
}
ISR(VECTOR_TIMER0_NORM)
{
    Gpt_Timer0_Callback_Normal();
}
ISR(VECTOR_TIMER1_NORM)
{
    Gpt_Timer1_Callback_Normal();
}
ISR(VECTOR_TIMER1A_CTC)
{
    Gpt_Timer1A_Callback_Ctc();
}
ISR(VECTOR_TIMER1B_CTC)
{
    Gpt_Timer1B_Callback_Ctc();
}
ISR(VECTOR_TIMER2_NORM)
{
    Gpt_Timer2_Callback_Normal();
}
ISR(VECTOR_TIMER2_CTC)
{
    Gpt_Timer2_Callback_Ctc();
}

Gpt_ReturnType Gpt_Init(Gpt_ConfigType *config)
{
    Gpt_ReturnType returnValue = GPT_OK;

    switch (config->channel)
    {

    case GPT_CHANNEL_TIMER0:
        /*Waveform Generation Mode*/
        if (config->mode == GPT_MODE_NORMAL)
        {
            CLR_BIT(TCCR0, TCCR0_WGM00);
            CLR_BIT(TCCR0, TCCR0_WGM01);
        }
        else if (config->mode == GPT_MODE_CTC)
        {
            CLR_BIT(TCCR0, TCCR0_WGM00);
            SET_BIT(TCCR0, TCCR0_WGM01);
        }
        else
        {
            returnValue = GPT_ERROR;
        }

        /*Compare Match Output Mode*/
        switch (config->output)
        {
        case GPT_OUTPUT_NORMAL:
            CLR_BIT(TCCR0, TCCR0_COM00);
            CLR_BIT(TCCR0, TCCR0_COM01);
            break;
        case GPT_OUTPUT_TOGGLE:
            SET_BIT(TCCR0, TCCR0_COM00);
            CLR_BIT(TCCR0, TCCR0_COM01);
            // TODO
            break;
        case GPT_OUTPUT_SET:
            SET_BIT(TCCR0, TCCR0_COM00);
            SET_BIT(TCCR0, TCCR0_COM01);
            // TODO
            break;
        case GPT_OUTPUT_CLEAR:
            CLR_BIT(TCCR0, TCCR0_COM00);
            SET_BIT(TCCR0, TCCR0_COM01);
            // TODO
            break;
        default:
            returnValue = GPT_ERROR;
            break;
        }

        /*Clock Select*/
        switch (config->prescaler)
        {
        case GPT_PRESCALER_0:
            CLR_BIT(TCCR0, TCCR0_CS00);
            CLR_BIT(TCCR0, TCCR0_CS01);
            CLR_BIT(TCCR0, TCCR0_CS02);
            break;
        case GPT_PRESCALER_1:
            SET_BIT(TCCR0, TCCR0_CS00);
            CLR_BIT(TCCR0, TCCR0_CS01);
            CLR_BIT(TCCR0, TCCR0_CS02);
            break;
        case GPT_PRESCALER_8:
            CLR_BIT(TCCR0, TCCR0_CS00);
            SET_BIT(TCCR0, TCCR0_CS01);
            CLR_BIT(TCCR0, TCCR0_CS02);
            break;
        case GPT_PRESCALER_64:
            SET_BIT(TCCR0, TCCR0_CS00);
            SET_BIT(TCCR0, TCCR0_CS01);
            CLR_BIT(TCCR0, TCCR0_CS02);
            // TODO
            break;
        case GPT_PRESCALER_256:
            CLR_BIT(TCCR0, TCCR0_CS00);
            CLR_BIT(TCCR0, TCCR0_CS01);
            SET_BIT(TCCR0, TCCR0_CS02);
            // TODO
            break;
        case GPT_PRESCALER_1024:
            SET_BIT(TCCR0, TCCR0_CS00);
            CLR_BIT(TCCR0, TCCR0_CS01);
            SET_BIT(TCCR0, TCCR0_CS02);
            break;
        case GPT_PRESCALER_EXT_FALLING:
            CLR_BIT(TCCR0, TCCR0_CS00);
            SET_BIT(TCCR0, TCCR0_CS01);
            SET_BIT(TCCR0, TCCR0_CS02);
            // TODO
            break;
        case GPT_PRESCALER_EXT_RISING:
            SET_BIT(TCCR0, TCCR0_CS00);
            SET_BIT(TCCR0, TCCR0_CS01);
            SET_BIT(TCCR0, TCCR0_CS02);
            // TODO
            break;
        default:
            returnValue = GPT_ERROR;
            break;
        }
        break;

    case GPT_CHANNEL_TIMER1A:
        /*Waveform Generation Mode*/
        if (config->mode == GPT_MODE_NORMAL)
        {
            CLR_BIT(TCCR1A,TCCR1A_WGM10);
            CLR_BIT(TCCR1A,TCCR1A_WGM11);
            CLR_BIT(TCCR1B,TCCR1B_WGM12);
            CLR_BIT(TCCR1B,TCCR1B_WGM13);
            // TODO
            // TODO
        }
        else if (config->mode == GPT_MODE_CTC)
        {
            CLR_BIT(TCCR1A,TCCR1A_WGM10);
            CLR_BIT(TCCR1A,TCCR1A_WGM11);
            SET_BIT(TCCR1B,TCCR1B_WGM12);
            CLR_BIT(TCCR1B,TCCR1B_WGM13);
            // TODO
            // TODO
        }
        else
        {
            returnValue = GPT_ERROR;
        }

        /*Compare Match Output Mode*/
        switch (config->output)
        {
        case GPT_OUTPUT_NORMAL:
            CLR_BIT(TCCR1A,TCCR1A_COM1A0);
            CLR_BIT(TCCR1A,TCCR1A_COM1A1);
            // TODO
            break;
        case GPT_OUTPUT_TOGGLE:
            SET_BIT(TCCR1A,TCCR1A_COM1A0);
            CLR_BIT(TCCR1A,TCCR1A_COM1A1);
            // TODO
            break;
        case GPT_OUTPUT_SET:
            SET_BIT(TCCR1A,TCCR1A_COM1A0);
            SET_BIT(TCCR1A,TCCR1A_COM1A1);
            // TODO
            break;
        case GPT_OUTPUT_CLEAR:
            CLR_BIT(TCCR1A,TCCR1A_COM1A0);
            SET_BIT(TCCR1A,TCCR1A_COM1A1);
            // TODO
            break;
        default:
            returnValue = GPT_ERROR;
            break;
        }

        /*Clock Select*/
        switch (config->prescaler)
        {
        case GPT_PRESCALER_0:
            CLR_BIT(TCCR1B,TCCR1B_CS10);
            CLR_BIT(TCCR1B,TCCR1B_CS11);
            CLR_BIT(TCCR1B,TCCR1B_CS12);
            // TODO
            break;
        case GPT_PRESCALER_1:
            SET_BIT(TCCR1B,TCCR1B_CS10);
            CLR_BIT(TCCR1B,TCCR1B_CS11);
            CLR_BIT(TCCR1B,TCCR1B_CS12);
            // TODO
            break;
        case GPT_PRESCALER_8:
            CLR_BIT(TCCR1B,TCCR1B_CS10);
            SET_BIT(TCCR1B,TCCR1B_CS11);
            CLR_BIT(TCCR1B,TCCR1B_CS12);
            // TODO
            break;
        case GPT_PRESCALER_64:
            SET_BIT(TCCR1B,TCCR1B_CS10);
            SET_BIT(TCCR1B,TCCR1B_CS11);
            CLR_BIT(TCCR1B,TCCR1B_CS12);
            // TODO
            break;
        case GPT_PRESCALER_256:
            CLR_BIT(TCCR1B,TCCR1B_CS10);
            CLR_BIT(TCCR1B,TCCR1B_CS11);
            SET_BIT(TCCR1B,TCCR1B_CS12);
            // TODO
            break;
        case GPT_PRESCALER_1024:
            SET_BIT(TCCR1B,TCCR1B_CS10);
            CLR_BIT(TCCR1B,TCCR1B_CS11);
            SET_BIT(TCCR1B,TCCR1B_CS12);
            // TODO
            break;
        case GPT_PRESCALER_EXT_FALLING:
            CLR_BIT(TCCR1B,TCCR1B_CS10);
            SET_BIT(TCCR1B,TCCR1B_CS11);
            SET_BIT(TCCR1B,TCCR1B_CS12);
            // TODO
            break;
        case GPT_PRESCALER_EXT_RISING:
            SET_BIT(TCCR1B,TCCR1B_CS10);
            SET_BIT(TCCR1B,TCCR1B_CS11);
            SET_BIT(TCCR1B,TCCR1B_CS12);
            // TODO
            break;
        default:
            returnValue = GPT_ERROR;
            break;
        }
        break;

    case GPT_CHANNEL_TIMER1B:
        /*Waveform Generation Mode*/
        if (config->mode == GPT_MODE_NORMAL)
        {
            CLR_BIT(TCCR1A,TCCR1A_WGM10);
            CLR_BIT(TCCR1A,TCCR1A_WGM11);
            CLR_BIT(TCCR1B,TCCR1B_WGM12);
            CLR_BIT(TCCR1B,TCCR1B_WGM13);
            // TODO
            // TODO
        }
        else if (config->mode == GPT_MODE_CTC)
        {
            CLR_BIT(TCCR1A,TCCR1A_WGM10);
            CLR_BIT(TCCR1A,TCCR1A_WGM11);
            SET_BIT(TCCR1B,TCCR1B_WGM12);
            CLR_BIT(TCCR1B,TCCR1B_WGM13);
            // TODO
            // TODO
        }
        else
        {
            returnValue = GPT_ERROR;
        }

        /*Compare Match Output Mode*/
        switch (config->output)
        {
        case GPT_OUTPUT_NORMAL:
            CLR_BIT(TCCR1A,TCCR1A_COM1B0);
            CLR_BIT(TCCR1A,TCCR1A_COM1B1);
            // TODO
            break;
        case GPT_OUTPUT_TOGGLE:
            SET_BIT(TCCR1A,TCCR1A_COM1B0);
            CLR_BIT(TCCR1A,TCCR1A_COM1B1);
            // TODO
            break;
        case GPT_OUTPUT_SET:
            SET_BIT(TCCR1A,TCCR1A_COM1B0);
            SET_BIT(TCCR1A,TCCR1A_COM1B1);
            // TODO
            break;
        case GPT_OUTPUT_CLEAR:
            CLR_BIT(TCCR1A,TCCR1A_COM1B0);
            SET_BIT(TCCR1A,TCCR1A_COM1B1);
            // TODO
            break;
        default:
            returnValue = GPT_ERROR;
            break;
        }

        /*Clock Select*/
        switch (config->prescaler)
        {
        case GPT_PRESCALER_0:
            CLR_BIT(TCCR1B,TCCR1B_CS10);
            CLR_BIT(TCCR1B,TCCR1B_CS11);
            CLR_BIT(TCCR1B,TCCR1B_CS12);
            // TODO
            break;
        case GPT_PRESCALER_1:
            SET_BIT(TCCR1B,TCCR1B_CS10);
            CLR_BIT(TCCR1B,TCCR1B_CS11);
            CLR_BIT(TCCR1B,TCCR1B_CS12);
            // TODO
            break;
        case GPT_PRESCALER_8:
            CLR_BIT(TCCR1B,TCCR1B_CS10);
            SET_BIT(TCCR1B,TCCR1B_CS11);
            CLR_BIT(TCCR1B,TCCR1B_CS12);
            // TODO
            break;
        case GPT_PRESCALER_64:
            SET_BIT(TCCR1B,TCCR1B_CS10);
            SET_BIT(TCCR1B,TCCR1B_CS11);
            CLR_BIT(TCCR1B,TCCR1B_CS12);
            // TODO
            break;
        case GPT_PRESCALER_256:
            CLR_BIT(TCCR1B,TCCR1B_CS10);
            CLR_BIT(TCCR1B,TCCR1B_CS11);
            SET_BIT(TCCR1B,TCCR1B_CS12);
            // TODO
            break;
        case GPT_PRESCALER_1024:
            SET_BIT(TCCR1B,TCCR1B_CS10);
            CLR_BIT(TCCR1B,TCCR1B_CS11);
            SET_BIT(TCCR1B,TCCR1B_CS12);
            // TODO
            break;
        case GPT_PRESCALER_EXT_FALLING:
            CLR_BIT(TCCR1B,TCCR1B_CS10);
            SET_BIT(TCCR1B,TCCR1B_CS11);
            SET_BIT(TCCR1B,TCCR1B_CS12);
            // TODO
            break;
        case GPT_PRESCALER_EXT_RISING:
            SET_BIT(TCCR1B,TCCR1B_CS10);
            SET_BIT(TCCR1B,TCCR1B_CS11);
            SET_BIT(TCCR1B,TCCR1B_CS12);
            // TODO
            break;
        default:
            returnValue = GPT_ERROR;
            break;
        }
        break;

    case GPT_CHANNEL_TIMER2:
        /*Waveform Generation Mode*/
        if (config->mode == GPT_MODE_NORMAL)
        {
            CLR_BIT(TCCR2,TCCR2_COM20);
            CLR_BIT(TCCR2,TCCR2_COM21);
            // TODO
            // TODO
        }
        else if (config->mode == GPT_MODE_CTC)
        {
            CLR_BIT(TCCR2,TCCR2_COM20);
            SET_BIT(TCCR2,TCCR2_COM21);
            // TODO
            // TODO
        }
        else
        {
            returnValue = GPT_ERROR;
        }

        /*Compare Match Output Mode*/
        switch (config->output)
        {
        case GPT_OUTPUT_NORMAL:
            CLR_BIT(TCCR2,TCCR2_COM20);
            CLR_BIT(TCCR2,TCCR2_COM21);
            // TODO
            break;
        case GPT_OUTPUT_TOGGLE:
            SET_BIT(TCCR2,TCCR2_COM20);
            CLR_BIT(TCCR2,TCCR2_COM21);
            // TODO
            break;
        case GPT_OUTPUT_SET:
            SET_BIT(TCCR2,TCCR2_COM20);
            SET_BIT(TCCR2,TCCR2_COM21);
            // TODO
            break;
        case GPT_OUTPUT_CLEAR:
            CLR_BIT(TCCR2,TCCR2_COM20);
            SET_BIT(TCCR2,TCCR2_COM21);
            // TODO
            break;
        default:
            returnValue = GPT_ERROR;
            break;
        }

        /*Clock Select*/
        switch (config->prescaler)
        {
        case GPT_PRESCALER_0:
            CLR_BIT(TCCR2,TCCR2_CS20);
            CLR_BIT(TCCR2,TCCR2_CS21);
            CLR_BIT(TCCR2,TCCR2_CS22);
            // TODO
            break;
        case GPT_PRESCALER_1:
            SET_BIT(TCCR2,TCCR2_CS20);
            CLR_BIT(TCCR2,TCCR2_CS21);
            CLR_BIT(TCCR2,TCCR2_CS22);
            // TODO
            break;
        case GPT_PRESCALER_8:
            CLR_BIT(TCCR2,TCCR2_CS20);
            SET_BIT(TCCR2,TCCR2_CS21);
            CLR_BIT(TCCR2,TCCR2_CS22);
            // TODO
            break;
        case GPT_PRESCALER_32:
            SET_BIT(TCCR2,TCCR2_CS20);
            SET_BIT(TCCR2,TCCR2_CS21);
            CLR_BIT(TCCR2,TCCR2_CS22);
            // TODO
            break;
        case GPT_PRESCALER_64:
            CLR_BIT(TCCR2,TCCR2_CS20);
            CLR_BIT(TCCR2,TCCR2_CS21);
            SET_BIT(TCCR2,TCCR2_CS22);
            // TODO
            break;
        case GPT_PRESCALER_128:
            SET_BIT(TCCR2,TCCR2_CS20);
            CLR_BIT(TCCR2,TCCR2_CS21);
            SET_BIT(TCCR2,TCCR2_CS22);
            // TODO
            break;
        case GPT_PRESCALER_256:
            CLR_BIT(TCCR2,TCCR2_CS20);
            SET_BIT(TCCR2,TCCR2_CS21);
            SET_BIT(TCCR2,TCCR2_CS22);
            // TODO
            break;
        case GPT_PRESCALER_1024:
            SET_BIT(TCCR2,TCCR2_CS20);
            SET_BIT(TCCR2,TCCR2_CS21);
            SET_BIT(TCCR2,TCCR2_CS22);
            // TODO
            break;
        default:
            returnValue = GPT_ERROR;
            break;
        }
        break;

    default:
        returnValue = GPT_ERROR;
    }
    return returnValue;
}

Gpt_ReturnType Gpt_StartTimer(Gpt_ChannelType channel, u16 value)
{
    Gpt_ReturnType returnValue = GPT_OK;
    switch (channel)
    {
    case GPT_CHANNEL_TIMER0:
        if (value < 256)
        {
            OCR0 = value;
        }
        else
        {
            returnValue = GPT_ERROR;
        }
        break;
    case GPT_CHANNEL_TIMER1A:
        if (value < 65536)
        {
            OCR1A = value;
        }
        else
        {
            returnValue = GPT_ERROR;
        }
        // TODO
        break;
    case GPT_CHANNEL_TIMER1B:
        if (value < 65536)
        {
            OCR1B = value;
        }
        else
        {
            returnValue = GPT_ERROR;
        }
        // TODO
        break;
    case GPT_CHANNEL_TIMER2:
        if (value < 256)
        {
            OCR2 = value;
        }
        else
        {
            returnValue = GPT_ERROR;
        }
        // TODO
        break;

    default:
        break;
    }
    return returnValue;
}

u16 Gpt_GetTimeElapsed(Gpt_ChannelType channel)
{
    u16 value = 0;
    switch (channel)
    {
    case GPT_CHANNEL_TIMER0:
        value = TCNT0;
        break;
    case GPT_CHANNEL_TIMER1A:
        value = TCNT1;
        // TODO
        break;
    case GPT_CHANNEL_TIMER1B:
        value = TCNT1;
        // TODO
        break;
    case GPT_CHANNEL_TIMER2:
        value = TCNT2;
        // TODO
        break;
    default:
        break;
    }
    return value;
}

u16 Gpt_GetTimeRemaining(Gpt_ChannelType channel, Gpt_ModeType mode)
{
    u16 value = 0;
    switch (channel)
    {
    case GPT_CHANNEL_TIMER0:
        if (mode == GPT_MODE_NORMAL)
        {
            value = 0xFF - TCNT0;
        }
        else if (mode == GPT_MODE_CTC)
        {
            value = OCR0 - TCNT0;
        }
        break;
    case GPT_CHANNEL_TIMER1A:
        if (mode == GPT_MODE_NORMAL)
        {
            value = 0xFFFF - TCNT1;
        }
        else if (mode == GPT_MODE_CTC)
        {
            value = OCR1A - TCNT1;
        }
        // TODO
        break;
    case GPT_CHANNEL_TIMER1B:
        if (mode == GPT_MODE_NORMAL)
        {
            value = 0xFFFF - TCNT1;
        }
        else if (mode == GPT_MODE_CTC)
        {
            value = OCR1B - TCNT1;
        }
        // TODO
        break;
    case GPT_CHANNEL_TIMER2:
        if (mode == GPT_MODE_NORMAL)
        {
            value = 0xFF - TCNT2;
        }
        else if (mode == GPT_MODE_CTC)
        {
            value = OCR2 - TCNT2;
        }
        // TODO
        break;
    default:
        break;
    }
    return value;
}

void Gpt_EnableNotification(Gpt_ChannelType channel, Gpt_ModeType mode, void (*callback)(void))
{
    switch (channel)
    {
    case GPT_CHANNEL_TIMER0:
        if (mode == GPT_MODE_NORMAL)
        {
            Gpt_Timer0_Callback_Normal = callback;
            SET_BIT(TIMSK, TIMSK_TOIE0);
        }
        else if (mode == GPT_MODE_CTC)
        {
            Gpt_Timer0_Callback_Ctc = callback;
            SET_BIT(TIMSK, TIMSK_OCIE0);
        }
        break;

    case GPT_CHANNEL_TIMER1A:
        if (mode == GPT_MODE_NORMAL)
        {
            Gpt_Timer1_Callback_Normal = callback;
            SET_BIT(TIMSK, TIMSK_TOIE1);
            // TODO
        }
        else if (mode == GPT_MODE_CTC)
        {
            Gpt_Timer1A_Callback_Ctc = callback;
            SET_BIT(TIMSK, TIMSK_OCIE1A);
            // TODO
        }
        break;

    case GPT_CHANNEL_TIMER1B:
        if (mode == GPT_MODE_NORMAL)
        {
            Gpt_Timer1_Callback_Normal = callback;
            SET_BIT(TIMSK, TIMSK_TOIE1);
            // TODO
        }
        else if (mode == GPT_MODE_CTC)
        {
            Gpt_Timer1B_Callback_Ctc = callback;
            SET_BIT(TIMSK, TIMSK_OCIE1B);
            // TODO
        }
        break;

    case GPT_CHANNEL_TIMER2:
        if (mode == GPT_MODE_NORMAL)
        {
            Gpt_Timer2_Callback_Normal = callback;
            SET_BIT(TIMSK, TIMSK_TOIE2);
            // TODO
        }
        else if (mode == GPT_MODE_CTC)
        {
            Gpt_Timer2_Callback_Ctc = callback;
            SET_BIT(TIMSK, TIMSK_OCIE2);
            // TODO
        }
        break;

    default:
        break;
    }
}

void Gpt_DisableNotification(Gpt_ChannelType channel, Gpt_ModeType mode)
{
    switch (channel)
    {
    case GPT_CHANNEL_TIMER0:
        if (mode == GPT_MODE_NORMAL)
        {
            CLR_BIT(TIMSK, TIMSK_TOIE0);
        }
        else if (mode == GPT_MODE_CTC)
        {
            CLR_BIT(TIMSK, TIMSK_OCIE0);
        }
        break;

    case GPT_CHANNEL_TIMER1A:
        if (mode == GPT_MODE_NORMAL)
        {
            CLR_BIT(TIMSK, TIMSK_TOIE1);
            // TODO
        }
        else if (mode == GPT_MODE_CTC)
        {
            CLR_BIT(TIMSK, TIMSK_OCIE1A);
            // TODO
        }
        break;

    case GPT_CHANNEL_TIMER1B:
        if (mode == GPT_MODE_NORMAL)
        {
            CLR_BIT(TIMSK, TIMSK_TOIE1);
            // TODO
        }
        else if (mode == GPT_MODE_CTC)
        {
            CLR_BIT(TIMSK, TIMSK_OCIE1B);
            // TODO
        }
        break;

    case GPT_CHANNEL_TIMER2:
        if (mode == GPT_MODE_NORMAL)
        {
            CLR_BIT(TIMSK, TIMSK_TOIE2);
            // TODO
        }
        else if (mode == GPT_MODE_CTC)
        {
            CLR_BIT(TIMSK, TIMSK_OCIE2);
            // TODO
        }
        break;

    default:
        break;
    }
}
