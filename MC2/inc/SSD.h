

#ifndef INC_SSD_H_
#define INC_SSD_H_

#include "DIO.h"
#define SSD_COMM_CATHODE    0
#define COMM_ANODE      1

/*Configuration*/
#define SSD_PIN_A   DIO_PORTB,DIO_PIN6
#define SSD_PIN_B   DIO_PORTB,DIO_PIN5
#define SSD_PIN_C   DIO_PORTB,DIO_PIN4
#define SSD_PIN_D   DIO_PORTB,DIO_PIN7
#define SSD_PIN_E   DIO_PORTB,DIO_PIN2
#define SSD_PIN_F   DIO_PORTB,DIO_PIN1
#define SSD_PIN_G   DIO_PORTB,DIO_PIN0
#define SSD_TYPE    COMM_ANODE

typedef enum {
    SSD_NUMBER_0,
    SSD_NUMBER_1,
    SSD_NUMBER_2,
    SSD_NUMBER_3,
    SSD_NUMBER_4,
    SSD_NUMBER_5,
    SSD_NUMBER_6,
    SSD_NUMBER_7,
    SSD_NUMBER_8,
    SSD_NUMBER_9,
    SSD_OFF
} SSD_NumberType;

void SSD_Init(void);
void SSD_Write (SSD_NumberType number);


#endif /* INC_SSD_H_ */
