#ifndef _POWER_ELECTROBOT_H_
#define _POWER_ELECTROBOT_H_

#include "dspicpowerelectrobotbase.h"


// ====================================================
//
// ====================================================
class PowerElectrobot : public dsPicPowerElectrobotBase
{
public:

    PowerElectrobot();
    virtual ~PowerElectrobot();

    // =============================================
    //    Reimplement MessengerInterfaceBase virual
    virtual void writeI2C(unsigned char *buff, unsigned short size);
    virtual void readI2C(unsigned char *dest_buff, unsigned short size);
};

#endif // _POWER_ELECTROBOT_H_
