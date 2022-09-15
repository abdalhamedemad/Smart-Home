/*
 * UART.h
 *
 *  Created on: ??�/??�/????
 *      Author: ascom
 */

#ifndef INC_UART_H_
#define INC_UART_H_
#include "std_types.h"

typedef enum {
    DISABLE_PRITY,
    ENABLE_EVEN_PARITY,
    ENABLE_ODD_PARITY
}Parity_Mode_Type;

typedef enum {
    ONE_STOP_BIT,
    TWO_STOP_BIT
}Stop_Bit_Select;

typedef enum {
    CHARACTER_SIZE_5_BIT,
    CHARACTER_SIZE_6_BIT,
    CHARACTER_SIZE_7_BIT,
    CHARACTER_SIZE_8_BIT,
    CHARACTER_SIZE_9_BIT
}Character_Size_Type;

typedef struct {
    Parity_Mode_Type parity;
    Stop_Bit_Select stop_bit;
    Character_Size_Type char_size;
}UART_ConfigType;



void UART_Init (UART_ConfigType* config);
void UART_Send_Data (u8 data);
u8 UART_Recieve_Data (void);

#endif /* INC_UART_H_ */
