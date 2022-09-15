#ifndef EEPROM_H_
#define EEPROM_H_

/*Initialize EEPROM*/
void EEPROM_Init(void);
/*Send byte to EEPROM*/
void EEPROM_Write_Byte(u8 AddressSlave ,u8 AddressLocation,u8 Data);
/*Read byte to EEPROM*/
u8 EEPROM_Read_Byte(u8 AddressSlave ,u8 AddressLocation);

#endif
