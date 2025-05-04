/*! \file CAsservissement.cpp
	\brief Classe qui contient toute l'application
*/

#include "CAsservissement.h"
#include "CGlobale.h"

// Constantes spécifiques au robot
const float CAsservissementBase::DISTANCE_PAR_PAS_CODEUR_G = 0.003189567f;  // (27/04/2025)
const float CAsservissementBase::DISTANCE_PAR_PAS_CODEUR_D = 0.003200126f;  // (27/04/2025)
const float CAsservissementBase::VOIE_ROBOT = 30.7;                         // (27/04/2025)

// Cartos spécifique au robo
const float CAsservissementBase::ini_conv_erreur_dist_vitesse_cur_x[NBRE_POINTS_CARTO_ERREUR] = {-40, -20, -10, -4, -2, -1, 0, 1, 2, 4, 10, 20, 40};							// [cm]
const float CAsservissementBase::ini_conv_erreur_dist_vitesse_1_cur[NBRE_POINTS_CARTO_ERREUR] = {-50, -35, -20, -8, -2, -1, 0, 1, 2, 8, 20, 35, 50};						// [cm/s] Carto perfo 0% environ 30cm/s2
const float CAsservissementBase::ini_conv_erreur_dist_vitesse_2_cur[NBRE_POINTS_CARTO_ERREUR] = {-130, -100, -50, -16, -4, -2, 0, 2, 4, 16, 50, 100, 130};

const float CAsservissementBase::ini_conv_erreur_angle_vitesse_cur_x[NBRE_POINTS_CARTO_ERREUR] = {-1.6, -0.8, -0.4, -0.2, -0.1, -0.05, 0, 0.05, 0.1, 0.2, 0.4, 0.8, 1.6};	// [rad]
const float CAsservissementBase::ini_conv_erreur_angle_vitesse_1_cur[NBRE_POINTS_CARTO_ERREUR] = {-4, -2.8, -2, -1.4, -1, -0.5, 0, 0.5, 1, 1.4, 2, 2.8, 4};					// [rad/s] Carto perfo 0% environ 5rad/s2
const float CAsservissementBase::ini_conv_erreur_angle_vitesse_2_cur[NBRE_POINTS_CARTO_ERREUR] = {-8, -5.65, -4, -2.82, -2, -0.5, 0, 0.5, 2, 2.82, 4, 5.65, 8};				// [rad/s] Carto perfo 100% environ 20rad/s2


//___________________________________________________________________________
 /*!
   \brief Constructeur

   \param --
   \return --
*/
CAsservissement::CAsservissement() 
{
    Init();
    m_automatic_start_logger = true;
}

//___________________________________________________________________________
 /*!
   \brief Initialisation

   \param --
   \return --
*/
void CAsservissement::Init(void)
{
 int i;
 
 CAsservissementBase::Init();

 te = 0.005f;
 // initialisation des paramètres de l'asservissement
 cde_max = 80;				// %	Commande maximum normalisée pour saturer la régulation
 cde_min = -80 ;			// %	Commande minimum normalisée pour saturer la régulation
 kp_distance = 0.8;		// 		Gain proportionnel pour la régulation en distance
 ki_distance = 4.0;		// 		Gain intégral pour la régulation en distance
 kp_angle =  5.0;			// 		Gain proportionnel pour la régulation en angle
 ki_angle =  10.0;			// 		Gain intégral pour la régulation en angle
 k_angle = 0.5;				//		Coeff de filtrage pour le terme dérivé
 seuil_conv_distance =  1;	// cm	Erreur en dessous de laquelle on considère que le robot est en position sur la distance
 seuil_conv_angle =  0.02;	// rad	Erreur en dessous de laquelle on considère que le robot est en position sur l'angle
 compteur_max = 3;			// 		Nombre de coups d'horloge (N*te) avant de confirmer que le robot est en position

 // Initialisation des zones mortes
 zone_morte_D = 4;
 zone_morte_G = 4;

 cde_offset_min_D = zone_morte_D;
 cde_offset_min_G = zone_morte_G;
 correction_ubatt = 1;
 //m_tension_batterie; // Externe
 ubatt_nominale=15.5;
 m_tension_batterie_filt = 1.44;
 m_tension_batterie_filt_prec = 14.4;
 k_batt = 0.9;							// Coeff de filtrage de la tension batterie (1 = pas de filtrage)
 k_filt_avance = 0.98;					// Coeff de filtrage de la vitesse d'avance (1 = pas de filtrage)
 k_filt_rotation = 0.98;					// Coeff de filtrage de la vitesse de rotation (1 = pas de filtrage)
 seuil_vitesse_diag_blocage = 2;		// cm/s
 commande_min_diag_blocage = 38;		// En cas de blocage l'égrateur charge rapidement à des valeurs importantes
 seuil_vitesse_diag_rotation = 0.1;	// rad/s
 seuil_max_compteur_diag_blocage = 500;	// k * te = g secondes
 inc_diag_blocage = 1;
 dec_diag_blocage = 2;

 vitesse_avance_max = 80;				//	[cm/s]
 vitesse_rotation_max = 3;				//	[rad/s]
 Ind_perfo = 0.4;

 // Initialisation des valeurs par défauts des tableaux
 for (i=0; i<NBRE_POINTS_CARTO_ERREUR; i++) {
	 conv_erreur_dist_vitesse_cur_x[i] = ini_conv_erreur_dist_vitesse_cur_x[i];
	 conv_erreur_dist_vitesse_1_cur[i] = ini_conv_erreur_dist_vitesse_1_cur[i];
	 conv_erreur_dist_vitesse_2_cur[i] = ini_conv_erreur_dist_vitesse_2_cur[i];
	 
	 conv_erreur_angle_vitesse_cur_x[i] = ini_conv_erreur_angle_vitesse_cur_x[i];
	 conv_erreur_angle_vitesse_1_cur[i] = ini_conv_erreur_angle_vitesse_1_cur[i];
	 conv_erreur_angle_vitesse_2_cur[i] = ini_conv_erreur_angle_vitesse_2_cur[i];
 }

 // Initialise les positions des codeurs
 Application.m_roues.resetCodeurs();
}


//___________________________________________________________________________
void CAsservissement::CalculsMouvementsRobots()
{
    CAsservissementBase::CalculsMouvementsRobots();   // là, c'est l'appel de l'asservissement génériques (commun Grosbot / Minibot)
    m_data_logger.step();  // log des data
}

//___________________________________________________________________________
void CAsservissement::CommandeMouvementXY(float x, float y)
{
   if (m_automatic_start_logger) m_data_logger.start();
   CAsservissementBase::CommandeMouvementXY(x, y);
}

//___________________________________________________________________________
void CAsservissement::CommandeMouvementDistanceAngle(float distance, float angle)
{
    if (m_automatic_start_logger) m_data_logger.start();
    CAsservissementBase::CommandeMouvementDistanceAngle(distance, angle);
}

//___________________________________________________________________________
void CAsservissement::CommandeMouvementXY_A(float x, float y)
{
    if (m_automatic_start_logger) m_data_logger.start();
    CAsservissementBase::CommandeMouvementXY_A(x, y);
}

//___________________________________________________________________________
void CAsservissement::CommandeMouvementXY_B(float x, float y)
{
    if (m_automatic_start_logger)  m_data_logger.start();
    CAsservissementBase::CommandeMouvementXY_B(x, y);
}

//___________________________________________________________________________
void CAsservissement::CommandeMouvementXY_TETA(float x, float y, float teta)
{
    if (m_automatic_start_logger) m_data_logger.start();
    CAsservissementBase::CommandeMouvementXY_TETA(x, y, teta);
}

//___________________________________________________________________________
void CAsservissement::CommandeVitesseMouvement(float vit_avance, float vit_angle)
{
    if (m_automatic_start_logger)  m_data_logger.start();
    CAsservissementBase::CommandeVitesseMouvement(vit_avance, vit_angle);
}
