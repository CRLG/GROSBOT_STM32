/*! \file RessoucesHardware.h
	\brief Déclare les ressources hardware du MBED utilisées par le reste du logiciel
*/
#ifndef _CM7_RESSOURCES_HARDWARE_H_ 
#define _CM7_RESSOURCES_HARDWARE_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"

void setLedBuiltin(bool state);
void toggleLedBuiltin();
void CdeMoteur(unsigned char num_moteur, float cde_pourcent);
void CdeServo(unsigned char num_servo, unsigned int pulse_usec);
unsigned int readAnalog(int num_eana);

int getCodeur1();
int getCodeur2();

#ifdef __cplusplus
}
#endif

#endif


