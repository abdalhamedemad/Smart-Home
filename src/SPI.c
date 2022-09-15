/*
 * SPI.c
 *
 *  Created on: ??�/??�/????
 *      Author: ascom
 */

#include "std_types.h"
#include "macros.h"
#include "Registers.h"
#include "SPI.h"
#include "SPI_cfg.h"
#include "DIO.h"


void SPI_Init () {

    #if (DATA_ORDER == LSB)
    SET_BIT(SPCR,SPCR_DORD);
    #elif (DATA_ORDER == MSB)
    CLR_BIT(SPCR,SPCR_DORD);
    #endif

    #if (SPI_MODE == MASTER)
    SET_BIT(SPCR,SPCR_MSTR);
    SET_BIT(SPCR,SPCR_SPR0);
    SET_BIT(SPCR,SPCR_SPR1);
    CLR_BIT(SPSR,SPSR_SPI2x);
    DIO_SetPinMode(DIO_PORTB,DIO_PIN5,DIO_OUTPUT);
    DIO_SetPinMode(DIO_PORTB,DIO_PIN4,DIO_OUTPUT);
    DIO_SetPinMode(DIO_PORTB,DIO_PIN7,DIO_OUTPUT);
    DIO_SetPinMode(DIO_PORTB,DIO_PIN6,DIO_INPUT_FLOATING);
    #elif (SPI_MODE == SLAVE)
    CLR_BIT(SPCR,SPCR_MSTR);
    DIO_SetPinMode(DIO_PORTB,DIO_PIN5,DIO_INPUT_FLOATING);
    DIO_SetPinMode(DIO_PORTB,DIO_PIN4,DIO_INPUT_FLOATING);
    DIO_SetPinMode(DIO_PORTB,DIO_PIN7,DIO_INPUT_FLOATING);
    DIO_SetPinMode(DIO_PORTB,DIO_PIN6,DIO_OUTPUT);
    #endif

    SET_BIT(SPCR,SPCR_SPE);
}
void SPI_Send_Data(u8 data) {
    SPDR = data;
    while (GET_BIT(SPSR,SPSR_SPIF) == 0);
}
u8 SPI_Recieve_Data() {
    while (GET_BIT(SPSR,SPSR_SPIF) == 0);
    return SPDR;
}

