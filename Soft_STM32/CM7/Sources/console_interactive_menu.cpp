/*! \file RessoucesHardware.cpp
    \brief Déclare les ressources hardware du MBED utilisées par le reste du logiciel
*/
#include "console_interactive_menu.h"
#include "RessourcesHardware.h"
#include "stdio.h"

CMenuApp::CMenuApp()
{
    enable_echo(false);
    DECLARE_START_PAGE(CMenuApp::page1)
}

// ______________________________________________
void CMenuApp::send_to_console(char msg[])
{
    printf("%s", msg);
}

// ============================================================================
//                             LES MENUS
// ============================================================================
void CMenuApp::page1()
{
    DECLARE_PAGE("Menu Page 1", CMenuApp::page1);
    DECLARE_OPTION('a', "Commande moteurs", CMenuApp::page_cde_moteurs);
    DECLARE_OPTION('z', "Commande servo", CMenuApp::page_servos);
    DECLARE_OPTION('e', "Capteurs", CMenuApp::page_capteurs);
    DECLARE_OPTION('q', "TEST", CMenuApp::page_set_param_1);
    DECLARE_OPTION('s', "TEST", CMenuApp::page_set_param_2);
}

void CMenuApp::page_cde_moteurs()
{
    DECLARE_PAGE("COMMANDE MOTEURS", CMenuApp::page_cde_moteurs);
    DECLARE_OPTION('0', "Retour en page d'accueil", CMenuApp::page1);
    DECLARE_ACTION('a', "Arrêt moteur G", CMenuApp::action_moteurG_stop);
    DECLARE_ACTION('z', "Moteur G : 10%", CMenuApp::action_moteurG_10pct);
    DECLARE_ACTION('e', "Moteur G : 50%", CMenuApp::action_moteurG_50pct);
    DECLARE_ACTION('r', "Moteur G : 100%", CMenuApp::action_moteurG_100pct);
    DECLARE_ACTION('s', "Moteur G : -10%", CMenuApp::action_moteurG_M10pct);
    DECLARE_ACTION('d', "Moteur G : -50%", CMenuApp::action_moteurG_M50pct);
    DECLARE_ACTION('f', "Moteur G : -100%", CMenuApp::action_moteurG_M100pct);

    DECLARE_ACTION('u', "Arrêt moteur D", CMenuApp::action_moteurD_stop);
    DECLARE_ACTION('i', "Moteur D : 10%", CMenuApp::action_moteurD_10pct);
    DECLARE_ACTION('o', "Moteur D : 50%", CMenuApp::action_moteurD_50pct);
    DECLARE_ACTION('p', "Moteur D : 100%", CMenuApp::action_moteurD_100pct);
    DECLARE_ACTION('k', "Moteur D : -10%", CMenuApp::action_moteurD_M10pct);
    DECLARE_ACTION('l', "Moteur D : -50%", CMenuApp::action_moteurD_M50pct);
    DECLARE_ACTION('m', "Moteur D : -100%", CMenuApp::action_moteurD_M100pct);


}

void CMenuApp::page_capteurs()
{
    DECLARE_PAGE("Capteurs", CMenuApp::page_capteurs);
    DECLARE_OPTION('0', "Retour en page d'accueil", CMenuApp::page1);
    DECLARE_ACTION('a', "Etat des codeurs", CMenuApp::read_codeurs);
    DECLARE_ACTION('z', "Etat des entrees analogiques", CMenuApp::read_analog_inputs);
}

void CMenuApp::page_servos()
{
    DECLARE_PAGE("SERVO MOTEURS", CMenuApp::page_servos);
    DECLARE_OPTION('0', "Retour en page d'accueil", CMenuApp::page1);
    DECLARE_ACTION('a', "Servo1 : 1500", CMenuApp::page_servo1_1500);
    DECLARE_ACTION('z', "Servo1 : 1200", CMenuApp::page_servo1_1200);
    DECLARE_ACTION('e', "Servo1 : 1700", CMenuApp::page_servo1_1700);
    DECLARE_ACTION('r', "Servo1 : 2000", CMenuApp::page_servo1_2000);


    DECLARE_ACTION('q', "Servo2 : 1500", CMenuApp::page_servo2_1500);
    DECLARE_ACTION('s', "Servo2 : 1200", CMenuApp::page_servo2_1200);
    DECLARE_ACTION('d', "Servo2 : 1700", CMenuApp::page_servo2_1700);
    DECLARE_ACTION('f', "Servo2 : 2000", CMenuApp::page_servo2_2000);

    DECLARE_ACTION('w', "Servo3 : 1500", CMenuApp::page_servo3_1500);
    DECLARE_ACTION('x', "Servo3 : 1200", CMenuApp::page_servo3_1200);
    DECLARE_ACTION('c', "Servo3 : 1700", CMenuApp::page_servo3_1700);
    DECLARE_ACTION('v', "Servo3 : 2000", CMenuApp::page_servo3_2000);

}



void CMenuApp::page_set_param_1()
{
    DECLARE_PAGE("Forçage paramètre Param1", CMenuApp::page_set_param_1)
            DECLARE_ACTION('r', "Lecture du paramètre", CMenuApp::action_read_param1)
            DECLARE_OPTION('q', "Retour en page principale", CMenuApp::page1)
            DECLARE_ACTION_DOUBLE("Entrez une valeur pour Param1", CMenuApp::action_set_param1)
}

void CMenuApp::page_set_param_2()
{
    DECLARE_PAGE("Forçage paramètre Param2", CMenuApp::page_set_param_2)
            DECLARE_ACTION('r', "Lecture du paramètre", CMenuApp::action_read_param2)
            DECLARE_OPTION('q', "Retour en page principale", CMenuApp::page_set_param_1)
            DECLARE_ACTION_INT("Entrez une valeur pour Param2", CMenuApp::action_set_param2)
}


// ============================================================================
//                             LES ACTIONS
// ============================================================================
bool CMenuApp::action_set_param1(double val)
{
    _printf("Changement de la valeur du paramètre Param1: %f\n\r", val);
    m_param1 = val;
    return true;
}

bool CMenuApp::action_read_param1()
{
    _printf("Valeur du Param1: %f\n\r", m_param1);
    return true;
}

bool CMenuApp::action_set_param2(int val)
{
    _printf("Changement de la valeur du paramètre Param2: %d\n\r", val);
    m_param2 = val;
    return true;
}

bool CMenuApp::action_read_param2()
{
    _printf("Valeur du Param2: %d\n\r", m_param2);
    return true;
}

bool CMenuApp::action_read_params()
{
    _printf("Valeur du Param1: %f\n\r", m_param1);
    _printf("Valeur du Param2: %d\n\r", m_param2);
    return true;
}


// ===========================================================
//                  MOTEURS
// ===========================================================

bool CMenuApp::action_moteurG_stop()
{
    CdeMoteur(1, 0);
    return true;
}

bool CMenuApp::action_moteurG_10pct()
{
    CdeMoteur(1, 10);
    return true;
}

bool CMenuApp::action_moteurG_50pct()
{
    CdeMoteur(1, 50);
    return true;
}

bool CMenuApp::action_moteurG_100pct()
{
    CdeMoteur(1, 100);
    return true;
}

bool CMenuApp::action_moteurG_M10pct()
{
    CdeMoteur(1, -10);
    return true;
}

bool CMenuApp::action_moteurG_M50pct()
{
    CdeMoteur(1, -50);
    return true;
}

bool CMenuApp::action_moteurG_M100pct()
{
    CdeMoteur(1, -100);
    return true;
}


bool CMenuApp::action_moteurD_stop()
{
    CdeMoteur(2, 0);
    return true;
}

bool CMenuApp::action_moteurD_10pct()
{
    CdeMoteur(2, 10);
    return true;
}

bool CMenuApp::action_moteurD_50pct()
{
    CdeMoteur(2, 50);
    return true;
}

bool CMenuApp::action_moteurD_100pct()
{
    CdeMoteur(2, 100);
    return true;
}

bool CMenuApp::action_moteurD_M10pct()
{
    CdeMoteur(2, -10);
    return true;
}

bool CMenuApp::action_moteurD_M50pct()
{
    CdeMoteur(2, -50);
    return true;
}

bool CMenuApp::action_moteurD_M100pct()
{
    CdeMoteur(2, -100);
    return true;
}

// ===========================================================
//                  SERVO MOTEURS
// ===========================================================
bool CMenuApp::page_servo1_1200()
{
    CdeServo(1, 1200);
    return true;
}

bool CMenuApp::page_servo1_1500()
{
    CdeServo(1, 1500);
    return true;
}

bool CMenuApp::page_servo1_1700()
{
    CdeServo(1, 1700);
    return true;
}

bool CMenuApp::page_servo1_2000()
{
    CdeServo(1, 2000);
    return true;
}

bool CMenuApp::page_servo2_1200()
{
   CdeServo(2, 1200);
    return true;
}

bool CMenuApp::page_servo2_1500()
{
   CdeServo(2, 1500);
    return true;
}

bool CMenuApp::page_servo2_1700()
{
   CdeServo(2, 1700);
    return true;
}

bool CMenuApp::page_servo2_2000()
{
   CdeServo(2, 2000);
    return true;
}


bool CMenuApp::page_servo3_1200()
{
   CdeServo(3, 1200);
    return true;
}

bool CMenuApp::page_servo3_1500()
{
   CdeServo(3, 1500);
    return true;
}

bool CMenuApp::page_servo3_1700()
{
   CdeServo(3, 1700);
    return true;
}

bool CMenuApp::page_servo3_2000()
{
   CdeServo(3, 2000);
    return true;
}



// ===========================================================
//                  CAPTEURS
// ===========================================================

bool CMenuApp::read_codeurs()
{
    _printf("Codeur1: %d / Codeur2: %d / Codeur3: %d / Codeur4: %d\n\r", getCodeur(1), getCodeur(2), getCodeur(3), getCodeur(4));
    return true;
}

bool CMenuApp::read_analog_inputs()
{
    _printf("Eana1=%d / Eana2=%d / Eana3=%d / Eana4=%d / Eana5=%d / Vbat=%d\n\r", readAnalog(1), readAnalog(2), readAnalog(3), readAnalog(4), readAnalog(5), readAnalog(6));
    return true;
}
