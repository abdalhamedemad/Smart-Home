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

u8* Prayer =" ";
volatile u16 counter = 0;
u8 i = 0, k = 0, m = 0, n = 0, p = 0, q = 0;
volatile u8 counter2;
volatile u16 counter3=0;
volatile u8 Counterflag=0;
volatile u8 Counterflag2=0;
void Timer_Clock();
void Recieve_UART_data();

void Print_ON_LCD();

void TimerHandler(void)
{
    counter++;
    counter2++;
    counter3++;
}

u16 result = 0;
void Adc_Handler(u16 res)
{
    result = res;
}
int arr[10]; ////////////////////////// [0]-> fhh  [1]->fMM
void INT0_Handler(void)
{
    Recieve_UART_data();
}

int main(void)
{   /************************************************/
    DIO_SetPinMode(DIO_PORTC,DIO_PIN0,DIO_OUTPUT);
    DIO_SetPinMode(DIO_PORTC,DIO_PIN1,DIO_OUTPUT);
    /************************************************/
    DIO_SetPinMode(DIO_PORTA, DIO_PIN1, DIO_OUTPUT);
    DIO_SetPinMode(DIO_PORTA, DIO_PIN2, DIO_OUTPUT);
    DIO_SetPinMode(DIO_PORTA, DIO_PIN3, DIO_OUTPUT);
    DIO_SetPinMode(DIO_PORTA, DIO_PIN4, DIO_OUTPUT);
    DIO_SetPinMode(DIO_PORTA, DIO_PIN5, DIO_OUTPUT);
    DIO_SetPinMode(DIO_PORTA, DIO_PIN6, DIO_OUTPUT);
    DIO_SetPinMode(DIO_PORTA, DIO_PIN0, DIO_INPUT_FLOATING);
    DIO_SetPinMode(DIO_PORTD, DIO_PIN7, DIO_OUTPUT); // OCR2
    DIO_SetPinMode(DIO_PORTD, DIO_PIN3, DIO_INPUT_FLOATING);
    Adc_Init();
    SSD_Init();
    LCD_Init();
    /*********************************************************************/
    UART_Init(Asynchronous, Odd_Parity, one_Stop_bit, _8_bit, _9600);
    /**************************************************************************************/
    //_delay_ms(800);
    Gpt_ConfigType config = {GPT_CHANNEL_TIMER0, GPT_MODE_CTC, GPT_OUTPUT_NORMAL, GPT_PRESCALER_1024};
    Gpt_Init(&config);
    /**********************************************************************/
    Spt_ConfigType config2 = {SPT_CHANNEL_TIMER2, SPT_MODE_FAST_PWM, SPT_OUTPUT_CLEAR, SPT_PRESCALER_1024};
    Spt_Init(&config2);
    u16 fast = 0;
    /********************************************************************/
    u8 flag_print=0;
    Gpt_StartTimer(GPT_CHANNEL_TIMER0, 250);
    Gpt_EnableNotification(GPT_CHANNEL_TIMER0, GPT_MODE_CTC, TimerHandler);
    Adc_SetCallback(Adc_Handler);
    ExtInterrupt_Init();
    ExtInterrupt_SetINT0Callback(INT0_Handler);
    GlobalInterrupt_Enable();
    
    while (1) {
        if (arr[0]==0 && arr[1]==0 && arr[2]==0 & arr[3]==0) {
            continue;
        }
        else {
            i=0;
            k=0;
            break;
        } 
    }

    while (1)
    {
        /************************************/
        if(p==6 && Counterflag == 0 )
        {
            Counterflag=1;
            counter2=0;
        }
        if(Counterflag == 1)
        {
            DIO_SetPinLevel(DIO_PORTC,DIO_PIN0,DIO_HIGH);
            DIO_SetPinLevel(DIO_PORTC,DIO_PIN1,DIO_LOW);
            if(counter2 == 62)
            {
            DIO_SetPinLevel(DIO_PORTC,DIO_PIN0,DIO_LOW);
            DIO_SetPinLevel(DIO_PORTC,DIO_PIN1,DIO_LOW);
            Counterflag=2;
            Counterflag2=0;
            }
        }

        if(p==7 && q==1 && Counterflag2==0 )
        {
            Counterflag2=1;
            counter2=0;
        }
        if(Counterflag2==1)
        {
            DIO_SetPinLevel(DIO_PORTC,DIO_PIN1,DIO_HIGH);
            DIO_SetPinLevel(DIO_PORTC,DIO_PIN0,DIO_LOW);
            if(counter2 == 62)
            {
            DIO_SetPinLevel(DIO_PORTC,DIO_PIN0,DIO_LOW);
            DIO_SetPinLevel(DIO_PORTC,DIO_PIN1,DIO_LOW);
            Counterflag2=2;
            Counterflag=0;
            }
        }

        
        /************************************/
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

        if ((flag_print==1)) {
            if (counter3 >= 1860) {
                LCD_Clear();
                flag_print=0;
                counter3=0;
                continue;
            }
			Print_ON_LCD();
        }

        Adc_StartConversion(ADC_SINGLE_ADC0);
        if ((i==0) && (k==0) && (!flag_print) && (m == arr[1] % 10) && (n == arr[1]/10) && (p == arr[0]%10) && (q == arr[0]/10))
		{
            Prayer="Fajr";
            flag_print=1;
            counter3=0;
		}
		else if ((m == arr[3] % 10) && (n == arr[3]/10) && (p == arr[2]%10) && (q == arr[2]/10) && (k==0) && (i==0) && (!flag_print))
		{
			Prayer="Duhr";
            flag_print=1;
            counter3=0;
		}
		else if ((m == arr[5] % 10) && (n == arr[5]/10) && (p == arr[4]%10) && (q == arr[4]/10) && (k==0) && (i==0) && (!flag_print))
		{
			Prayer="Asr";
            flag_print=1;
            counter3=0;
		}
		else if ((m == arr[7] % 10) && (n == arr[7]/10) && (p == arr[6]%10) && (q == arr[6]/10) && (k==0) && (i==0) && (!flag_print))
		{
			Prayer="Maghrib";
            flag_print=1;
            counter3=0;
		}
		else if ((m == arr[9] % 10) && (n == arr[9]/10) && (p == arr[8]%10) && (q == arr[8]/10) && (k==0) && (i==0) && (!flag_print))
		{
			Prayer="Isha";
            flag_print=1;
            counter3=0;
		}
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
    u8 c = Recieve_Data();
    if (c == 5)
    {
        DIO_SetPinLevel(DIO_PORTD, DIO_PIN7, DIO_LOW);
        c = Recieve_Data();
        u8 x = Recieve_Data();
        q = x / 10;
        p = x % 10;
        x = Recieve_Data();
        n = x / 10;
        m = x % 10;
    }
    else if (c == 6)
    {
        for (i = 0; i < 10; i++)
        {
            arr[i] = Recieve_Data();
            _delay_ms(200);
        }
    }
}

void Print_ON_LCD() {
    if (Prayer != " ") {
    LCD_DisplayString(Prayer);
    }
    Prayer=" ";
}
