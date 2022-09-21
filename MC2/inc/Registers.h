/*
 * Registers.h
 *
 *  Created on: Sep 1, 2022
 *      Author: ahmad
 */

#ifndef INC_REGISTERS_H_
#define INC_REGISTERS_H_


/************ DIO ************/
#define PORTA	                *((volatile u8*)0x3B)
#define DDRA	                *((volatile u8*)0x3A)
#define PINA	                *((volatile u8*)0x39)
#define PORTB	                *((volatile u8*)0x38)
#define DDRB	                *((volatile u8*)0x37)
#define PINB	                *((volatile u8*)0x36)
#define PORTC	                *((volatile u8*)0x35)
#define DDRC	                *((volatile u8*)0x34)
#define PINC	                *((volatile u8*)0x33)
#define PORTD	                *((volatile u8*)0x32)
#define DDRD	                *((volatile u8*)0x31)
#define PIND	                *((volatile u8*)0x30)

/************ External Interrupt ************/
#define MCUCR                   *((volatile u8*)0x55)
#define MCUCSR                  *((volatile u8*)0x54)
#define GICR                    *((volatile u8*)0x5B)
#define GIFR                    *((volatile u8*)0x5A)

/************ Global Interrupt ************/
#define SREG                    *((volatile u8*)0x5F)

/************ ADC ************/
#define ADMUX                   *((volatile u8*)0x27)
#define ADCSRA                  *((volatile u8*)0x26)
#define ADC_DATA_REGISTER       *((volatile u16*)0x24)
#define ADCL                    *((volatile u8*)0x24)
#define ADCH                    *((volatile u8*)0x25)
#define SFIOR                   *((volatile u8*)0x50)

/************ TIMER 0 ************/
#define TCCR0                   *((volatile u8*)0x53)
#define TCNT0                   *((volatile u8*)0x52)
#define OCR0                    *((volatile u8*)0x5C)
#define TIMSK                   *((volatile u8*)0x59)
#define TIFR                    *((volatile u8*)0x58)

/************ TIMER 1 ************/
#define TCCR1A                  *((volatile u8*)0x4F)
#define TCCR1B                  *((volatile u8*)0x4E)
#define OCR1A                   *((volatile u16*)0x4A)
#define OCR1B                   *((volatile u16*)0x48)
#define TCNT1                   *((volatile u16*)0x4C)
#define ICR1                    *((volatile u16*)0x46)

/************ TIMER 2 ************/
#define TCCR2                   *((volatile u8*)0x45)
#define OCR2                    *((volatile u8*)0x43)
#define TCNT2                   *((volatile u8*)0x44)

/************ UART ************/
#define UDR                     *((volatile u8*)0x2C)
#define UCSRA                   *((volatile u8*)0x2B)
#define UCSRB                   *((volatile u8*)0x2A)
#define UBRRL                   *((volatile u8*)0x29)
#define UCSRC                   *((volatile u8*)0x40)

/************ SPI ************/
#define SPCR                    *((volatile u8*)0x2D)
#define SPDR                    *((volatile u8*)0x2F)
#define SPSR                    *((volatile u8*)0x2E)

/************ I2C ************/
#define TWBR     *((volatile u8*)0x20)
#define TWCR     *((volatile u8*)0x56)
#define TWSR     *((volatile u8*)0x21)
#define TWDR     *((volatile u8*)0x23)
#define TWAR     *((volatile u8*)0x22)

/************ Timer WDT ************/
#define WDTCR                   *((volatile u8*)0x41)

#endif /* INC_REGISTERS_H_ */
