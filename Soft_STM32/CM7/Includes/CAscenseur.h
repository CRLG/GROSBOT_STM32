#ifndef _ASCENSEUR_H_
#define _ASCENSEUR_H_

#include "CAscenseurBase.h"

// ====================================================
//
// ====================================================
class CAscenseur : public CAscenseurBase
{
public:
    CAscenseur();

    // Méthodes vituelles pures à réimplémenter dans l'applicatif
    /*virtual*/ void command_motor(signed char consigne_pourcent);  // consigne_pource positif pour le sens monter / négatif pour le sens descente
    /*virtual*/ bool is_sensor_high();  // capteur de butée haute
    /*virtual*/ bool is_sensor_low();   // capteur de butée basse

};

#endif // _ASCENSEUR_H_
