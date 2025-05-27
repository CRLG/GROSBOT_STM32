/*! \file CGlobale_ModePiloteLaBotBox.cpp
    \brief Classe qui contient toute l'application pour le mode de fonctionnement pilote via Anaconbot
*/
#include "CGlobale.h"

//___________________________________________________________________________
/*!
   \brief Gestion du mode piloté via Labotbox

   \param --
   \return --
*/
void CGlobale::ModePiloteLaBotBox(void)
{
    m_LaBotBox.Start();
    m_LaBotBox.setAllTransmitPeriod(200);  // Toutes les trames sont envoyées à Labotbox avec la même période
    m_leds.setPattern(PATTERN_CLIGNO_12_34, 200);

    while(1) {
        if (tick>0) {
            tick = 0;
            SequenceurModePiloteLaBotBox();
        }
    }
}

//___________________________________________________________________________
/*!
   \brief Sequenceur de taches en mode Labotbox

   \param --
   \return --
*/
void CGlobale::SequenceurModePiloteLaBotBox(void)
{
    static unsigned int cpt1msec= 0;
    static unsigned int cpt5msec= 0;
    static unsigned int cpt10msec = 0;
    static unsigned int cpt20msec = 0;
    static unsigned int cpt50msec = 0;
    static unsigned int cpt100msec = 0;
    static unsigned int cpt200msec = 0;
    static unsigned int cpt500msec = 0;
    static unsigned int cpt1sec = 0;

    // ______________________________
    cpt1msec++;
    if (cpt1msec >= TEMPO_1msec) {
        cpt1msec = 0;

        m_codeurs.Traitement();
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

        m_LaBotBox.Execute();
    }

    // ______________________________
    cpt20msec++;
    if (cpt20msec >= TEMPO_20msec) {
        cpt20msec = 0;

        m_electrobot.Traitement();
        m_capteurs.Traitement();
        m_telemetres.Traitement();
        m_servos.periodicCall();
    }

    // ______________________________
    cpt50msec++;
    if (cpt50msec >= TEMPO_50msec) {
        cpt50msec = 0;

        m_leds.compute();
        m_ascenseur.periodicCall();
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

        HAL_GPIO_TogglePin(LED2_GPIO_Port, LED2_Pin);
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
