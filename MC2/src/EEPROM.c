#include "std_types.h"
#include "macros.h"
#include "Registers.h"
#include "I2C.h"
#include "EEPROM.h"
#include "EEPROM_cfg.h"

void EEPROM_Init(void)
{
	I2C_InitMaster();
}

/*Send byte to EEPROM*/
void EEPROM_Write_Byte(u8 AddressSlave ,u8 AddressLocation,u8 Data)
{
	I2C_SendStartCondition();
	//write the device address and so we need to get A2 A1 A0 address bits and R/W=0 (write)
	I2C_MasterWriteDataByte(AddressSlave);

	//send the required location address
	I2C_MasterWriteDataByte(AddressLocation);

	//write byte to eeprom
	I2C_MasterWriteDataByte(Data);

	I2C_SendStopCondition();
}

u8 EEPROM_Read_Byte(u8 AddressSlave ,u8 AddressLocation)
{

	I2C_SendStartCondition();

	//write the device address and so we need to get A2 A1 A0 address bits and R/W=0 (write)
	I2C_MasterWriteDataByte(AddressSlave);

	//send the required location address
	I2C_MasterWriteDataByte(AddressLocation);

	//send a repeated start
	I2C_SendStartCondition();

	//write the device address and so we need to get A2 A1 A0 address bits and R/W=1 (Read)
	SET_BIT(AddressSlave,0);
	I2C_MasterWriteDataByte(AddressSlave);

	return I2C_MasterReadDataByteWith_NACK();

	I2C_SendStopCondition();
}
