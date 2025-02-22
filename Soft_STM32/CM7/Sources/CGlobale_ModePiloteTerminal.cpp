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
    static unsigned int cpt10msec = 0;
    static unsigned int cpt20msec = 0;
    static unsigned int cpt50msec = 0;
    static unsigned int cpt100msec = 0;
    static unsigned int cpt200msec = 0;
    static unsigned int cpt500msec = 0;
    static unsigned int cpt1sec = 0;

    static unsigned char compteur=1;
    static unsigned char toggle=0;

    // ______________________________
    cpt1msec++;
    if (cpt1msec >= TEMPO_1msec) {
        cpt1msec = 0;
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

        //m_asservissement.CalculsMouvementsRobots();
    }


    // ______________________________
    cpt50msec++;
    if (cpt50msec >= TEMPO_50msec) {
        cpt50msec = 0;

        HAL_GPIO_TogglePin(LED4_GPIO_Port, LED4_Pin);
        HAL_GPIO_TogglePin(LED5_GPIO_Port, LED5_Pin);
        HAL_GPIO_TogglePin(LED6_GPIO_Port, LED6_Pin);
        HAL_GPIO_TogglePin(LED7_GPIO_Port, LED7_Pin);
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
    }
    // ______________________________
    cpt500msec++;
    if (cpt500msec >= TEMPO_500msec) {
        cpt500msec = 0;

        toggleLedBuiltin();
        printf("[%d] : Hello\n\r", HAL_GetTick());
        for (int i=1; i<=6; i++) {
            printf("\t Eana%i = %d\n\r", i, readAnalog(i));
        }
        CdeServo(1, 1000);
        CdeServo(2, 1100);
        CdeServo(3, 1200);
        CdeServo(4, 1300);
        CdeServo(5, 1400);
        CdeServo(6, 1500);
        CdeServo(7, 1647);

        CdeMoteur(1, 10);
        CdeMoteur(2, 1.2);
        CdeMoteur(3, 52);
        CdeMoteur(4, -76);

    }
    // ______________________________
    cpt1sec++;
    if (cpt1sec >= TEMPO_1sec) {
        cpt1sec = 0;
    }

}
