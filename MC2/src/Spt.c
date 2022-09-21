/*
 * Spt.c
 *
 *  Created on: ??�/??�/????
 *      Author: ascom
 */
#include "std_types.h"
#include "macros.h"
#include "Registers.h"
#include "int.h"
#include "Spt.h"

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

// /************ ISR Callbacks ************/
// void (*Spt_Timer0_Callback_Ctc)(void);
// void (*Spt_Timer0_Callback_Normal)(void);
// void (*Spt_Timer1A_Callback_Ctc)(void);
// void (*Spt_Timer1B_Callback_Ctc)(void);
// void (*Spt_Timer1_Callback_Normal)(void);
// void (*Spt_Timer2_Callback_Ctc)(void);
// void (*Spt_Timer2_Callback_Normal)(void);

// /************ ISR ************/
// ISR(VECTOR_TIMER0_CTC)
// {
//     Spt_Timer0_Callback_Ctc();
// }
// ISR(VECTOR_TIMER0_NORM)
// {
//     Spt_Timer0_Callback_Normal();
// }
// ISR(VECTOR_TIMER1_NORM)
// {
//     Spt_Timer1_Callback_Normal();
// }
// ISR(VECTOR_TIMER1A_CTC)
// {
//     Spt_Timer1A_Callback_Ctc();
// }
// ISR(VECTOR_TIMER1B_CTC)
// {
//     Spt_Timer1B_Callback_Ctc();
// }
// ISR(VECTOR_TIMER2_NORM)
// {
//     Spt_Timer2_Callback_Normal();
// }
// ISR(VECTOR_TIMER2_CTC)
// {
//     Spt_Timer2_Callback_Ctc();
// }

Spt_ReturnType Spt_Init(Spt_ConfigType *config)
{
    Spt_ReturnType returnValue = SPT_OK;

    switch (config->channel)
    {

    case SPT_CHANNEL_TIMER0:
        /*Waveform Generation Mode*/
        if (config->mode == SPT_MODE_FAST_PWM)
        {
            SET_BIT(TCCR0, TCCR0_WGM00);
            SET_BIT(TCCR0, TCCR0_WGM01);
        }
        else if (config->mode == SPT_MODE_PWM_PHASE_CORRECT)
        {
            SET_BIT(TCCR0, TCCR0_WGM00);
            CLR_BIT(TCCR0, TCCR0_WGM01);
        }
        else
        {
            returnValue = SPT_ERROR;
        }

        /*Compare Match Output Mode*/
        switch (config->output)
        {
        case SPT_OUTPUT_NORMAL:
            CLR_BIT(TCCR0, TCCR0_COM00);
            CLR_BIT(TCCR0, TCCR0_COM01);
            break;
        case SPT_OUTPUT_SET:
            SET_BIT(TCCR0, TCCR0_COM00);
            SET_BIT(TCCR0, TCCR0_COM01);
            // TODO
            break;
        case SPT_OUTPUT_CLEAR:
            CLR_BIT(TCCR0, TCCR0_COM00);
            SET_BIT(TCCR0, TCCR0_COM01);
            // TODO
            break;
        default:
            returnValue = SPT_ERROR;
            break;
        }

        /*Clock Select*/
        switch (config->prescaler)
        {
        case SPT_PRESCALER_0:
            CLR_BIT(TCCR0, TCCR0_CS00);
            CLR_BIT(TCCR0, TCCR0_CS01);
            CLR_BIT(TCCR0, TCCR0_CS02);
            break;
        case SPT_PRESCALER_1:
            SET_BIT(TCCR0, TCCR0_CS00);
            CLR_BIT(TCCR0, TCCR0_CS01);
            CLR_BIT(TCCR0, TCCR0_CS02);
            break;
        case SPT_PRESCALER_8:
            CLR_BIT(TCCR0, TCCR0_CS00);
            SET_BIT(TCCR0, TCCR0_CS01);
            CLR_BIT(TCCR0, TCCR0_CS02);
            break;
        case SPT_PRESCALER_64:
            SET_BIT(TCCR0, TCCR0_CS00);
            SET_BIT(TCCR0, TCCR0_CS01);
            CLR_BIT(TCCR0, TCCR0_CS02);
            // TODO
            break;
        case SPT_PRESCALER_256:
            CLR_BIT(TCCR0, TCCR0_CS00);
            CLR_BIT(TCCR0, TCCR0_CS01);
            SET_BIT(TCCR0, TCCR0_CS02);
            // TODO
            break;
        case SPT_PRESCALER_1024:
            SET_BIT(TCCR0, TCCR0_CS00);
            CLR_BIT(TCCR0, TCCR0_CS01);
            SET_BIT(TCCR0, TCCR0_CS02);
            break;
        case SPT_PRESCALER_EXT_FALLING:
            CLR_BIT(TCCR0, TCCR0_CS00);
            SET_BIT(TCCR0, TCCR0_CS01);
            SET_BIT(TCCR0, TCCR0_CS02);
            // TODO
            break;
        case SPT_PRESCALER_EXT_RISING:
            SET_BIT(TCCR0, TCCR0_CS00);
            SET_BIT(TCCR0, TCCR0_CS01);
            SET_BIT(TCCR0, TCCR0_CS02);
            // TODO
            break;
        default:
            returnValue = SPT_ERROR;
            break;
        }
        break;

    case SPT_CHANNEL_TIMER1A:
        /*Waveform Generation Mode*/
        if (config->mode == SPT_MODE_FAST_PWM)
        {
            CLR_BIT(TCCR1A,TCCR1A_WGM10);
            SET_BIT(TCCR1A,TCCR1A_WGM11);
            SET_BIT(TCCR1B,TCCR1B_WGM12);
            SET_BIT(TCCR1B,TCCR1B_WGM13);
            // TODO
            // TODO
        }
        // else if (config->mode == SPT_MODE_CTC)
        // {
        //     CLR_BIT(TCCR1A,TCCR1A_WGM10);
        //     CLR_BIT(TCCR1A,TCCR1A_WGM11);
        //     SET_BIT(TCCR1B,TCCR1B_WGM12);
        //     CLR_BIT(TCCR1B,TCCR1B_WGM13);
        //     // TODO
        //     // TODO
        // }
        else
        {
            returnValue = SPT_ERROR;
        }

        /*Compare Match Output Mode*/
        switch (config->output)
        {
        case SPT_OUTPUT_NORMAL:
            CLR_BIT(TCCR1A,TCCR1A_COM1A0);
            CLR_BIT(TCCR1A,TCCR1A_COM1A1);
            // TODO
            break;
        case SPT_OUTPUT_TOGGLE:
            SET_BIT(TCCR1A,TCCR1A_COM1A0);
            CLR_BIT(TCCR1A,TCCR1A_COM1A1);
            // TODO
            break;
        case SPT_OUTPUT_SET:
            SET_BIT(TCCR1A,TCCR1A_COM1A0);
            SET_BIT(TCCR1A,TCCR1A_COM1A1);
            // TODO
            break;
        case SPT_OUTPUT_CLEAR:
            CLR_BIT(TCCR1A,TCCR1A_COM1A0);
            SET_BIT(TCCR1A,TCCR1A_COM1A1);
            // TODO
            break;
        default:
            returnValue = SPT_ERROR;
            break;
        }

        /*Clock Select*/
        switch (config->prescaler)
        {
        case SPT_PRESCALER_0:
            CLR_BIT(TCCR1B,TCCR1B_CS10);
            CLR_BIT(TCCR1B,TCCR1B_CS11);
            CLR_BIT(TCCR1B,TCCR1B_CS12);
            // TODO
            break;
        case SPT_PRESCALER_1:
            SET_BIT(TCCR1B,TCCR1B_CS10);
            CLR_BIT(TCCR1B,TCCR1B_CS11);
            CLR_BIT(TCCR1B,TCCR1B_CS12);
            // TODO
            break;
        case SPT_PRESCALER_8:
            CLR_BIT(TCCR1B,TCCR1B_CS10);
            SET_BIT(TCCR1B,TCCR1B_CS11);
            CLR_BIT(TCCR1B,TCCR1B_CS12);
            // TODO
            break;
        case SPT_PRESCALER_64:
            SET_BIT(TCCR1B,TCCR1B_CS10);
            SET_BIT(TCCR1B,TCCR1B_CS11);
            CLR_BIT(TCCR1B,TCCR1B_CS12);
            // TODO
            break;
        case SPT_PRESCALER_256:
            CLR_BIT(TCCR1B,TCCR1B_CS10);
            CLR_BIT(TCCR1B,TCCR1B_CS11);
            SET_BIT(TCCR1B,TCCR1B_CS12);
            // TODO
            break;
        case SPT_PRESCALER_1024:
            SET_BIT(TCCR1B,TCCR1B_CS10);
            CLR_BIT(TCCR1B,TCCR1B_CS11);
            SET_BIT(TCCR1B,TCCR1B_CS12);
            // TODO
            break;
        case SPT_PRESCALER_EXT_FALLING:
            CLR_BIT(TCCR1B,TCCR1B_CS10);
            SET_BIT(TCCR1B,TCCR1B_CS11);
            SET_BIT(TCCR1B,TCCR1B_CS12);
            // TODO
            break;
        case SPT_PRESCALER_EXT_RISING:
            SET_BIT(TCCR1B,TCCR1B_CS10);
            SET_BIT(TCCR1B,TCCR1B_CS11);
            SET_BIT(TCCR1B,TCCR1B_CS12);
            // TODO
            break;
        default:
            returnValue = SPT_ERROR;
            break;
        }
        break;

        case SPT_CHANNEL_TIMER1B:
        /*Waveform Generation Mode*/
        if (config->mode == SPT_MODE_FAST_PWM)
        {
            CLR_BIT(TCCR1A,TCCR1A_WGM10);
            SET_BIT(TCCR1A,TCCR1A_WGM11);
            SET_BIT(TCCR1B,TCCR1B_WGM12);
            SET_BIT(TCCR1B,TCCR1B_WGM13);
            // TODO
            // TODO
        }
        //     else if (config->mode == GPT_MODE_CTC)
        //     {
        //         CLR_BIT(TCCR1A,TCCR1A_WGM10);
        //         CLR_BIT(TCCR1A,TCCR1A_WGM11);
        //         SET_BIT(TCCR1B,TCCR1B_WGM12);
        //         CLR_BIT(TCCR1B,TCCR1B_WGM13);
        //         // TODO
        //         // TODO
        //     }
        else
        {
            returnValue = SPT_ERROR;
        }

        /*Compare Match Output Mode*/
        switch (config->output)
        {
        case SPT_OUTPUT_NORMAL:
            CLR_BIT(TCCR1A,TCCR1A_COM1B0);
            CLR_BIT(TCCR1A,TCCR1A_COM1B1);
            // TODO
            break;
        case SPT_OUTPUT_TOGGLE:
            SET_BIT(TCCR1A,TCCR1A_COM1B0);
            CLR_BIT(TCCR1A,TCCR1A_COM1B1);
            // TODO
            break;
        case SPT_OUTPUT_SET:
            SET_BIT(TCCR1A,TCCR1A_COM1B0);
            SET_BIT(TCCR1A,TCCR1A_COM1B1);
            // TODO
            break;
        case SPT_OUTPUT_CLEAR:
            CLR_BIT(TCCR1A,TCCR1A_COM1B0);
            SET_BIT(TCCR1A,TCCR1A_COM1B1);
            // TODO
            break;
        default:
            returnValue = SPT_ERROR;
            break;
        }

        /*Clock Select*/
        switch (config->prescaler)
        {
        case SPT_PRESCALER_0:
            CLR_BIT(TCCR1B,TCCR1B_CS10);
            CLR_BIT(TCCR1B,TCCR1B_CS11);
            CLR_BIT(TCCR1B,TCCR1B_CS12);
            // TODO
            break;
        case SPT_PRESCALER_1:
            SET_BIT(TCCR1B,TCCR1B_CS10);
            CLR_BIT(TCCR1B,TCCR1B_CS11);
            CLR_BIT(TCCR1B,TCCR1B_CS12);
            // TODO
            break;
        case SPT_PRESCALER_8:
            CLR_BIT(TCCR1B,TCCR1B_CS10);
            SET_BIT(TCCR1B,TCCR1B_CS11);
            CLR_BIT(TCCR1B,TCCR1B_CS12);
            // TODO
            break;
        case SPT_PRESCALER_64:
            SET_BIT(TCCR1B,TCCR1B_CS10);
            SET_BIT(TCCR1B,TCCR1B_CS11);
            CLR_BIT(TCCR1B,TCCR1B_CS12);
            // TODO
            break;
        case SPT_PRESCALER_256:
            CLR_BIT(TCCR1B,TCCR1B_CS10);
            CLR_BIT(TCCR1B,TCCR1B_CS11);
            SET_BIT(TCCR1B,TCCR1B_CS12);
            // TODO
            break;
        case SPT_PRESCALER_1024:
            SET_BIT(TCCR1B,TCCR1B_CS10);
            CLR_BIT(TCCR1B,TCCR1B_CS11);
            SET_BIT(TCCR1B,TCCR1B_CS12);
            // TODO
            break;
        case SPT_PRESCALER_EXT_FALLING:
            CLR_BIT(TCCR1B,TCCR1B_CS10);
            SET_BIT(TCCR1B,TCCR1B_CS11);
            SET_BIT(TCCR1B,TCCR1B_CS12);
            // TODO
            break;
        case SPT_PRESCALER_EXT_RISING:
            SET_BIT(TCCR1B,TCCR1B_CS10);
            SET_BIT(TCCR1B,TCCR1B_CS11);
            SET_BIT(TCCR1B,TCCR1B_CS12);
            // TODO
            break;
        default:
            returnValue = SPT_ERROR;
            break;
        }
        break;

         case SPT_CHANNEL_TIMER2:
		 /*Waveform Generation Mode*/
		 if (config->mode == SPT_MODE_FAST_PWM)
		 {
			 SET_BIT(TCCR2,TCCR2_WGM20);
			 SET_BIT(TCCR2,TCCR2_WGM21);
			 // TODO
			 // TODO
		 }
//		 else if (config->mode == GPT_MODE_CTC)
//		 {
//			 CLR_BIT(TCCR2,TCCR2_COM20);
//			 SET_BIT(TCCR2,TCCR2_COM21);
//			 // TODO
//			 // TODO
//		 }
		 else
		 {
			 returnValue = SPT_ERROR;
		 }

		 /*Compare Match Output Mode*/
		 switch (config->output)
		 {
		 case SPT_OUTPUT_NORMAL:
			 CLR_BIT(TCCR2,TCCR2_COM20);
			 CLR_BIT(TCCR2,TCCR2_COM21);
			 // TODO
			 break;
		 case SPT_OUTPUT_TOGGLE:
			 SET_BIT(TCCR2,TCCR2_COM20);
			 CLR_BIT(TCCR2,TCCR2_COM21);
			 // TODO
			 break;
		 case SPT_OUTPUT_SET:
			 SET_BIT(TCCR2,TCCR2_COM20);
			 SET_BIT(TCCR2,TCCR2_COM21);
			 // TODO
			 break;
		 case SPT_OUTPUT_CLEAR:
			 CLR_BIT(TCCR2,TCCR2_COM20);
			 SET_BIT(TCCR2,TCCR2_COM21);
			 // TODO
			 break;
		 default:
			 returnValue = SPT_ERROR;
			 break;
		 }

		 /*Clock Select*/
		 switch (config->prescaler)
		 {
		 case SPT_PRESCALER_0:
			 CLR_BIT(TCCR2,TCCR2_CS20);
			 CLR_BIT(TCCR2,TCCR2_CS21);
			 CLR_BIT(TCCR2,TCCR2_CS22);
			 // TODO
			 break;
		 case SPT_PRESCALER_1:
			 SET_BIT(TCCR2,TCCR2_CS20);
			 CLR_BIT(TCCR2,TCCR2_CS21);
			 CLR_BIT(TCCR2,TCCR2_CS22);
			 // TODO
			 break;
		 case SPT_PRESCALER_8:
			 CLR_BIT(TCCR2,TCCR2_CS20);
			 SET_BIT(TCCR2,TCCR2_CS21);
			 CLR_BIT(TCCR2,TCCR2_CS22);
			 // TODO
			 break;
		 case SPT_PRESCALER_32:
			 SET_BIT(TCCR2,TCCR2_CS20);
			 SET_BIT(TCCR2,TCCR2_CS21);
			 CLR_BIT(TCCR2,TCCR2_CS22);
			 // TODO
			 break;
		 case SPT_PRESCALER_64:
			 CLR_BIT(TCCR2,TCCR2_CS20);
			 CLR_BIT(TCCR2,TCCR2_CS21);
			 SET_BIT(TCCR2,TCCR2_CS22);
			 // TODO
			 break;
		 case SPT_PRESCALER_128:
			 SET_BIT(TCCR2,TCCR2_CS20);
			 CLR_BIT(TCCR2,TCCR2_CS21);
			 SET_BIT(TCCR2,TCCR2_CS22);
			 // TODO
			 break;
		 case SPT_PRESCALER_256:
			 CLR_BIT(TCCR2,TCCR2_CS20);
			 SET_BIT(TCCR2,TCCR2_CS21);
			 SET_BIT(TCCR2,TCCR2_CS22);
			 // TODO
			 break;
		 case SPT_PRESCALER_1024:
			 SET_BIT(TCCR2,TCCR2_CS20);
			 SET_BIT(TCCR2,TCCR2_CS21);
			 SET_BIT(TCCR2,TCCR2_CS22);
			 // TODO
			 break;
		 default:
			 returnValue = SPT_ERROR;
			 break;
		 }
		 break;

        default:
            returnValue = SPT_ERROR;
        }
        return returnValue;
}

void Spt_Set_ICR1(u16 value) {
    ICR1 = value;
}

u16 Get_OCR_Value (u8 angle) {
    return ((angle*1000)/180)+1000;
}

Spt_ReturnType Spt_StartTimer(Spt_ChannelType channel, u16 value)
{
    Spt_ReturnType returnValue = SPT_OK;
    switch (channel)
    {
    case SPT_CHANNEL_TIMER0:
        if (value < 256)
        {
            OCR0 = value;
        }
        else
        {
            returnValue = SPT_ERROR;
        }
        break;
    case SPT_CHANNEL_TIMER1A:
        if (value < 65536)
        {
            OCR1A = value;
        }
        else
        {
            returnValue = SPT_ERROR;
        }
        // TODO
        break;
    case SPT_CHANNEL_TIMER1B:
        if (value < 65536)
        {
            OCR1B = value;
        }
        else
        {
            returnValue = SPT_ERROR;
        }
        // TODO
        break;
    case SPT_CHANNEL_TIMER2:
		if (value < 256)
		{
			OCR2 = value;
		}
		else
		{
			returnValue = SPT_ERROR;
		}
		break;

    default:
        break;
    }
    return returnValue;
}
