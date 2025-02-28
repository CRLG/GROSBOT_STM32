/*! \file CRoues.cpp
	\brief Classe qui contient toute l'application
*/
#include "CMoteurs.h"
#include "RessourcesHardware.h"

//___________________________________________________________________________
 /*!
   \brief Constructeur

   \param --
   \return --
*/
CMoteurs::CMoteurs() 
{
}

//___________________________________________________________________________
 /*!
   \brief Destructeur

   \param --
   \return --
*/
CMoteurs::~CMoteurs() 
{
}



//___________________________________________________________________________
 /*!
   \brief Applique la puissance au moteur gauche

   \param vitesse la vitesse signee en pourcentage [-100%;+100]
   \return --
*/
void CMoteurs::CommandeVitesse(unsigned char num_mot, float vitesse)
{
  // Saturation de la commande
  if (vitesse > 100.0)          { vitesse  = 100.0; }
  else if (vitesse < -100.0)    { vitesse = -100.0; }

  switch(num_mot) {
    case MOTEUR_1 : 
      CdeMoteur(1, vitesse);
      m_cde_mot_1 = vitesse;    
    break;
    case MOTEUR_2 :
      CdeMoteur(2, vitesse);
      m_cde_mot_2 = vitesse;
    break;
    case MOTEUR_3 : 
      CdeMoteur(3, vitesse);
      m_cde_mot_3 = vitesse;
    break;
    case MOTEUR_4 : 
      CdeMoteur(4, vitesse);
      m_cde_mot_4 = vitesse;
    break;
    default : /* ne rien faire */ break;
  }
}
