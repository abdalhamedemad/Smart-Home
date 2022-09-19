/*
 * main.c
 *
 *  Created on: ??�/??�/????
 *      Author: ascom
 */

#include <util/delay.h>
#include "macros.h"
#include "std_types.h"
#include "DIO.h"
#include "SSD.h"
#include "LCD.h"
#include "Keypad.h"
#include "ExtInterrupt.h"
#include "Adc.h"
#include "Gpt.h"
#include "GlobalInterrupt.h"
#include "Spt.h"
#include "UART.h"
#include "SPI_cfg.h"
#include "SPI.h"
#include "WDT.h"
#include "I2C.h"
#include "I2C_cfg.h"
#include "EEPROM.h"
#include "EEPROM_cfg.h"
#undef F_CPU
#define F_CPU 8000000

volatile u16 counter = 0;
u8 i = 0, k = 0, m = 0, n = 0, p = 0, q = 0;

void Timer_Clock();
void Recieve_UART_data();

void TimerHandler(void)
{
    counter++;
}

u16 result = 0;
void Adc_Handler(u16 res)
{
    result = res;
}
int arr[10];
void INT0_Handler(void)
{
    // DIO_SetPinLevel(DIO_PORTD, DIO_PIN7, DIO_HIGH);
    Recieve_UART_data();
}

int main(void)
{
    DIO_SetPinMode(DIO_PORTA, DIO_PIN1, DIO_OUTPUT);
    DIO_SetPinMode(DIO_PORTA, DIO_PIN2, DIO_OUTPUT);
    DIO_SetPinMode(DIO_PORTA, DIO_PIN3, DIO_OUTPUT);
    DIO_SetPinMode(DIO_PORTA, DIO_PIN4, DIO_OUTPUT);
    DIO_SetPinMode(DIO_PORTA, DIO_PIN5, DIO_OUTPUT);
    DIO_SetPinMode(DIO_PORTA, DIO_PIN6, DIO_OUTPUT);
    DIO_SetPinMode(DIO_PORTA, DIO_PIN0, DIO_INPUT_FLOATING);
    DIO_SetPinMode(DIO_PORTD, DIO_PIN7, DIO_OUTPUT); // OCR2
    // DIO_SetPinMode(DIO_PORTD,DIO_PIN0,DIO_INPUT_FLOATING);
    // DIO_SetPinMode(DIO_PORTD,DIO_PIN1,DIO_OUTPUT);
    // DIO_SetPinMode(DIO_PORTD, DIO_PIN7, DIO_OUTPUT);
    // DIO_SetPinMode(DIO_PORTD, DIO_PIN6, DIO_OUTPUT);
    DIO_SetPinMode(DIO_PORTD, DIO_PIN3, DIO_INPUT_FLOATING);
    Adc_Init();
    SSD_Init();
    /*********************************************************************/
    //    UART_ConfigType config1 = {ENABLE_EVEN_PARITY,ONE_STOP_BIT,CHARACTER_SIZE_8_BIT};
    //	UART_Init(&config1);
    UART_Init(Asynchronous, Odd_Parity, one_Stop_bit, _8_bit, _9600);
    /**************************************************************************************/
    Gpt_ConfigType config = {GPT_CHANNEL_TIMER0, GPT_MODE_CTC, GPT_OUTPUT_NORMAL, GPT_PRESCALER_1024};
    Gpt_Init(&config);
    /**********************************************************************/
    Spt_ConfigType config2 = {SPT_CHANNEL_TIMER2, SPT_MODE_FAST_PWM, SPT_OUTPUT_CLEAR, SPT_PRESCALER_1024};
    Spt_Init(&config2);
    u16 fast = 0;
    /********************************************************************/
    Gpt_StartTimer(GPT_CHANNEL_TIMER0, 250);
    Gpt_EnableNotification(GPT_CHANNEL_TIMER0, GPT_MODE_CTC, TimerHandler);
    Adc_SetCallback(Adc_Handler);
    ExtInterrupt_Init();
    ExtInterrupt_SetINT0Callback(INT0_Handler);
    GlobalInterrupt_Enable();
    while (1)
    {
        if (counter == 31)
        {
            counter = 0;
            i++;
        }
        Timer_Clock();
        Spt_StartTimer(SPT_CHANNEL_TIMER2, fast);
        u16 temperature = (result * (5000.0 / 1024)) / 10;
        if (temperature >= 40)
        {
            fast = 250;
        }
        else if ((temperature >= 30) && (temperature < 40))
        {
            fast = 160;
        }
        else if ((temperature >= 20) && (temperature < 30))
        {
            fast = 90;
        }
        else
        {
            fast = 0;
        }

        Adc_StartConversion(ADC_SINGLE_ADC0);
    }
}

void Timer_Clock()
{
    if (i == 10)
    {
        k++;
        i = 0;
    }
    if ((k == 6))
    {
        m++;
        k = 0;
    }
    if ((m == 10))
    {
        n++;
        m = 0;
    }
    if ((n == 6))
    {
        p++;
        n = 0;
    }
    if ((p == 10))
    {
        q++;
        p = 0;
    }
    if ((q == 2) && (p == 4))
    {
        i = 0;
        k = 0;
        m = 0;
        n = 0;
        p = 0;
        q = 0;
    }
    DIO_SetPinLevel(DIO_PORTA, DIO_PIN6, DIO_HIGH);
    SSD_Write(i);
    _delay_ms(1);
    DIO_SetPinLevel(DIO_PORTA, DIO_PIN6, DIO_LOW);
    DIO_SetPinLevel(DIO_PORTA, DIO_PIN5, DIO_HIGH);
    SSD_Write(k);
    _delay_ms(1);
    DIO_SetPinLevel(DIO_PORTA, DIO_PIN5, DIO_LOW);
    DIO_SetPinLevel(DIO_PORTA, DIO_PIN4, DIO_HIGH);
    SSD_Write(m);
    _delay_ms(1);
    DIO_SetPinLevel(DIO_PORTA, DIO_PIN4, DIO_LOW);
    DIO_SetPinLevel(DIO_PORTA, DIO_PIN3, DIO_HIGH);
    SSD_Write(n);
    _delay_ms(1);
    DIO_SetPinLevel(DIO_PORTA, DIO_PIN3, DIO_LOW);
    DIO_SetPinLevel(DIO_PORTA, DIO_PIN2, DIO_HIGH);
    SSD_Write(p);
    _delay_ms(1);
    DIO_SetPinLevel(DIO_PORTA, DIO_PIN2, DIO_LOW);
    DIO_SetPinLevel(DIO_PORTA, DIO_PIN1, DIO_HIGH);
    SSD_Write(q);
    _delay_ms(1);
    DIO_SetPinLevel(DIO_PORTA, DIO_PIN1, DIO_LOW);
}

void Recieve_UART_data()
{
    // q=5;
    u8 c = Recieve_Data();
    // DIO_SetPinLevel(DIO_PORTD,DIO_PIN7,DIO_LOW);
    if (c == 5)
    {
        DIO_SetPinLevel(DIO_PORTD, DIO_PIN7, DIO_LOW);
        c = Recieve_Data();
        if (c == 6)
        {
            // DIO_SetPinLevel(DIO_PORTD, DIO_PIN7, DIO_HIGH);
            q = 5;
        }
        u8 x = Recieve_Data();
        if (x == 22)
        {
            // DIO_SetPinLevel(DIO_PORTD, DIO_PIN6, DIO_HIGH);
        }
        q = x / 10;
        p = x % 10;
        x = Recieve_Data();
        n = x / 10;
        m = x % 10;
    }
    else if (c == 6)
    {
        // DIO_SetPinLevel(DIO_PORTD, DIO_PIN6, DIO_HIGH);
        for (i = 0; i < 10; i++)
        {
            arr[i] = Recieve_Data();
            _delay_ms(200);
        }
    }

    //	if(c == 'p')
    //	{
    //		//DIO_SetPinLevel(DIO_PORTD,DIO_PIN7,DIO_LOW);
    //		u8 i;
    //		for ( i = 0; i < 10; i++)
    //		{
    //			arr[i]=Recieve_Data();
    //		}
    //
    //	}else if(c == 6)
    //	{
    //		DIO_SetPinLevel(DIO_PORTD,DIO_PIN7,DIO_HIGH);
    //
    //		u8 x=Recieve_Data();
    //        q=x/10;
    //        p=x%10;
    //        x=Recieve_Data();
    //        n=x/10;
    //        m=x%10;
    //	}
}
