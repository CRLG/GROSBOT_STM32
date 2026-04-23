#include "vl53l0xMulti.h"
#include "main.h"
// _____________________________________________
VL53L0xMulti::VL53L0xMulti(I2C_HandleTypeDef *i2c_hdl)
    : VL53L0xMultiBase(i2c_hdl)
{
}

// _____________________________________________
uint8_t VL53L0xMulti::get_vl53_count()
{
    return VL53_COUNT;
}

// _____________________________________________
VL53L0x * VL53L0xMulti::get_vl53(uint8_t index)
{
    if (index >= VL53_COUNT) return &m_vl53[0];
    return &m_vl53[index];
}

// _____________________________________________
void VL53L0xMulti::set_reset_pin(uint8_t vl53_index, bool pin_state)
{
    switch(vl53_index) {
    case 0:
        HAL_GPIO_WritePin(SPI_CS1_GPIO_Port, SPI_CS1_Pin, (GPIO_PinState)pin_state);
        break;
    case 1:
        HAL_GPIO_WritePin(SPI_SCK_GPIO_Port, SPI_SCK_Pin, (GPIO_PinState)pin_state);
        break;
    case 2:
        HAL_GPIO_WritePin(SPI_MOSI_GPIO_Port, SPI_MOSI_Pin, (GPIO_PinState)pin_state);
        break;
    case 3:
        HAL_GPIO_WritePin(SPI_MISO_GPIO_Port, SPI_MISO_Pin, (GPIO_PinState)pin_state);
        break;
    default:
        break;
    }
}

// _____________________________________________
uint8_t VL53L0xMulti::get_i2c_address(uint8_t vl53_index)
{
    if (vl53_index >= VL53_COUNT) return 0;

    const uint8_t addr[VL53_COUNT] = { 0x46, 0x48, 0x50, 0x52};
    return addr[vl53_index];
}



