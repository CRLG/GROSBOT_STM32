#include "CAscenseur.h"
#include "CGlobale.h"
#include <stdio.h>

CAscenseur::CAscenseur()
    : m_target(TARGET_STOP),
      m_speed_up(0),
      m_speed_down(0)
{
}
CAscenseur::~CAscenseur()
{
}

// _________________________________________
void CAscenseur::up()
{
    set_position(TARGET_UP);
}

// _________________________________________
void CAscenseur::down()
{
    set_position(TARGET_DOWN);
}

// _________________________________________
void CAscenseur::set_position(unsigned char target)
{
    m_target = target;
}

// _________________________________________
void CAscenseur::set_speeds(int speed_up, int speed_down)
{
    m_speed_up = speed_up;
    m_speed_down = speed_down;
}


// _________________________________________
void CAscenseur::stop()
{
    m_target = TARGET_STOP;
    CdeMoteur(MOTEUR_ASCENSEUR, 0);
}

// _________________________________________
unsigned int CAscenseur::get_position()
{
    if (Application.m_capteurs.getAscenseurButeeBasse() && !Application.m_capteurs.getAscenseurButeeHaute()) return POSITION_LOW;
    else if (Application.m_capteurs.getAscenseurButeeHaute() && !Application.m_capteurs.getAscenseurButeeBasse()) return POSITION_HIGH;
    else return POSITION_UNKNOWN;
}

// _________________________________________
// Fonctionnement de l'ascenseur :
//   -> On donne une consigne cible haut, bas ou arrêt (target)
// L'ascenseur maintien la consigne, même si par gravité l'ascenseur redescend et quitte la butée haute,
//  le moteur sera de nouveau piloté (pour rester en haut)
void CAscenseur::periodicCall()
{
    if ((Application.m_capteurs.getAscenseurButeeBasse()) && (m_target==TARGET_DOWN))       CdeMoteur(MOTEUR_ASCENSEUR, 0);
    else if ((Application.m_capteurs.getAscenseurButeeHaute()) && (m_target==TARGET_UP))    CdeMoteur(MOTEUR_ASCENSEUR, 0);
    else if (m_target==TARGET_DOWN)                                                         CdeMoteur(MOTEUR_ASCENSEUR, m_speed_down);
    else if (m_target==TARGET_UP)                                                           CdeMoteur(MOTEUR_ASCENSEUR, m_speed_up);
    else                                                                                    CdeMoteur(MOTEUR_ASCENSEUR, 0);
}
