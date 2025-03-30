/*! \file CGlobale_ModeAutonome.cpp
    \brief Classe qui contient toute l'application pour le mode de fonctionnement autonome
*/
#include "CGlobale.h"
#include <stdio.h>
//#include "ConfigSpecifiqueCoupe.h"



//___________________________________________________________________________
/*!
   \brief Point d'entrée pour l'execution de toute l'application

   \param --
   \return --
*/
void CGlobale::ModeAutonome(void)
{
    m_LaBotBox.Start();
    m_LaBotBox.setAllTransmitPeriod(200);
    m_leds.setPattern(PATTERN_K2000, 50);
    m_modelia.init();

    while(1) {
        if (tick) {
            tick = 0;
            SequenceurModeAutonome();
        }
    }
}

//___________________________________________________________________________
/*!
   \brief Sequenceur de taches en mode autonome

   \param --
   \return --
*/
void CGlobale::SequenceurModeAutonome(void)
{
    static unsigned int cpt1msec = 0;
    static unsigned int cpt10msec = 0;
    static unsigned int cpt20msec = 0;
    static unsigned int cpt50msec = 0;
    static unsigned int cpt100msec = 0;
    static unsigned int cpt200msec = 0;
    static unsigned int cpt500msec = 0;
    static unsigned int cpt1sec = 0;
    static bool old_match_en_cours=0;

    // ______________________________
    cpt1msec++;
    if (cpt1msec >= TEMPO_1msec) {
        cpt1msec = 0;

        m_codeurs.Traitement();

    }
    // ______________________________
    cpt10msec++;
    if (cpt10msec >= TEMPO_10msec) {
        cpt10msec = 0;

        m_LaBotBox.Execute();
    }

    // ______________________________
    cpt20msec++;
    if (cpt20msec >= TEMPO_20msec) {
        cpt20msec = 0;

        toggleLedBuiltin();

        m_electrobot.Traitement();
        m_capteurs.Traitement();
        m_telemetres.Traitement();

        // Execute un pas de calcul du modele
        m_modelia.step();

        m_asservissement.CalculsMouvementsRobots();
        m_servos.periodicCall();
    }


    // ______________________________
    cpt50msec++;
    if (cpt50msec >= TEMPO_50msec) {
        cpt50msec = 0;

        m_leds.compute();
#ifdef UTILSATION_SERVOS_AX
        m_servos_ax.compute();
#endif
#ifdef UTILISATION_KMAR
        m_kmar.compute();
#endif
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
    }
    // ______________________________
    cpt1sec++;
    if (cpt1sec >= TEMPO_1sec) {
        cpt1sec = 0;

        m_power_electrobot.refreshOuptuts();
    }

}







