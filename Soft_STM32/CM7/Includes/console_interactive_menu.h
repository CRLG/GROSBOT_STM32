/*! \file CGlobale.h
        \brief Classe qui contient toute l'application
*/
#ifndef _CONSOLE_INTERACTIVE_MENU_H_
#define _CONSOLE_INTERACTIVE_MENU_H_

#include "console_interaction.h"

class CMenuApp : public ConsoleInteraction
{
public:
    CMenuApp();

    void send_to_console(char msg[]);  // méthode virtuelle pure ré-implémentée

    void page_principale();
    void page_set_param_1();
    void page_set_param_2();

    bool action_set_param1(double val);
    bool action_read_param1();

    bool action_set_param2(int val);
    bool action_read_param2();

    bool action_read_params();

    // _____________________________
    // Page Moteurs
    void page_cde_moteurs();

    bool arret_moteurs();
    bool cde_mot_G_M1();
    bool cde_mot_G_M2();
    bool cde_mot_G_M3();
    bool cde_mot_G_P1();
    bool cde_mot_G_P2();
    bool cde_mot_G_P3();

    bool cde_mot_D_M1();
    bool cde_mot_D_M2();
    bool cde_mot_D_M3();
    bool cde_mot_D_P1();
    bool cde_mot_D_P2();
    bool cde_mot_D_P3();

    bool cde_mot_GD_M1();
    bool cde_mot_GD_M2();
    bool cde_mot_GD_M3();
    bool cde_mot_GD_P1();
    bool cde_mot_GD_P2();
    bool cde_mot_GD_P3();

    // _____________________________
    // Page Asservissement
    void page_commande_asserv();
    bool force_asserv_manuel();
    bool cde_distance1();
    bool cde_distance2();
    bool cde_distance3();
    bool cde_distance4();
    bool cde_angle1();
    bool cde_angle2();
    bool cde_angle3();
    bool cde_angle4();
    bool cde_angle5();
    bool cde_angle6();

    // _____________________________
    // Pages réglages coefs asserv
    void page_reglage_coefs();

    void page_kp_distance();
    bool action_set_Kp_distance(double val);

    void page_ki_distance();
    bool action_set_Ki_distance(double val);

    void page_kp_angle();
    bool action_set_Kp_angle(double val);

    void page_ki_angle();
    bool action_set_Ki_angle(double val);

    void page_cde_min();
    bool action_set_cde_min(int val);

    void page_cde_max();
    bool action_set_cde_max(int val);

    bool affiche_coefs_asserv();

    // _____________________________
    // Page Data logger pour asservissement
    void page_asserv_data_logger();
    bool start_logger();
    bool stop_logger();
    bool print_logger();
    bool synchro_logger_off();
    bool synchro_logger_on();

    // _____________________________
    // Page Capteurs
    void page_capteurs();

    bool read_codeurs();
    bool read_analog_inputs();

    // _____________________________
    // Page Servomoteurs
    void page_servos();

    bool page_servo1_1000();
    bool page_servo1_1200();
    bool page_servo1_1500();
    bool page_servo1_1700();
    bool page_servo1_2000();

    bool page_servo2_1000();
    bool page_servo2_1200();
    bool page_servo2_1500();
    bool page_servo2_1700();
    bool page_servo2_2000();

    bool page_servo3_1000();
    bool page_servo3_1200();
    bool page_servo3_1500();
    bool page_servo3_1700();
    bool page_servo3_2000();

     // _____________________________
    // Page EEPROM
    void  page_eeprom();

    bool eep_action_init();
    bool eep_action_is_valid();
    bool eep_action_format();
    bool eep_action_checkshum();
    bool eep_action_magic_number();
    bool eep_action_read_all();

    // _____________________________
    // Page servos AX
    void page_servos_ax();

    bool ax_check_present();
    bool ax_512();
    bool ax_600();
    bool ax_lecture_pos();

    // _____________________________
    // Page I2C
    void page_i2c();

    bool i2c_action_scan();

    // _____________________________
    // Page Mode de fonctionnement CPU
    void page_modes();

    bool mode_labotbox();
    bool mode_autonome();

    double m_param1;
    int m_param2;
};
#endif 



