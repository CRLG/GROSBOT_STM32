/*! \file CGlobale_ModePiloteTerminal.cpp
    \brief Classe qui contient toute l'application pour le mode de fonctionnement pilote via Anaconbot
*/
#include "CGlobale.h"
#include <stdio.h>

//___________________________________________________________________________
/*!
   \brief Gestion du mode piloté via Anaconbot

   \param --
   \return --
*/
void CGlobale::ModePiloteTerminal(void)
{
    m_leds.setPattern(PATTERN_CLIGNO_1234, 200);
    while(1) {
        if (tick) {
            tick = 0;
            SequenceurModePiloteTerminal();
        }
    }
}



// _____________________________________________________________
void CGlobale::ReceiveRS232_ModePiloteTerminal(unsigned char data)
{
    HAL_UART_Transmit(&huart3, &data, 1, 100); // renvoi le caractère comme écho
    m_menu_interactive.receive_car(data);
//    if (data == 'i') {
//    	scan_i2c();
//    }
}


//___________________________________________________________________________
/*!
   \brief Sequenceur de taches en mode autonome

   \param --
   \return --
*/
void CGlobale::SequenceurModePiloteTerminal(void)
{
    static unsigned int cpt1msec = 0;
    static unsigned int cpt5msec = 0;
    static unsigned int cpt10msec = 0; // TODO : initialiser à des valeurs différentes pour que les appels soient sur des ticks différents pour répartir la charge CPU
    static unsigned int cpt20msec = 0;
    static unsigned int cpt50msec = 0;
    static unsigned int cpt100msec = 0;
    static unsigned int cpt200msec = 0;
    static unsigned int cpt500msec = 0;
    static unsigned int cpt1sec = 0;

    // ______________________________
    cpt1msec++;
    if (cpt1msec >= TEMPO_1msec) {

        m_codeurs.Traitement();
        cpt1msec = 0;
    }


    // ______________________________
    cpt5msec++;
    if (cpt5msec >= TEMPO_5msec) {
        cpt5msec = 0;

        m_asservissement.CalculsMouvementsRobots();
    }

    // ______________________________
    cpt10msec++;
    if (cpt10msec >= TEMPO_10msec) {
        cpt10msec = 0;

    }

    // ______________________________
    cpt20msec++;
    if (cpt20msec >= TEMPO_20msec) {
        cpt20msec = 0;

        m_electrobot.Traitement();
        m_capteurs.Traitement();
        m_telemetres.Traitement();
    }


    // ______________________________
    cpt50msec++;
    if (cpt50msec >= TEMPO_50msec) {
        cpt50msec = 0;
        m_leds.compute();
        m_ascenseur.periodicCall();
    }

    // ______________________________
    cpt100msec++;
    if (cpt100msec >= TEMPO_100msec) {
        cpt100msec = 0;
    }

    // ______________________________
    cpt200msec++;
    if (cpt200msec >= TEMPO_200msec) {
        cpt200msec = 0;

        m_power_electrobot.periodicCall();
    }
    // ______________________________
    cpt500msec++;
    if (cpt500msec >= TEMPO_500msec) {
        cpt500msec = 0;

        toggleLedBuiltin();
    }
    // ______________________________
    cpt1sec++;
    if (cpt1sec >= TEMPO_1sec) {
        cpt1sec = 0;

        m_power_electrobot.refreshOuptuts();
    }

}
