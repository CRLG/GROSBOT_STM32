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

    void page1();
    void page_cde_moteurs();
    void page_capteurs();
    void page_servos();
    void page_set_param_1();
    void page_set_param_2();

    bool action_set_param1(double val);
    bool action_read_param1();

    bool action_set_param2(int val);
    bool action_read_param2();

    bool action_read_params();

    bool action_moteurG_stop();
    bool action_moteurG_10pct();
    bool action_moteurG_50pct();
    bool action_moteurG_100pct();
    bool action_moteurG_M10pct();
    bool action_moteurG_M50pct();
    bool action_moteurG_M100pct();

    bool action_moteurD_stop();
    bool action_moteurD_10pct();
    bool action_moteurD_50pct();
    bool action_moteurD_100pct();
    bool action_moteurD_M10pct();
    bool action_moteurD_M50pct();
    bool action_moteurD_M100pct();

    bool read_codeurs();
    bool read_analog_inputs();

    bool page_servo1_1200();
    bool page_servo1_1500();
    bool page_servo1_1700();
    bool page_servo1_2000();

    bool page_servo2_1200();
    bool page_servo2_1500();
    bool page_servo2_1700();
    bool page_servo2_2000();

    bool page_servo3_1200();
    bool page_servo3_1500();
    bool page_servo3_1700();
    bool page_servo3_2000();

    void  page_eeprom();
    bool eep_action_init();
    bool eep_action_is_valid();
    bool eep_action_format();
    bool eep_action_checkshum();
    bool eep_action_magic_number();
    bool eep_action_read_all();

    void page_servos_ax();
    bool ax_check_present();
    bool ax_100();
    bool ax_200();
    bool ax_lecture_pos();

    void page_i2c();
    bool i2c_action_scan();

    void page_modes();
    bool mode_labotbox();
    bool mode_autonome();

    double m_param1;
    int m_param2;
};
#endif 



