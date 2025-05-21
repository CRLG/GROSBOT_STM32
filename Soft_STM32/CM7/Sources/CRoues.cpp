/*! \file CRoues.cpp
    \brief Implémentationd la classe CRoues pour CPU
*/
#include "RessourcesHardware.h"
#include "CGlobale.h"

//___________________________________________________________________________
/*!
   \brief Constructeur

   \param --
   \return --
*/
CRoues::CRoues() 
{
    resetCodeurs();
}

//___________________________________________________________________________
/*!
   \brief Applique la puissance au moteur gauche

   \param vitesse la vitesse signee en pourcentage [-100%;+100]
   \return --
*/
void CRoues::AdapteCommandeMoteur_G(float vitesse)
{
    Application.m_moteurs.CommandeVitesse(CMoteurs::MOTEUR_1, vitesse);
    m_cde_roue_G = vitesse;
}


//___________________________________________________________________________
/*!
   \brief Applique la puissance au moteur droit

   \param vitesse la vitesse signee en pourcentage [-100%;+100]
   \return --
*/
void CRoues::AdapteCommandeMoteur_D(float vitesse)
{
    Application.m_moteurs.CommandeVitesse(CMoteurs::MOTEUR_2, vitesse);
    m_cde_roue_D = vitesse;
}

//___________________________________________________________________________
/*!
   \brief Renvoie la position du codeur G

   \param --
   \return la position du codeur
*/
int CRoues::getCodeurG(void)
{
    return(Application.m_codeurs.m_CumulCodeurPosition1);
}


//___________________________________________________________________________
/*!
   \brief Renvoie la position du codeur D

   \param --
   \return la position du codeur
*/
int CRoues::getCodeurD(void)
{
    return(Application.m_codeurs.m_CumulCodeurPosition2);
}


//___________________________________________________________________________
/*!
   \brief Reset les pas cumules par les 2 ccodeurs G et D

   \param --
   \return --
*/
void CRoues::resetCodeurs(void)
{
    Application.m_codeurs.reset(CCodeurs::CODEUR_1);
    Application.m_codeurs.reset(CCodeurs::CODEUR_2);
}
