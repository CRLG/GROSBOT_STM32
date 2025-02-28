/*! \file CMoteurs.h
	\brief Classe qui contient la gestion du pilotage des moteurs
*/

#ifndef _MOTEURS_H_
#define _MOTEURS_H_

// -----------------------------
//! Classe de gestion des options d'exécution passees en ligne de commande
class CMoteurs {

public :
    typedef enum {
      MOTEUR_1 = 1,
      MOTEUR_2,
      MOTEUR_3,
      MOTEUR_4,
      LAST_NUMERO_MOTEUR
    }T_MOTEUR;

    #define NBRE_MAX_MOTEURS    (LAST_NUMERO_MOTEUR-1)

	CMoteurs();
	~CMoteurs();

	void CommandeVitesse(unsigned char num_mot, float vitesse);

    //! Memorise la commande des moteurs
    float m_cde_mot_1;
    float m_cde_mot_2;
    float m_cde_mot_3;
    float m_cde_mot_4;
};

#endif


