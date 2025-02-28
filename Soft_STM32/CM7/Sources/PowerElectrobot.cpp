#include "RessourcesHardware.h"
#include "PowerElectrobot.h"

PowerElectrobot::PowerElectrobot()
{
}

PowerElectrobot::~PowerElectrobot()
{
}

// ______________________________________________
void PowerElectrobot::writeI2C(unsigned char *buff, unsigned short size)
{
    HAL_I2C_Master_Transmit(&I2C_HDL_ELECTROBOT, m_address, (uint8_t*)buff, size, I2C_DEFAULT_TIMEOUT);
}

// ______________________________________________
void PowerElectrobot::readI2C(unsigned char *dest_buff, unsigned short size)
{
    HAL_I2C_Master_Receive(&I2C_HDL_ELECTROBOT, m_address, (uint8_t*)dest_buff, size, I2C_DEFAULT_TIMEOUT);
}
