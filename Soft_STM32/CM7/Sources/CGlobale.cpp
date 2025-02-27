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
    // Lecture des paramètres EEPROM
    readEEPROM();

    // Attends la montée de toutes les alimentation et l'initialisation de l'écran
    // Temps nécessaire en pratique pour que l'écran tactile ai fini de démarrer
    // avant de commencer à  lui en envoyer des messages (et d'en recevoir)
    //wait_ms(3000);

    //m_electrobot.Init();

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

}
