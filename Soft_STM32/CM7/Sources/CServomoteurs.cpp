/*! \file CServomoteurs.cpp
    \brief Classe qui contient les méthodes pour le dialogue avec ANACONBOT
*/
#include "CServomoteurs.h"
#include "RessourcesHardware.h"

//___________________________________________________________________________
/*!
   \brief Constructeur

   \param --
   \return --
*/
CServomoteurs::CServomoteurs()
    : CServomoteursBase()
{
}

// ____________________________________________________________________
/*!
 * \brief Fixe le PPM en µsec du servo
 * \param numServo le numéro du servo
 * \param position_usec la consigne de position en [µsec]
 */
void CServomoteurs::CommandeServo(unsigned char numServo, unsigned short position_usec)
{
    CdeServo(numServo, position_usec);
}

