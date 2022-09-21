/*
 * SPI.h
 *
 *  Created on: ??�/??�/????
 *      Author: ascom
 */

#ifndef INC_SPI_H_
#define INC_SPI_H_

#include "std_types.h"

#define SPCR_SPE 6
#define SPCR_DORD 5
#define SPCR_MSTR 4
#define SPCR_SPR1 1
#define SPCR_SPR0 0

#define SPSR_SPIF 7
#define SPSR_SPI2x 0

void SPI_Init ();
void SPI_Send_Data(u8 data);
u8 SPI_Recieve_Data();

#endif /* INC_SPI_H_ */
