/*! \file CAsservissement.h
    \brief Classe qui contient l'asservissement vitesse/position du robot
*/

#ifndef _ASSERVISSEMENT_H_
#define _ASSERVISSEMENT_H_

#include "CAsservissementBase.h"
#include "CAsservLogger.h"

// -----------------------------
//! Classe de gestion des options d'exécution passees en ligne de commande
class CAsservissement : public CAsservissementBase
{
public :
    //! Constructeur
    CAsservissement();

    //! Initilise tous les paramètres et valeurs
    /*virtual*/void Init(void);

    /*virtual*/ void CalculsMouvementsRobots(void);

    /*virtual*/void CommandeMouvementXY(float x, float y);
    /*virtual*/void CommandeMouvementDistanceAngle(float distance, float angle);
    /*virtual*/void CommandeMouvementXY_A(float x, float y);
    /*virtual*/void CommandeMouvementXY_B(float x, float y);
    /*virtual*/void CommandeMouvementXY_TETA(float x, float y, float teta);
    /*virtual*/void CommandeVitesseMouvement(float vit_avance, float vit_angle);

    //! Logger asservissement
    CAsservLogger m_data_logger;
    bool m_automatic_start_logger;
};


#endif


