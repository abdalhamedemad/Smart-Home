/*
 * UART.c
 *
 *  Created on: ??�/??�/????
 *      Author: ascom
 */

#include "std_types.h"
#include "macros.h"
#include "Registers.h"
#include "int.h"
#include "UART.h"

#define UCSRC_UCPOL 0
#define UCSRC_UCSZ0 1
#define UCSRC_UCSZ1 2
#define UCSRC_USBS 3
#define UCSRC_UPM0 4
#define UCSRC_UPM1 5
#define UCSRC_UMSEL 6
#define UCSRC_URSEL 7

#define UCSRB_UCSZ2 2
#define UCSRB_TXEN 3
#define UCSRB_RXEN 4

#define UCSRA_TXC 6
#define UCSRA_RXC 7

void UART_Init (UART_ConfigType* config) {

    SET_BIT(UCSRC,UCSRC_URSEL);
    CLR_BIT(UCSRC,UCSRC_UMSEL);

    switch (config->parity)
    {
        case DISABLE_PRITY:
            CLR_BIT(UCSRC,UCSRC_UPM0);
            CLR_BIT(UCSRC,UCSRC_UPM1);
            break;
        case ENABLE_EVEN_PARITY:
            CLR_BIT(UCSRC,UCSRC_UPM0);
            SET_BIT(UCSRC,UCSRC_UPM1);
            break;
        case ENABLE_ODD_PARITY:
            SET_BIT(UCSRC,UCSRC_UPM0);
            SET_BIT(UCSRC,UCSRC_UPM1);
            break;
        default:
            break;
    }

    switch (config->stop_bit)
    {
        case ONE_STOP_BIT:
            CLR_BIT(UCSRC,UCSRC_USBS);
            break;
        case TWO_STOP_BIT:
            SET_BIT(UCSRC,UCSRC_USBS);
            break;
        default:
            break;
    }

    switch (config->char_size)
    {
        case CHARACTER_SIZE_5_BIT:
            CLR_BIT(UCSRC,UCSRC_UCSZ0);
            CLR_BIT(UCSRC,UCSRC_UCSZ1);
            CLR_BIT(UCSRB,UCSRB_UCSZ2);
            break;
        case CHARACTER_SIZE_6_BIT:
            SET_BIT(UCSRC,UCSRC_UCSZ0);
            CLR_BIT(UCSRC,UCSRC_UCSZ1);
            CLR_BIT(UCSRB,UCSRB_UCSZ2);
            break;
        case CHARACTER_SIZE_7_BIT:
            CLR_BIT(UCSRC,UCSRC_UCSZ0);
            SET_BIT(UCSRC,UCSRC_UCSZ1);
            CLR_BIT(UCSRB,UCSRB_UCSZ2);
            break;
        case CHARACTER_SIZE_8_BIT:
            SET_BIT(UCSRC,UCSRC_UCSZ0);
            SET_BIT(UCSRC,UCSRC_UCSZ1);
            CLR_BIT(UCSRB,UCSRB_UCSZ2);
            break;
        case CHARACTER_SIZE_9_BIT:
            SET_BIT(UCSRC,UCSRC_UCSZ0);
            SET_BIT(UCSRC,UCSRC_UCSZ1);
            SET_BIT(UCSRB,UCSRB_UCSZ2);
            break;
        default:
            break;
    }

    UBRRL=103;
    SET_BIT(UCSRB,UCSRB_RXEN);
    SET_BIT(UCSRB,UCSRB_TXEN);
}

void UART_Send_Data (u8 data) {
    UDR=data;
    while (GET_BIT(UCSRA,UCSRA_TXC) == 0);
}

u8 UART_Recieve_Data (void) {
    while (GET_BIT(UCSRA,UCSRA_RXC) == 0);
    return UDR;
}

