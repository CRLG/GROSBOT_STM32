/*! \file console_interfactive_menu.cpp
    \brief Menu console / terminal
*/
#include <math.h>
#include <stdio.h>
#include "console_interactive_menu.h"
#include "RessourcesHardware.h"
#include "CGlobale.h"

CMenuApp::CMenuApp()
{
    enable_echo(false);
    DECLARE_START_PAGE(CMenuApp::page_principale);
}

// ______________________________________________
void CMenuApp::send_to_console(char msg[])
{
    printf("%s", msg);
}

// ============================================================================
//                             LES MENUS
// ============================================================================
void CMenuApp::page_principale()
{
    DECLARE_PAGE("Menu Princial", CMenuApp::page_principale);
    DECLARE_OPTION('o', "Changement de mode", CMenuApp::page_modes);
    DECLARE_OPTION('m', "Commande moteurs", CMenuApp::page_cde_moteurs);
    DECLARE_OPTION('z', "Commande asserv", CMenuApp::page_commande_asserv);
    DECLARE_OPTION('s', "Commande servo", CMenuApp::page_servos);
    DECLARE_OPTION('a', "Commande servo AX", CMenuApp::page_servos_ax);
    DECLARE_OPTION('c', "Capteurs", CMenuApp::page_capteurs);
    DECLARE_OPTION('e', "EEPPROM", CMenuApp::page_eeprom);
    DECLARE_OPTION('i', "I2C", CMenuApp::page_i2c);
    DECLARE_OPTION('q', "TEST", CMenuApp::page_set_param_1);
    DECLARE_OPTION('s', "TEST", CMenuApp::page_set_param_2);
}


// =============================================================================
//                          ASSERV
// =============================================================================

void CMenuApp::page_commande_asserv()
{
    DECLARE_PAGE("Commande Asservissement", CMenuApp::page_commande_asserv);
    DECLARE_OPTION('e', "Coeficients Asserv", CMenuApp::page_reglage_coefs)
    DECLARE_ACTION('a', "Arrêt moteurs / Asserv manuel", CMenuApp::arret_moteurs);
    DECLARE_ACTION('q', "CommandeMouvementDistanceAngle(10, 0)", CMenuApp::cde_distance1);
    DECLARE_ACTION('s', "CommandeMouvementDistanceAngle(20, 0)", CMenuApp::cde_distance2);
    DECLARE_ACTION('d', "CommandeMouvementDistanceAngle(50, 0)", CMenuApp::cde_distance3);
    DECLARE_ACTION('f', "CommandeMouvementDistanceAngle(100, 0)", CMenuApp::cde_distance4);
    DECLARE_ACTION('w', "CommandeMouvementDistanceAngle(0, M_PI/4.)", CMenuApp::cde_angle1);
    DECLARE_ACTION('x', "CommandeMouvementDistanceAngle(0, M_PI/2.)", CMenuApp::cde_angle2);
    DECLARE_ACTION('c', "CommandeMouvementDistanceAngle(0, M_PI)", CMenuApp::cde_angle3);
    DECLARE_ACTION('v', "CommandeMouvementDistanceAngle(0, -M_PI/4.)", CMenuApp::cde_angle4);
    DECLARE_ACTION('b', "CommandeMouvementDistanceAngle(0, -M_PI/2.)", CMenuApp::cde_angle5);
    DECLARE_ACTION('n', "CommandeMouvementDistanceAngle(0, -M_PI)", CMenuApp::cde_angle6);
}

bool CMenuApp::force_asserv_manuel(){ Application.m_asservissement.ModeAsservissement = CAsservissementBase::cMODE_MANUEL; return true; }
bool CMenuApp::cde_distance1()      { Application.m_asservissement.CommandeMouvementDistanceAngle(10, 0); return true; }
bool CMenuApp::cde_distance2()      { Application.m_asservissement.CommandeMouvementDistanceAngle(20, 0); return true; }
bool CMenuApp::cde_distance3()      { Application.m_asservissement.CommandeMouvementDistanceAngle(50, 0); return true; }
bool CMenuApp::cde_distance4()      { Application.m_asservissement.CommandeMouvementDistanceAngle(100, 0); return true; }
bool CMenuApp::cde_angle1()         { Application.m_asservissement.CommandeMouvementDistanceAngle(0, M_PI_4); return true; }
bool CMenuApp::cde_angle2()         { Application.m_asservissement.CommandeMouvementDistanceAngle(0, M_PI_2); return true; }
bool CMenuApp::cde_angle3()         { Application.m_asservissement.CommandeMouvementDistanceAngle(0, M_PI); return true; }
bool CMenuApp::cde_angle4()         { Application.m_asservissement.CommandeMouvementDistanceAngle(0, -M_PI_4); return true; }
bool CMenuApp::cde_angle5()         { Application.m_asservissement.CommandeMouvementDistanceAngle(0, -M_PI_2); return true; }
bool CMenuApp::cde_angle6()         { Application.m_asservissement.CommandeMouvementDistanceAngle(0, -M_PI); return true; }

// =============================================================================
//                    REGLAGE COEFS ASSER
// =============================================================================

void CMenuApp::page_reglage_coefs()
{
    DECLARE_PAGE("Réglage coefs", CMenuApp::page_reglage_coefs);
    DECLARE_ACTION('a', "Affiche tous les coefs asserv", CMenuApp::affiche_coefs_asserv);
    DECLARE_OPTION('q', "Kp_distance", CMenuApp::page_kp_distance);
    DECLARE_OPTION('s', "Ki_distance", CMenuApp::page_ki_distance);
    DECLARE_OPTION('d', "Kp_angle", CMenuApp::page_kp_angle);
    DECLARE_OPTION('f', "Ki_angle", CMenuApp::page_ki_angle);
    DECLARE_OPTION('g', "cde_min", CMenuApp::page_cde_min);
    DECLARE_OPTION('h', "cde_max", CMenuApp::page_cde_max);
}


// _________________________________________________
void CMenuApp::page_kp_distance()
{
    DECLARE_PAGE("Forçage Kp_distance", CMenuApp::page_kp_distance)
    DECLARE_OPTION('a', "Retour à la page Coefs", CMenuApp::page_reglage_coefs)
    DECLARE_ACTION_DOUBLE("Entrez une valeur pour Kp_distance", CMenuApp::action_set_Kp_distance)
}

bool CMenuApp::action_set_Kp_distance(double val)
{
    _printf("Changement de la valeur du paramètre kp_distance: %f\n\r", val);
    Application.m_asservissement.kp_distance = val;
    Application.m_eeprom.write_float(EEPROM_MAPPING::KP_DISTANCE, val);
    return true;
}

// _________________________________________________
void CMenuApp::page_ki_distance()
{
    DECLARE_PAGE("Forçage Ki_distance", CMenuApp::page_ki_distance)
    DECLARE_OPTION('a', "Retour à la page Coefs", CMenuApp::page_reglage_coefs)
    DECLARE_ACTION_DOUBLE("Entrez une valeur pour Ki_distance", CMenuApp::action_set_Ki_distance)
}

bool CMenuApp::action_set_Ki_distance(double val)
{
    _printf("Changement de la valeur du paramètre ki_distance: %f\n\r", val);
    Application.m_asservissement.ki_distance = val;
    Application.m_eeprom.write_float(EEPROM_MAPPING::KI_DISTANCE, val);
    return true;
}

// _________________________________________________
void CMenuApp::page_kp_angle()
{
    DECLARE_PAGE("Forçage Kp_angle", CMenuApp::page_kp_angle)
    DECLARE_OPTION('a', "Retour à la page Coefs", CMenuApp::page_reglage_coefs)
    DECLARE_ACTION_DOUBLE("Entrez une valeur pour Kp_angle", CMenuApp::action_set_Kp_angle)
}

bool CMenuApp::action_set_Kp_angle(double val)
{
    _printf("Changement de la valeur du paramètre kp_angle: %f\n\r", val);
    Application.m_asservissement.kp_angle = val;
    Application.m_eeprom.write_float(EEPROM_MAPPING::KP_ANGLE, val);
    return true;
}

// _________________________________________________
void CMenuApp::page_ki_angle()
{
    DECLARE_PAGE("Forçage Ki_angle", CMenuApp::page_ki_angle)
    DECLARE_OPTION('a', "Retour à la page Coefs", CMenuApp::page_reglage_coefs)
    DECLARE_ACTION_DOUBLE("Entrez une valeur pour Ki_angle", CMenuApp::action_set_Ki_angle)
}

bool CMenuApp::action_set_Ki_angle(double val)
{
    _printf("Changement de la valeur du paramètre ki_angle: %f\n\r", val);
    Application.m_asservissement.ki_angle = val;
    Application.m_eeprom.write_float(EEPROM_MAPPING::KI_ANGLE, val);
    return true;
}

// _________________________________________________
void CMenuApp::page_cde_min()
{
    DECLARE_PAGE("Forçage cde_min", CMenuApp::page_cde_min);
    DECLARE_OPTION('a', "Retour à la page Coefs", CMenuApp::page_reglage_coefs);
    DECLARE_ACTION_INT("Entrez une valeur pour cde_min", CMenuApp::action_set_cde_min);
}

bool CMenuApp::action_set_cde_min(int val)
{
    _printf("Changement de la valeur du paramètre cde_min: %d\n\r", val);
    Application.m_asservissement.cde_min = val;
    Application.m_eeprom.write_int32(EEPROM_MAPPING::CDE_MIN, val);
    return true;
}

// _________________________________________________
void CMenuApp::page_cde_max()
{
    DECLARE_PAGE("Forçage cde_min", CMenuApp::page_cde_min);
    DECLARE_OPTION('a', "Retour à la page Coefs", CMenuApp::page_reglage_coefs);
    DECLARE_ACTION_INT("Entrez une valeur pour cde_max", CMenuApp::action_set_cde_max);
}

bool CMenuApp::action_set_cde_max(int val)
{
    _printf("Changement de la valeur du paramètre cde_max: %d\n\r", val);
    Application.m_asservissement.cde_max = val;
    Application.m_eeprom.write_uint32(EEPROM_MAPPING::CDE_MAX, val);
    return true;
}

// _________________________________________________
bool CMenuApp::affiche_coefs_asserv()
{
    _printf("Coef distance Kp=%f / Ki=%f\n\r",  Application.m_asservissement.kp_distance,
                                                Application.m_asservissement.ki_distance);

    _printf("Coef angle : Kp=%f / Ki=%f\n\r",   Application.m_asservissement.kp_angle,
                                                Application.m_asservissement.ki_angle);

    _printf("Coef cde_min=%d / cde_max=%d\n\r", Application.m_asservissement.cde_min,
                                                Application.m_asservissement.cde_max);

    return true;
}


// =============================================================================
//                          EEPROM
// =============================================================================
void CMenuApp::page_eeprom()
{
    DECLARE_PAGE("EEPROM", CMenuApp::page_eeprom);
    DECLARE_ACTION('i', "Initialisation", CMenuApp::eep_action_init);
    DECLARE_ACTION('v', "Test la validité EEPROM", CMenuApp::eep_action_is_valid);
    DECLARE_ACTION('f', "Format l'EEPROM", CMenuApp::eep_action_format);
    DECLARE_ACTION('c', "Checksum EEPROM ", CMenuApp::eep_action_checkshum);
    DECLARE_ACTION('m', "Magic Number", CMenuApp::eep_action_magic_number);
    DECLARE_ACTION('r', "Read all", CMenuApp::eep_action_read_all);
}

bool CMenuApp::eep_action_init()
{
    _printf("Statut de l'init EEPROM: %d\n\r", Application.m_eeprom.init());
    return true;
}


bool CMenuApp::eep_action_is_valid()
{
    _printf("Validité de l'EEPROM: %d\n\r", Application.m_eeprom.is_valid());
    return true;
}

bool CMenuApp::eep_action_format()
{
    _printf("Formatage...\n\r");
    bool status = Application.m_eeprom.format();
    _printf("Statut du formatage : %d\n\r", status);
    return true;
}

bool CMenuApp::eep_action_checkshum()
{
    unsigned long cs_computed = Application.m_eeprom.compute_checksum();
    unsigned long cs_read;
    bool status = Application.m_eeprom.read_checksum(&cs_read);
    printf("Statut Lecture CS: %d / Val=%ld / Computed=%ld\n\r", status, cs_read, cs_computed);
    return true;
}

bool CMenuApp::eep_action_magic_number()
{
    unsigned long ulval;
    bool status = Application.m_eeprom.read_magic_number(&ulval);
    printf("Statut Lecture MagicNumber: %d / Val=0x%lx\n\r", status, ulval);
    return true;
}

bool CMenuApp::eep_action_read_all()
{
    bool status = true;
    typedef union {
        unsigned long ulval;
        float fval;
    }uEE;
    uEE val;
    for (unsigned int i=0; i<EEPROM_MAPPING::NB_MAX_EE_DATA; i++)
    {
        for(unsigned long j=0; j<100000; j++);
        status = Application.m_eeprom.read_uint32(i, &val.ulval);
        if (status) printf("[%d] : 0x%lx / %ld / %f\n\r", i, val.ulval, val.ulval, val.fval);
        else        printf("[%d] : Erreur de lecture\n\r", i);
    }
    eep_action_magic_number();
    eep_action_checkshum();
    return true;
}

// =============================================================================
//                          I2C
// =============================================================================
void CMenuApp::page_i2c()
{
    DECLARE_PAGE("I2C", CMenuApp::page_i2c);
    DECLARE_ACTION('s', "Scan I2C", CMenuApp::i2c_action_scan);
}

bool CMenuApp::i2c_action_scan()
{
    uint8_t data;
    _printf("SCAN I2C\n\r");

    // 1. présentation du scan sous une forme linéaire des calculateurs présents
    for (unsigned int addr=0; addr<0xFF; addr++)
    {
        if (HAL_I2C_Master_Transmit(&I2C_HDL_ELECTROBOT, addr, &data, 1, 200) == HAL_OK) {
            printf(" Echo on 0x%x\n\r", addr);
        }
    }

    // 1. présentation du scan sous une forme de tableau
    _printf("\n\r      ");
    for (unsigned int i=0; i<16; i++) _printf("%x   ", i);
    for (unsigned int addr=0; addr<=0xFF; addr++)
    {
        if ((addr%16) == 0) printf("\n\r0x%02x", addr);
        if (HAL_I2C_Master_Transmit(&I2C_HDL_ELECTROBOT, addr, &data, 1, 200) == HAL_OK) {
            _printf("  OK", addr);
        }
        else {
            _printf("  --", addr);
        }
    }
    _printf("\n\r");

    return true;
}

void CMenuApp::page_set_param_1()
{
    DECLARE_PAGE("Forçage paramètre Param1", CMenuApp::page_set_param_1);
    DECLARE_ACTION('r', "Lecture du paramètre", CMenuApp::action_read_param1);
    DECLARE_OPTION('q', "Retour en page principale", CMenuApp::page_principale);
    DECLARE_ACTION_DOUBLE("Entrez une valeur pour Param1", CMenuApp::action_set_param1);
}

void CMenuApp::page_set_param_2()
{
    DECLARE_PAGE("Forçage paramètre Param2", CMenuApp::page_set_param_2);
    DECLARE_ACTION('r', "Lecture du paramètre", CMenuApp::action_read_param2);
    DECLARE_OPTION('q', "Retour en page principale", CMenuApp::page_set_param_1);
    DECLARE_ACTION_INT("Entrez une valeur pour Param2", CMenuApp::action_set_param2);
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

void CMenuApp::page_cde_moteurs()
{
    DECLARE_PAGE("Commande moteurs", CMenuApp::page_cde_moteurs);
    DECLARE_ACTION('a', "Arrêt moteurs", CMenuApp::arret_moteurs);

    DECLARE_ACTION('q', "Gauche -10%", CMenuApp::cde_mot_G_M1);
    DECLARE_ACTION('s', "Gauche -25%", CMenuApp::cde_mot_G_M2);
    DECLARE_ACTION('d', "Gauche -50%", CMenuApp::cde_mot_G_M3);

    DECLARE_ACTION('k', "Gauche +10%", CMenuApp::cde_mot_G_P1);
    DECLARE_ACTION('l', "Gauche +25%", CMenuApp::cde_mot_G_P2);
    DECLARE_ACTION('m', "Gauche +50%", CMenuApp::cde_mot_G_P3);


    DECLARE_ACTION('w', "Droit -10%", CMenuApp::cde_mot_D_M1);
    DECLARE_ACTION('x', "Droit -25%", CMenuApp::cde_mot_D_M2);
    DECLARE_ACTION('c', "Droit -50%", CMenuApp::cde_mot_D_M3);

    DECLARE_ACTION('v', "Droit +10%", CMenuApp::cde_mot_D_P1);
    DECLARE_ACTION('b', "Droit +25%", CMenuApp::cde_mot_D_P2);
    DECLARE_ACTION('n', "Droit +50%", CMenuApp::cde_mot_D_P3);

    DECLARE_ACTION('r', "Gauche & Droit -10%", CMenuApp::cde_mot_GD_M1);
    DECLARE_ACTION('t', "Gauche & Droit -25%", CMenuApp::cde_mot_GD_M2);
    DECLARE_ACTION('y', "Gauche & Droit -50%", CMenuApp::cde_mot_GD_M3);

    DECLARE_ACTION('i', "Gauche & Droit +10%", CMenuApp::cde_mot_GD_P1);
    DECLARE_ACTION('o', "Gauche & Droit +25%", CMenuApp::cde_mot_GD_P2);
    DECLARE_ACTION('p', "Gauche & Droit +50%", CMenuApp::cde_mot_GD_P3);
}

bool CMenuApp::arret_moteurs()  { Application.m_asservissement.CommandeManuelle(0, 0); return true;}
bool CMenuApp::cde_mot_G_M1()   { force_asserv_manuel(); Application.m_roues.AdapteCommandeMoteur_G(-10); return true; }  // Pour commander une seule roue, on s'assure être en mode asserv manuel
bool CMenuApp::cde_mot_G_M2()   { force_asserv_manuel(); Application.m_roues.AdapteCommandeMoteur_G(-25); return true; }
bool CMenuApp::cde_mot_G_M3()   { force_asserv_manuel(); Application.m_roues.AdapteCommandeMoteur_G(-50); return true; }
bool CMenuApp::cde_mot_G_P1()   { force_asserv_manuel(); Application.m_roues.AdapteCommandeMoteur_G(+10); return true; }
bool CMenuApp::cde_mot_G_P2()   { force_asserv_manuel(); Application.m_roues.AdapteCommandeMoteur_G(+25); return true; }
bool CMenuApp::cde_mot_G_P3()   { force_asserv_manuel(); Application.m_roues.AdapteCommandeMoteur_G(+50); return true; }

bool CMenuApp::cde_mot_D_M1()   { force_asserv_manuel(); Application.m_roues.AdapteCommandeMoteur_D(-10); return true; }
bool CMenuApp::cde_mot_D_M2()   { force_asserv_manuel(); Application.m_roues.AdapteCommandeMoteur_D(-25); return true; }
bool CMenuApp::cde_mot_D_M3()   { force_asserv_manuel(); Application.m_roues.AdapteCommandeMoteur_D(-50); return true; }
bool CMenuApp::cde_mot_D_P1()   { force_asserv_manuel(); Application.m_roues.AdapteCommandeMoteur_D(+10); return true; }
bool CMenuApp::cde_mot_D_P2()   { force_asserv_manuel(); Application.m_roues.AdapteCommandeMoteur_D(+25); return true; }
bool CMenuApp::cde_mot_D_P3()   { force_asserv_manuel(); Application.m_roues.AdapteCommandeMoteur_D(+50); return true; }

bool CMenuApp::cde_mot_GD_M1()   { Application.m_asservissement.CommandeManuelle(-10, -10); return true; }
bool CMenuApp::cde_mot_GD_M2()   { Application.m_asservissement.CommandeManuelle(-25, -25); return true; }
bool CMenuApp::cde_mot_GD_M3()   { Application.m_asservissement.CommandeManuelle(-50, -50); return true; }
bool CMenuApp::cde_mot_GD_P1()   { Application.m_asservissement.CommandeManuelle(+10, +10); return true; }
bool CMenuApp::cde_mot_GD_P2()   { Application.m_asservissement.CommandeManuelle(+25, +25); return true; }
bool CMenuApp::cde_mot_GD_P3()   { Application.m_asservissement.CommandeManuelle(+50, +50); return true; }


// ===========================================================
//                  SERVO MOTEURS
// ===========================================================
void CMenuApp::page_servos()
{
    DECLARE_PAGE("SERVO MOTEURS", CMenuApp::page_servos);
    DECLARE_OPTION('0', "Retour en page d'accueil", CMenuApp::page_principale);
    DECLARE_ACTION('a', "Servo1 : 1000", CMenuApp::page_servo1_1000);
    DECLARE_ACTION('z', "Servo1 : 1200", CMenuApp::page_servo1_1200);
    DECLARE_ACTION('e', "Servo1 : 1500", CMenuApp::page_servo1_1500);
    DECLARE_ACTION('r', "Servo1 : 1700", CMenuApp::page_servo1_1700);
    DECLARE_ACTION('t', "Servo1 : 2000", CMenuApp::page_servo1_2000);

    DECLARE_ACTION('q', "Servo2 : 1000", CMenuApp::page_servo2_1000);
    DECLARE_ACTION('s', "Servo2 : 1200", CMenuApp::page_servo2_1200);
    DECLARE_ACTION('d', "Servo2 : 1500", CMenuApp::page_servo2_1500);
    DECLARE_ACTION('f', "Servo2 : 1700", CMenuApp::page_servo2_1700);
    DECLARE_ACTION('g', "Servo2 : 2000", CMenuApp::page_servo2_2000);

    DECLARE_ACTION('w', "Servo3 : 1000", CMenuApp::page_servo3_1000);
    DECLARE_ACTION('x', "Servo3 : 1200", CMenuApp::page_servo3_1200);
    DECLARE_ACTION('c', "Servo3 : 1500", CMenuApp::page_servo3_1500);
    DECLARE_ACTION('v', "Servo3 : 1700", CMenuApp::page_servo3_1700);
    DECLARE_ACTION('b', "Servo3 : 2000", CMenuApp::page_servo3_2000);
}

bool CMenuApp::page_servo1_1000() { CdeServo(1, 1000); return true; }
bool CMenuApp::page_servo1_1200() { CdeServo(1, 1200); return true; }
bool CMenuApp::page_servo1_1500() { CdeServo(1, 1500); return true; }
bool CMenuApp::page_servo1_1700() { CdeServo(1, 1700); return true; }
bool CMenuApp::page_servo1_2000() { CdeServo(1, 2000); return true; }
bool CMenuApp::page_servo2_1000() { CdeServo(2, 1000); return true; }
bool CMenuApp::page_servo2_1200() { CdeServo(2, 1200); return true; }
bool CMenuApp::page_servo2_1500() { CdeServo(2, 1500); return true; }
bool CMenuApp::page_servo2_1700() { CdeServo(2, 1700); return true; }
bool CMenuApp::page_servo2_2000() { CdeServo(2, 2000); return true; }
bool CMenuApp::page_servo3_1000() { CdeServo(3, 1000); return true; }
bool CMenuApp::page_servo3_1200() { CdeServo(3, 1200); return true; }
bool CMenuApp::page_servo3_1500() { CdeServo(3, 1500); return true; }
bool CMenuApp::page_servo3_1700() { CdeServo(3, 1700); return true; }
bool CMenuApp::page_servo3_2000() { CdeServo(3, 2000); return true; }

// ===========================================================
//                  CAPTEURS
// ===========================================================

void CMenuApp::page_capteurs()
{
    DECLARE_PAGE("Capteurs", CMenuApp::page_capteurs);
    DECLARE_OPTION('0', "Retour en page d'accueil", CMenuApp::page_principale);
    DECLARE_ACTION('a', "Etat des codeurs", CMenuApp::read_codeurs);
    DECLARE_ACTION('z', "Etat des entrees analogiques", CMenuApp::read_analog_inputs);
}

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



// ===========================================================
//                  SERVOS AX
// ===========================================================

void CMenuApp::page_servos_ax()
{
    DECLARE_PAGE("SERVOS AX", CMenuApp::page_servos_ax);
    DECLARE_ACTION('p', "Test présents", CMenuApp::ax_check_present);
    DECLARE_ACTION('q', "Consigne 100", CMenuApp::ax_512);
    DECLARE_ACTION('s', "Consigne 200", CMenuApp::ax_600);
    DECLARE_ACTION('l', "Lecture position", CMenuApp::ax_lecture_pos);
}


bool CMenuApp::ax_check_present()
{
    int count = 0;

    _printf("Test present\n\r");
    for (unsigned int i=0; i< 20; i++) {
        bool present = Application.m_servos_ax.isPresent(i);
        count += present;
        if (present) _printf("ID %d : OK\n\r", i);
    }
    if (count)  _printf("   %d AX trouvés\n\r", count);
    else        _printf(" > Aucun servo AX trouvé !\n\r");

    return true;
}

bool CMenuApp::ax_512()
{
    Application.m_servos_ax.setPosition(1, 512);
    Application.m_servos_ax.setLed(1, 1);
    return true;
}

bool CMenuApp::ax_600()
{
    Application.m_servos_ax.setPosition(1, 600);
    Application.m_servos_ax.setLed(1, 0);
    unsigned short pos = Application.m_servos_ax.getPosition(1);
    _printf("Servo Position = %d\n\r", pos);
    return true;
}

bool CMenuApp::ax_lecture_pos()
{
    for (unsigned char i=0; i<Application.m_servos_ax.m_present_count; i++) {
        unsigned char id = Application.m_servos_ax.m_presents_list[i];
        unsigned short pos = Application.m_servos_ax.getPosition(id);
        _printf("ID=%d - Position = %d\n\r", id, pos);
    }
    return true;
}


// ===========================================================
//                  MODES
// ===========================================================

void CMenuApp::page_modes()
{
    DECLARE_PAGE("MODE FONCTIONNEMENT", CMenuApp::page_modes);
    DECLARE_ACTION('a', "Force mode Autonome", CMenuApp::mode_autonome);
    DECLARE_ACTION('l', "Force mode Labotbox", CMenuApp::mode_labotbox);
}

bool CMenuApp::mode_labotbox()
{
    Application.m_eeprom.write_uint32(EEPROM_MAPPING::MODE_FONCTIONNEMENT, MODE_PILOTE_LABOTBOX);
    reset_cpu(RESET_CPU_SECURE_CODE);
    return true;
}

bool CMenuApp::mode_autonome()
{
    Application.m_eeprom.write_uint32(EEPROM_MAPPING::MODE_FONCTIONNEMENT, MODE_AUTONOME);
    reset_cpu(RESET_CPU_SECURE_CODE);
    return true;
}
