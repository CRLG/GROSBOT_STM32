/*! \file RessoucesHardware.h
	\brief Déclare les ressources hardware du MBED utilisées par le reste du logiciel
*/
#ifndef _CM7_RESSOURCES_HARDWARE_H_ 
#define _CM7_RESSOURCES_HARDWARE_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"

#define I2C_HDL_ELECTROBOT hi2c1
#define I2C_DEFAULT_TIMEOUT (100)

#define RESET_CPU_SECURE_CODE (0x5A69)

void setLedBuiltin(bool state);
void toggleLedBuiltin();
void CdeMoteur(unsigned char num_moteur, float cde_pourcent);
void CdeServo(unsigned char num_servo, unsigned int pulse_usec);
unsigned int readAnalog(int num_eana);
float readAnalogVolt(int num_eana);
int getCodeur(int num);
unsigned long getTime();
void wait_ms(unsigned int ms);
void reset_cpu(unsigned int secure_code);

#ifdef __cplusplus
}
#endif

#endif


