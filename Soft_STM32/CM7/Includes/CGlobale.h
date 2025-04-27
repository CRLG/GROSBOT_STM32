/*! \file CGlobale.h
        \brief Classe qui contient toute l'application
*/
#ifndef _GLOBALE_H_
#define _GLOBALE_H_

#include "RessourcesHardware.h"
#include "CLeds.h"
#include "CLed.h"
#include "CTelemetres.h"
#include "CDetectionObstaclesBase.h"
#include "CCodeurs.h"
#include "CElectrobot.h"
#include "CCapteurs.h"
#include "CRoues.h"
#include "CMoteurs.h"
#include "CAsservissement.h"
#include "CServomoteurs.h"
#include "CServoMoteursAX.h"
#include "console_interactive_menu.h"
#include "PowerElectrobot.h"
#include "CLaBotBox.h"
#include "CEEPROM.h"
#include "ia.h"
#include "ConfigSpecifiqueCoupe.h"

typedef enum {
    MODE_AUTONOME = 0,
    MODE_PILOTE_LABOTBOX,
    MODE_PILOTE_TERMINAL
}tModeFonctionnement;

// Pour le séquenceur de tâche
#define PERIODE_TICK    (1)
#define TEMPO_1msec     (1/PERIODE_TICK)
#define TEMPO_5msec     (5/PERIODE_TICK)
#define TEMPO_10msec    (10/PERIODE_TICK)
#define TEMPO_20msec    (20/PERIODE_TICK)
#define TEMPO_50msec    (50/PERIODE_TICK)
#define TEMPO_100msec   (100/PERIODE_TICK)
#define TEMPO_200msec   (200/PERIODE_TICK)
#define TEMPO_500msec   (500/PERIODE_TICK)
#define TEMPO_1sec      (1000/PERIODE_TICK)
#define TEMPO_2sec      (2000/PERIODE_TICK)
#define TEMPO_5sec      (5000/PERIODE_TICK)
#define TEMPO_10sec     (10000/PERIODE_TICK)
#define TEMPO_15sec     (15000/PERIODE_TICK)

#define POWER_ELECTROBOT_I2C_ADDR 0x54

// -----------------------------
//! Classe de gestion des options d'exécution passees en ligne de commande
class CGlobale {
public :
    //! Le mode de fonctionnement (autonome ou piloté via Anaconbot)
    unsigned int ModeFonctionnement;

    CGlobale();
    ~CGlobale();

    //! Point d'entree pour lancer l'application
    void Run(void);

    //! Reception RS232 en IRQ
    void ReceiveRS232_ModePiloteTerminal(unsigned char data);

    //! La gestion des Led
    CLed m_led1;
    CLed m_led2;
    CLed m_led3;
    CLed m_led4;
    CLeds m_leds;
    //! Gestion de l'EEPROM
    CEEPROM m_eeprom;
    //! Gestion des codeurs de position
    CCodeurs m_codeurs;
    //! Gestion des télémètres
    CTelemetres m_telemetres;
    //! Gestion des détections d'obstacles (à priori l'algo de la classe de base suffit).
    CDetectionObstaclesBase m_detection_obstacles;
    //! Gestion Electrobot
    CElectrobot m_electrobot;
    //! Gestion des capteurs
    CCapteurs m_capteurs;
    //! La gestion des roues gauches et droites
    CRoues m_roues;
    //! Gestion des moteurs
    CMoteurs m_moteurs;
    //! Gestion de l'asservissement vitesse/position du robot
    CAsservissement m_asservissement;
    //! Carte PowerElectrobot
    PowerElectrobot m_power_electrobot;
    //! Servmoteurs intégrés
    CServomoteurs m_servos;
    //! Servmoteurs AX
    CServoMoteursAX m_servos_ax;
    //! La gestion Labotbox
    CLaBotBox m_LaBotBox;
    //! Le match à  jouer
    IA m_modelia;

    CMenuApp m_menu_interactive;

private : 
    //! Gestion du mode autonome
    void ModeAutonome(void);
    //! Sequenceur de taches en mode autonome
    void SequenceurModeAutonome(void);
    //! Sequenceur de taches en mode pilote par Anaconbot
    void SequenceurModePiloteLaBotBox(void);
    //! Sequenceur de taches en mode pilote par teminal RS232
    void SequenceurModePiloteTerminal(void);



    //! Gestion du mode piloté via Anaconbot
    void ModePiloteLaBotBox(void);

    //! Gestion du mode piloté par terminal
    void ModePiloteTerminal(void);

    //! Lecture eeprom
    void readEEPROM();
};

extern CGlobale Application;

#endif 



