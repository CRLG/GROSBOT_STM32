/*! \file ConfigSpecifiqueCoupe.h
	\brief Déclare
*/
#ifndef _CONFIG_SPECIFIQUE_COUPE 
#define _CONFIG_SPECIFIQUE_COUPE

// Directives pour la compilation conditionnelle
// Permet d'activer ou desactiver une fonctionnalite d'une annee sur l'autre ou d'un robot a l'autre
//#define UTILSATION_SERVOS_AX
//#define UTILISATION_KMAR
//#define UTILISATION_CHARIOT
//#define UTILISATION_XBEE
//#define UTILISATION_ASSERV_LOGGER
// Le choix du type de télémètre (UTILISATION_TELEMETRES_US_SRF08 ou UTILISATION_TELEMETRES_VL53),
//      c'est l'un ou l'autre par compilation conditionnelle (!! MAIS PAS LES 2 !!)
//#define UTILISATION_TELEMETRES_US_SRF08
#define UTILISATION_TELEMETRES_VL53

// Permet de configurer l'utilisation du LIDAR :
// Plusieurs possibilités pour compatibilité :
//      NO_LIDAR : N'utilise pas les données du LIDAR (ni Lidar connecté en direct sur le CPU, ni en provenance de la RPI)
//      LIDAR_EXTERNE : Les infos du LIDAR proviennent de l'exterieur via un message Labotbox
//      LIDAR_INTERNE : Le LIDAR est connecté directement au CPU (YDLIDAR)
#define NO_LIDAR        (0)
#define LIDAR_EXTERNE   (1)
#define LIDAR_INTERNE   (2)
#define UTILISATION_LIDAR (LIDAR_INTERNE)

#if UTILISATION_LIDAR == LIDAR_INTERNE
    #define UTILISATION_YDLIDAR     // active le YDLIDAR si c'est le LIDAR interne qui est choisi
#endif


// Couleur de l'équipe
#define EQUIPE_BLEU     SM_DatasInterface::EQUIPE_COULEUR_2
#define EQUIPE_JAUNE    SM_DatasInterface::EQUIPE_COULEUR_1
#define PI 3.14159265358979f

// Filtre de confirmation avant de lever le flag obstacleDetecte (pour rentrer en strategie d'evitement d'obstacle)
// La valeur du define correspond a un nombre de passage dans la boucle dans laquelle est calculee l'info
#define FILTRE_CONFIRMATION_OBSTACLE_DETECTE (3)
// Affectation des numéros de stratégie
typedef enum {
    STRATEGIE_PAR_DEFAUT= 0,
    STRATEGIE_HOMOLO1,
    STRATEGIE_HOMOLO2,
    STRATEGIE_01,
    STRATEGIE_02,
    STRATEGIE_03,
    STRATEGIE_04,
    STRATEGIE_05,
    STRATEGIE_06,
    // _____________________
    STRATEGIE_TEST_01 = 30,
    STRATEGIE_TEST_02,
    STRATEGIE_TEST_03,
    STRATEGIE_TEST_04,
    STRATEGIE_TEST_05,
    STRATEGIE_TEST_06,
    STRATEGIE_TEST_07
}eATTRIBUTION_STRATEGIES;

// Affectation des sorties moteurs
typedef enum {
   MOTEUR_ROUE_GAUCHE = 1,
   MOTEUR_ROUE_DROITE,
   MOTEUR_ASCENSEUR,
   MOTEUR_NON_DEFINI_2,
}eATTRIBUTION_MOTEURS;

// Affectation des codeurs de position
// ATTENTION : obsolète
typedef enum {

}eATTRIBUTION_CODEURS;

//! cet enumere contient les numeros d'attribution des servos
typedef enum {
    SERVO_NON_ATTRIBUE          = 1,
    SERVO_BRAS_THERMO_GAUCHE    = 2,
    SERVO_PINCE_GAUCHE          = 3,
    SERVO_NON_ATTRIBUE_2     	= 4,
    SERVO_BRAS_THERMO_DROIT     = 5,
    SERVO_NON_ATTRIBUE_3        = 6,
    SERVO_PINCE_DROIT           = 7
} eATTRIBUTION_SERVOS;

//!  cet énuméré contient les positions de références des servos
typedef enum {
    // SERVO BRAS THERMOMETRE GAUCHE
    SERVO_BRAS_THERMO_GAUCHE_RANGE     	= 735,
    SERVO_BRAS_THERMO_GAUCHE_SORTI      = 1645,
    // SERVO_PINCE_GAUCHE
    SERVO_PINCE_GAUCHE_SORTI            = 900,
    SERVO_PINCE_GAUCHE_SAISIR           = 900,
    SERVO_PINCE_GAUCHE_RENTRE       	= 2020,
    // SERVO BRAS THERMOMETRE DROIT
    SERVO_BRAS_THERMO_DROIT_RANGE     	= 2440,
    SERVO_BRAS_THERMO_DROIT_SORTI       = 1570,
	 // SERVO_PINCE_DROIT
    SERVO_PINCE_DROIT_SORTI             = 2130,
    SERVO_PINCE_DROIT_SAISIR            = 2130,
    SERVO_PINCE_DROIT_RENTRE            = 830,
}eVALUES_SERVOS;

//! cet enumere contient les numeros d'attribution des servos SD20
typedef enum {

} eATTRIBUTION_SERVOS_SD20;

typedef enum {

}eVALUES_SERVOS_SD20;

//! cet enumere contient les numeros d'attribution des servos AX (ID)
typedef enum {
    SERVO_AX_KMAR_AXIS_1 = 1,
    SERVO_AX_KMAR_AXIS_2 = 2,
    SERVO_AX_KMAR_AXIS_3 = 3,
    SERVO_AX_KMAR_AXIS_4 = 4,
    SERVO_AX_TOUS = 0xFE
} eATTRIBUTION_SERVOS_AX;

//! cet enumere contient les numeros d'attribution des servos AX
typedef enum {
} eVALUES_SERVOS_AX;

//code des demandes CPU vers LABOTBOX (trame générique)
typedef enum {
    DMDE_DEFAULT = 0,
    DMDE_DISTANCE_BALISE = 1,
    DMDE_VIDEO_NORD_SUD = 2,
    DMDE_VIDEO_CODE_COULEUR = 3
}eVALUES_DMDE_GEN;

//code des commandes/traitements LABOTBOX vers CPU (trame générique)
typedef enum {
    CMDE_DEFAULT = 0,
    CMDE_DISTANCE_BALISE = 1, // c'est un traitement: reco des balises aruco et distance par rapport au robot
    CMDE_VIDEO_NORD_SUD = 2, // SPECIFIQUE 2020/2021 - c'est un traitement: reco du nord-sud
    CMDE_VIDEO_CODE_COULEUR = 3 // SPECIFIQUE 2020/2021 - c'est un traitement : reco d'une série de couleur (pour les gobelets)
}eVALUES_CMDE_GEN;

typedef enum {
    MOUVEMENT_INIT = 0, // (CKmar::NO_MOUVEMENT + 1),
    MOUVEMENT_APPRENTISSAGE_CHARIOT,
    MOUVEMENT_PRISE_STATUETTE,
    MOUVEMENT_POSER_STATUETTE_SUR_VITRINE,
    MOUVEMENT_PRENDRE_ECHANTILLON_AU_SOL,
    MOUVEMENT_DEPOSER_ECHANTILLON_SUR_GALERIE,
    MOUVEMENT_RANGER_STATUETTE_DANS_ROBOT,
    MOUVEMENT_LEVER_STATUETTE_AVANT_DEPLACEMENT
}eKMAR_MOUVEMENTS;

// Spécifique à une coupe donnée
// Enuméré du message Labotbox ACTION_ROBOT (champ "command")
typedef enum {
    TOUS_ACTIONNEURS_AU_REPOS = 0,
    ACTIONNEURS_POSITION_INIT,

    ASCENSEUR_MONTE,
    ASCENSEUR_DESCEND,
    ASCENSEUR_STOP,

    PINCE_ARG_FERMEE,
    PINCE_ARG_OUVERTE,
    PINCE_ARG_INTERMEDIAIRE,
    PINCE_ARD_FERMEE,
    PINCE_ARD_OUVERTE,
    PINCE_ARD_INTERMEDIAIRE,

    VERRIN_HAUT,
    VERRIN_BAS,
    VERRIN_INTERMEDIAIRE,

    PINCE_PLANCHE_OUVERT,
    PINCE_PLANCHE_FERMEE,
    PINCE_PLANCHE_INTERMEDIAIRE,

    BANDEROLE_RANGEE,
    BANDEROLE_DEPLOYEE,
    BANDEROLE_HORIZONTALE,

    CAN_MOVER_INT_ON,
    CAN_MOVER_INT_OFF,
    CAN_MOVER_EXT_ON,
    CAN_MOVER_EXT_OFF,

}eCOMMANDE_ETAT_ROBOT;


typedef enum {
    SORTIE_ALIMENTATION_LIDAR             = 7,  // (index 7 -> sortie physique n°8)
}eATTRIBUTION_POWER_ELECTROBOT;

// Affectation des numéros de télémètres SRF08 et ANA
#define INDEX_TELEMETRE_AVG 0
#define INDEX_TELEMETRE_AVD 2
#define INDEX_TELEMETRE_ARG 3
#define INDEX_TELEMETRE_ARD 1
#define INDEX_TELEMETRE_ARGCentre 4
#define INDEX_TELEMETRE_ARDCentre 5

//Seuil de détection des capteurs US et du Lidar
#define SEUIL_DETECTION_US  30
#define SEUIL_DETECTION_LIDAR 50


//! Période d'appel du modèle
#define PERIODE_APPEL_MODELIA 0.02f // [sec]

//! Durée du match
#define DUREE_MATCH 100 // [sec]

// Consignes "tout doux" pour l'asserviseement
// utilisé dans la stratégie d'évitement et propre au robot
// TODO : peut être qu'il serait mieux de faire une méthode
// dans la classe Asservissement getCdeMinToutDoux() et getCdeMaxToutDoux()
// à ré-implémenter pour chaque robot en fonction de moteurs
#define CDE_MIN_TOUT_DOUX (-10)
#define CDE_MAX_TOUT_DOUX (10)

// Position d'init du robot dans le repère absolue terrain
#define X_ROBOT_TERRAIN_INIT_COULEUR_1        (42.0f)
#define Y_ROBOT_TERRAIN_INIT_COULEUR_1        (165.0f)
#define ANGLE_ROBOT_TERRAIN_INIT_COULEUR_1    (-PI/2.0f)

#define X_ROBOT_TERRAIN_INIT_COULEUR_2        (258.0f)
#define Y_ROBOT_TERRAIN_INIT_COULEUR_2        (165.0f)
#define ANGLE_ROBOT_TERRAIN_INIT_COULEUR_2    (PI/2.0f)

// Coordonnées dans le repère absolue terrain
// à partir desquelles il faut interdire la détection d'obstacle
// pour éviter les fausses détections hors du terrain
// Valeurs en [cm]
#define X_MAX_INTERDIT_DETECTION    (280)
#define X_MIN_INTERDIT_DETECTION    (20)
#define Y_MIN_INTERDIT_DETECTION    (10)
#define Y_MAX_INTERDIT_DETECTION    (190)


#define SEUIL_TENSION_BATTERIE_CRITIQUE (10.5)

// Pour la gestion du bandeau de LED
#define INDEX_LED_ANGLE_0 (14)
#define INDEX_FIRST_LED_BANDEAU (3)
#define INDEX_LAST_LED_BANDEAU  (49)
#define INDEX_LED_BANDEAU_OBSTACLE_AVG  (6)
#define INDEX_LED_BANDEAU_OBSTACLE_AV   (14)
#define INDEX_LED_BANDEAU_OBSTACLE_AVD  (20)
#define INDEX_LED_BANDEAU_OBSTACLE_ARD  (32)
#define INDEX_LED_BANDEAU_OBSTACLE_AR   (38)
#define INDEX_LED_BANDEAU_OBSTACLE_ARG  (43)


#define HOMOLO 1

#endif // _CONFIG_SPECIFIQUE_COUPE


