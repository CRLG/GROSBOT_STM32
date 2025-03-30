#ifndef _SERVOMOTEURS_AX_H_
#define _SERVOMOTEURS_AX_H_

#include "servoaxbase.h"

class CServoMoteursAX : public ServoAXBase
{
public:
    CServoMoteursAX();
    ~CServoMoteursAX();

    const static unsigned int NBRE_SERVOS_AX = 253;

    // pure virtual methods to abstract hardware.
    // to be implemented on specific hardware.
    virtual tAxErr read(unsigned char *buff_data, unsigned char size);
    virtual tAxErr write(unsigned char *buff_data, unsigned char size);
    virtual tAxErr flushSerialInput();
    virtual tAxErr waitTransmitComplete();
    virtual tAxErr setTxEnable(bool state);
    virtual void delay_us(unsigned long delay);

    virtual tAxErr checkPresents(unsigned char max_id=NBRE_SERVOS_AX);

    tAxErr Init();

    // a appeler périodiquement pour la lecture des états servos
    tAxErr compute();

    int servo_id_to_index_present(unsigned char servo_id);

    int m_presents_list[NBRE_SERVOS_AX];    // list all AX detected when checkPresents() called
    int m_positions[NBRE_SERVOS_AX];
    int m_moving[NBRE_SERVOS_AX];
    unsigned char m_present_count;

private :
    tAxErr readEEPROM();
};

#endif // _SERVOMOTEURS_AX_H_
