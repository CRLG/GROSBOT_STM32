/*! \file CGlobale.cpp
    \brief Classe qui contient toute l'application
*/
#include "CGlobale.h"

//___________________________________________________________________________
/*!
   \brief Constructeur

   \param --
   \return --
*/
CGlobale::CGlobale()
    : m_led1(LED4_GPIO_Port, LED4_Pin),
      m_led2(LED5_GPIO_Port, LED5_Pin),
      m_led3(LED6_GPIO_Port, LED6_Pin),
      m_led4(LED7_GPIO_Port, LED7_Pin),
      m_leds(&m_led1, &m_led2, &m_led3, &m_led4)
{
    ModeFonctionnement = MODE_PILOTE_TERMINAL;
}

//___________________________________________________________________________
/*!
   \brief Destructeur

   \param --
   \return --
*/
CGlobale::~CGlobale() 
{

}

//___________________________________________________________________________
/*!
   \brief Point d'entrée pour l'execution de toute l'application

   \param --
   \return --
*/
void CGlobale::Run(void)
{
    // Attends la montée de toutes les alimentation et l'initialisation de l'écran
    // Temps nécessaire en pratique pour que l'écran tactile ai fini de démarrer
    // avant de commencer à  lui en envoyer des messages (et d'en recevoir)
    wait_ms(200);

    // Lecture des paramètres EEPROM
    readEEPROM();

    m_asservissement.cde_min = -100;
    m_asservissement.cde_max = 100;

    m_asservissement.Init();

    m_asservissement.vitesse_avance_max = 80;				//	[cm/s]
    m_asservissement.kp_distance = 1; //0.8;
    m_asservissement.ki_distance = 10; // 8;
    m_asservissement.kp_angle = 20;
    m_asservissement.ki_angle = 20;

    m_asservissement.seuil_conv_distance = 0.5;	// cm	Erreur en dessous de laquelle on considère que le robot est en position sur la distance
    m_asservissement. seuil_conv_angle =  0.018;	// rad	Erreur en dessous de laquelle on considère que le robot est en position sur l'angle

    m_asservissement.Ind_perfo = 0.5;


    m_electrobot.Init();
    // Carte PowerElectrobot
    m_power_electrobot.init(POWER_ELECTROBOT_I2C_ADDR);
 #ifdef UTILSATION_SERVOS_AX
    m_servos_ax.Init();
 #endif // UTILSATION_SERVOS_AX

    switch(ModeFonctionnement) {
    case MODE_AUTONOME : 			ModeAutonome();			break;
    case MODE_PILOTE_LABOTBOX : 	ModePiloteLaBotBox();	break;
    case MODE_PILOTE_TERMINAL : 	ModePiloteTerminal();	break;
    default : 						ModeAutonome();			break;
    }

    while(1) {
        // Ce code ne devrait jamais être atteint
    }
}


//___________________________________________________________________________
/*!
   \brief Lecture des paramètre de l'EEPROM

   \param --
   \return --
*/
void CGlobale::readEEPROM()
{
    unsigned long uldata;
    signed long ldata;
    float fdata;
    bool err;

    int status;

    if (m_eeprom.init()) {
        if (!m_eeprom.is_valid()) m_eeprom.format();  // C'est peut être la première fois (carte neuve, après un formatage de la flash)
    }

    if (m_eeprom.is_valid()) {
        if (m_eeprom.read_uint32(EEPROM_MAPPING::MODE_FONCTIONNEMENT, &uldata)) ModeFonctionnement = uldata;
        // Asservissement
        if (m_eeprom.read_uint32(EEPROM_MAPPING::CDE_MAX, &uldata))             m_asservissement.cde_max = uldata;
        if (m_eeprom.read_int32(EEPROM_MAPPING::CDE_MIN, &ldata))               m_asservissement.cde_min = ldata;
        if (m_eeprom.read_float(EEPROM_MAPPING::KP_DISTANCE, &fdata))           m_asservissement.kp_distance = fdata;
        if (m_eeprom.read_float(EEPROM_MAPPING::KI_DISTANCE, &fdata))           m_asservissement.ki_distance = fdata;
        if (m_eeprom.read_float(EEPROM_MAPPING::KP_ANGLE, &fdata))              m_asservissement.kp_angle = fdata;
        if (m_eeprom.read_float(EEPROM_MAPPING::KI_ANGLE, &fdata))              m_asservissement.ki_angle = fdata;
        if (m_eeprom.read_float(EEPROM_MAPPING::K_ANGLE, &fdata))               m_asservissement.k_angle = fdata;
        if (m_eeprom.read_float(EEPROM_MAPPING::SEUIL_CONV_DISTANCE, &fdata))   m_asservissement.seuil_conv_distance = fdata;
        if (m_eeprom.read_float(EEPROM_MAPPING::SEUIL_CONV_ANGLE, &fdata))      m_asservissement.seuil_conv_angle = fdata;
        if (m_eeprom.read_uint32(EEPROM_MAPPING::COMPTEUR_MAX, &uldata))        m_asservissement.compteur_max = uldata;
        if (m_eeprom.read_uint32(EEPROM_MAPPING::ZONE_MORTE_D, &uldata))        m_asservissement.zone_morte_D = uldata;
        if (m_eeprom.read_uint32(EEPROM_MAPPING::ZONE_MORTE_G, &uldata))        m_asservissement.zone_morte_G = uldata;
    }
}
