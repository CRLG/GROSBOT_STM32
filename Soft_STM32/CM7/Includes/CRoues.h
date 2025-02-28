/*! \file CRoues.h
        \brief Classe qui contient la gestion des roues motrices gauche et droite
*/

#ifndef _ROUES_H_
#define _ROUES_H_

#include "CRouesBase.h"

// -----------------------------
//! Classe de gestion des options d'exécution passees en ligne de commande
class CRoues : public CRouesBase
{
public :
    CRoues();

    /*virtual*/void AdapteCommandeMoteur_G(float vitesse);
    /*virtual*/void AdapteCommandeMoteur_D(float vitesse);
    /*virtual*/int getCodeurG(void);
    /*virtual*/int getCodeurD(void);
    /*virtual*/void resetCodeurs(void);
};


#endif


