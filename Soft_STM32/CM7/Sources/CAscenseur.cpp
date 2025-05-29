#include "CAscenseur.h"
#include "CGlobale.h"
#include <stdio.h>

CAscenseur::CAscenseur()
{
}

// _________________________________________
void CAscenseur::command_motor(signed char consigne_pourcent)
{
    CdeMoteur(MOTEUR_ASCENSEUR, -consigne_pourcent);
}

// _________________________________________
bool CAscenseur::is_sensor_high()
{
    return Application.m_capteurs.getAscenseurButeeHaute();
}

// _________________________________________
bool CAscenseur::is_sensor_low()
{
    return Application.m_capteurs.getAscenseurButeeBasse();
}
