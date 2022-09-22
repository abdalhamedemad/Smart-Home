#ifndef I2C_H_
#define I2C_H_

void I2C_InitMaster(void);
void I2C_SendStartCondition(void);
void I2C_SendStopCondition(void);
void I2C_MasterWriteDataByte(u8 Data);
u8   I2C_MasterReadDataByteWith_ACK(void);           //read with send Ack
u8   I2C_MasterReadDataByteWith_NACK(void);          //read without send Ack


#endif
