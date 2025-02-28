/*! \file CTrameLaBotBox.h
    \brief Classe qui contient la gestion d'une trame CAN
*/

#ifndef _TRAME_LABOTBOX_H_
#define _TRAME_LABOTBOX_H_

#define LABOTBOX_MAX_DATA_LEN (64)
typedef struct {
    unsigned short ID;                            //!< L'identifiant de la trame
    unsigned char DLC;                          //!< La longueur de la trame
    unsigned char Data[LABOTBOX_MAX_DATA_LEN];	//!< Les donnees utiles de la trame
}tStructTrameLaBotBox;

// -----------------------------
//! Classe de base pour les trames CAN
class CTrameLaBotBox {
public :
    static const short NO_PERIODIC = -1;  // Indique que la trame n'est pas périodique

    unsigned short m_ID;
    unsigned char m_DLC;

    //! Memorise le nombre de trame recues
    unsigned int m_nombre_recue;
    //! Memorise l'arrivee d'une nouvelle trame
    bool m_new_trame;

    CTrameLaBotBox();
    ~CTrameLaBotBox();

    virtual void Decode(tStructTrameLaBotBox *trameRecue);
    virtual tStructTrameLaBotBox* Encode(tStructTrameLaBotBox *trame);
    void initTrame(tStructTrameLaBotBox* trame);

    bool isNewTrame(void);
    bool isTimeToSend();
    void setTransmitPeriod(short period_msec);

protected:
    //! Période d'émission souhaitée [msec]
    short m_tx_periode;
    //! Instant de la dernière émission
    int m_last_time_tx;
};


#endif


