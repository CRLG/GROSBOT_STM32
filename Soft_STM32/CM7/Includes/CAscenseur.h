#ifndef _ASCENSEUR_H_
#define _ASCENSEUR_H_


// ====================================================
//
// ====================================================
class CAscenseur
{
public:
    CAscenseur();
    virtual ~CAscenseur();

    typedef enum {
        POSITION_UNKNOWN = 0,
        POSITION_HIGH,
        POSITION_LOW
    }tPositionAscenseur;


    typedef enum {
        TARGET_STOP,
        TARGET_UP,
        TARGET_DOWN
    }tTargetAscenseur;

    void up();
    void down();
    void set_position(unsigned char target);
    void stop();
    unsigned int get_position();
    void set_speeds(int speed_up, int speed_down);

    void periodicCall();

    unsigned char m_target;
    int m_speed_up;     // Vitesse en montée [%]
    int m_speed_down;   // Vitesse en descente [%]
};

#endif // _ASCENSEUR_H_
