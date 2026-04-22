#ifndef _VL53L0X_MULTI_H_
#define _VL53L0X_MULTI_H_
#include "vl53l0x.h"
#include "vl53l0xMultiBase.h"

class VL53L0xMulti : public VL53L0xMultiBase
{
public :
    VL53L0xMulti(I2C_HandleTypeDef *i2c_hdl);

    #define VL53_COUNT 4
    VL53L0x m_vl53[VL53_COUNT];

    /*virtual*/uint8_t get_vl53_count();
    /*virtual*/VL53L0x *get_vl53(uint8_t index);
    /*virtual*/void set_reset_pin(uint8_t vl53_index, bool pin_state);
    /*virtual*/uint8_t get_i2c_address(uint8_t vl53_index);
};

#endif // _VL53L0X_MULTI_H_
