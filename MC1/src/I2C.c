#include "std_types.h"
#include "macros.h"

#include "Registers.h"
#include "I2C.h"
#include "I2C_cfg.h"

void I2C_InitMaster(void)
{
	/* Bit Rate: 400.000 kbps using zero pre-scaler TWPS=00 and F_CPU=8Mhz */
	TWBR = 0x02;
	TWSR = 0x00;

	TWCR = (1<<2); /* enable TWI */
}
void I2C_SendStartCondition(void)
{
	/*
	 * Clear the TWINT flag before sending the start bit TWINT=1
	 * send the start bit by TWSTA=1
	 * Enable TWI Module TWEN=1
	 */
	TWCR = (1 << 7) | (1 << 5) | (1 << 2);
	/* Wait for TWINT flag set in TWCR Register (start bit is send successfully) */
	while(GET_BIT(TWCR,7)==0);
}
void I2C_SendStopCondition(void)
{
	/*
	 * Clear the TWINT flag before sending the stop bit TWINT=1
	 * send the stop bit by TWSTO=1
	 * Enable TWI Module TWEN=1
	 * ----------------------------------------
	 *  Enable TWI Module TWEN=1 ---> //SET_BIT(TWCR,2);
		        Sent stop condition on the bus ---> //SET_BIT(TWCR,4);
		        Clear the interrupt flag To start the previous operation
		         //SET_BIT(TWCR,7);
	 */
	TWCR = (1 << 7) | (1 << 4) | (1 << 2);
}
void I2C_MasterWriteDataByte(u8 Data)
{
	/* Put data On TWI data Register */
	TWDR = Data;
	/*
	 * Clear the TWINT flag before sending the data TWINT=1
	 * Enable TWI Module TWEN=1
	 */
	TWCR = (1 << 7) | (1 << 2);
	/* Wait for TWINT flag set in TWCR Register(data is send successfully) */
	while(GET_BIT(TWCR,7)==0);
}
u8   I2C_MasterReadDataByteWith_ACK(void)
{
	/*
	 * Clear the TWINT flag before reading the data TWINT=1
	 * Enable sending ACK after reading or receiving data TWEA=1
	 * Enable TWI Module TWEN=1
	 * --------------------------------------------
	 *     Enable Acknowledge bit --> //SET_BIT(TWCR,6);
	 *     Clear the interrupt flag To start the previous operation --> //SET_BIT(TWCR,7);
	 *     Enable TWI Module TWEN=1 -->//SET_BIT(TWCR,2);
	 */
	TWCR = (1 << 7) | (1 << 2) | (1 << 6);

	/* Wait for TWINT flag set in TWCR Register (data received successfully) */
	while(GET_BIT(TWCR,7)==0);
	/* Read Data */
	return TWDR;
}
u8   I2C_MasterReadDataByteWith_NACK(void)
{
	/*
	 * Clear the TWINT flag before reading the data TWINT=1
	 * Enable TWI Module TWEN=1
	 * -------------------------------------------
	 * 	 * Disable Acknowledge bit --> //CLR_BIT(TWCR,6);
	 *     Clear the interrupt flag To start the previous operation --> //SET_BIT(TWCR,7);
	 *     Enable TWI Module TWEN=1 -->//SET_BIT(TWCR,2);
	 */
	TWCR = (1 << 7) | (1 << 2);
	/* Wait for TWINT flag set in TWCR Register (data received successfully) */
	while(GET_BIT(TWCR,7)==0);
	/* Read Data */
	return TWDR;
}

