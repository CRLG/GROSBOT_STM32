/*! \file RessoucesHardware.cpp
	\brief Déclare les ressources hardware du CPU utilisées par le reste du logiciel
*/
#include "RessourcesHardware.h"

// ===================================================
//          LED INTEGREE SUR LA CARTE
// ===================================================

// --------------------------------------------------
void setLedBuiltin(bool state)
{
    HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, (GPIO_PinState)state);
}

// --------------------------------------------------
void toggleLedBuiltin()
{
    HAL_GPIO_TogglePin(LED2_GPIO_Port, LED2_Pin);
}

// ===================================================
//              COMMANDES MOTEURS
// ===================================================

/*!
 * \brief Commande de moteur
 * \param num_moteur numéro du moteur entre 1 et 4
 * \param cde_pourcent valeur signée du PWM
 * PWM = PeriodTimer * (cde_pourcent / 100)
 *      PeriodTimer = 9600 (htim<xxx>.Init.Period = 9600)
 *      PWM = 9600/100 * cde_pourcent
 *      PWM = 96 * cde_pourcent
 *      (valable pour les 3 timers TIM15, 16, 17)
 */
void CdeMoteur(unsigned char num_moteur, float cde_pourcent)
{
    const float COEF_CDE_MOTEUR = 96;
    switch(num_moteur)
    {
    // ___________________________________________
    case 1:
           if (cde_pourcent == 0) {
               HAL_GPIO_WritePin(Mot1_Sens1_GPIO_Port, Mot1_Sens1_Pin, GPIO_PIN_RESET);
               HAL_GPIO_WritePin(Mot1_Sens2_GPIO_Port, Mot1_Sens2_Pin, GPIO_PIN_RESET);
               __HAL_TIM_SET_COMPARE(&htim15, TIM_CHANNEL_1, 0);
           }
           else if (cde_pourcent > 0) {
               HAL_GPIO_WritePin(Mot1_Sens1_GPIO_Port, Mot1_Sens1_Pin, GPIO_PIN_SET);
               HAL_GPIO_WritePin(Mot1_Sens2_GPIO_Port, Mot1_Sens2_Pin, GPIO_PIN_RESET);
               __HAL_TIM_SET_COMPARE(&htim15, TIM_CHANNEL_1, COEF_CDE_MOTEUR * cde_pourcent);
           }
           else {
               HAL_GPIO_WritePin(Mot1_Sens1_GPIO_Port, Mot1_Sens1_Pin, GPIO_PIN_RESET);
               HAL_GPIO_WritePin(Mot1_Sens2_GPIO_Port, Mot1_Sens2_Pin, GPIO_PIN_SET);
               __HAL_TIM_SET_COMPARE(&htim15, TIM_CHANNEL_1, COEF_CDE_MOTEUR * (-cde_pourcent));
           }
        break;
    // ___________________________________________
    case 2:
           if (cde_pourcent == 0) {
               HAL_GPIO_WritePin(Mot2_Sens1_GPIO_Port, Mot2_Sens1_Pin, GPIO_PIN_RESET);
               HAL_GPIO_WritePin(Mot2_Sens2_GPIO_Port, Mot2_Sens2_Pin, GPIO_PIN_RESET);
               __HAL_TIM_SET_COMPARE(&htim15, TIM_CHANNEL_2, 0);
           }
           else if (cde_pourcent > 0) {
               HAL_GPIO_WritePin(Mot2_Sens1_GPIO_Port, Mot2_Sens1_Pin, GPIO_PIN_RESET);
               HAL_GPIO_WritePin(Mot2_Sens2_GPIO_Port, Mot2_Sens2_Pin, GPIO_PIN_SET);
               __HAL_TIM_SET_COMPARE(&htim15, TIM_CHANNEL_2, COEF_CDE_MOTEUR * cde_pourcent);
           }
           else {
               HAL_GPIO_WritePin(Mot2_Sens1_GPIO_Port, Mot2_Sens1_Pin, GPIO_PIN_SET);
               HAL_GPIO_WritePin(Mot2_Sens2_GPIO_Port, Mot2_Sens2_Pin, GPIO_PIN_RESET);
               __HAL_TIM_SET_COMPARE(&htim15, TIM_CHANNEL_2, COEF_CDE_MOTEUR * (-cde_pourcent));
           }
        break;
    // ___________________________________________
    case 3:
        if (cde_pourcent == 0) {
            HAL_GPIO_WritePin(Mot3_Sens1_GPIO_Port, Mot3_Sens1_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(Mot3_Sens2_GPIO_Port, Mot3_Sens2_Pin, GPIO_PIN_RESET);
            __HAL_TIM_SET_COMPARE(&htim16, TIM_CHANNEL_1, 0);
        }
        else if (cde_pourcent > 0) {
            HAL_GPIO_WritePin(Mot3_Sens1_GPIO_Port, Mot3_Sens1_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(Mot3_Sens2_GPIO_Port, Mot3_Sens2_Pin, GPIO_PIN_RESET);
            __HAL_TIM_SET_COMPARE(&htim16, TIM_CHANNEL_1, COEF_CDE_MOTEUR * cde_pourcent);
        }
        else {
            HAL_GPIO_WritePin(Mot3_Sens1_GPIO_Port, Mot3_Sens1_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(Mot3_Sens2_GPIO_Port, Mot3_Sens2_Pin, GPIO_PIN_SET);
            __HAL_TIM_SET_COMPARE(&htim16, TIM_CHANNEL_1, COEF_CDE_MOTEUR * (-cde_pourcent));
        }
        break;
    // ___________________________________________
    case 4:
        if (cde_pourcent == 0) {
            HAL_GPIO_WritePin(Mot4_Sens1_GPIO_Port, Mot4_Sens1_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(Mot4_Sens2_GPIO_Port, Mot4_Sens2_Pin, GPIO_PIN_RESET);
            __HAL_TIM_SET_COMPARE(&htim17, TIM_CHANNEL_1, 0);
        }
        else if (cde_pourcent > 0) {
            HAL_GPIO_WritePin(Mot4_Sens1_GPIO_Port, Mot4_Sens1_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(Mot4_Sens2_GPIO_Port, Mot4_Sens2_Pin, GPIO_PIN_RESET);
            __HAL_TIM_SET_COMPARE(&htim17, TIM_CHANNEL_1, COEF_CDE_MOTEUR * cde_pourcent);
        }
        else {
            HAL_GPIO_WritePin(Mot4_Sens1_GPIO_Port, Mot4_Sens1_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(Mot4_Sens2_GPIO_Port, Mot4_Sens2_Pin, GPIO_PIN_SET);
            __HAL_TIM_SET_COMPARE(&htim17, TIM_CHANNEL_1, COEF_CDE_MOTEUR * (-cde_pourcent));
        }
        break;
    // ___________________________________________
    default:
        break;
    }
}


// ===================================================
//                      CODEURS
// ===================================================

int getCodeur(int num)
{
	switch(num)
	{
	case 1 : return __HAL_TIM_GET_COUNTER(&htim1); break;
	case 2 : return __HAL_TIM_GET_COUNTER(&htim3); break;
	case 3 : return __HAL_TIM_GET_COUNTER(&htim4); break;
	case 4 : return __HAL_TIM_GET_COUNTER(&htim8); break;
	default: break;
	}
	return 0;
}




// ===================================================
//              ENTREES ANALOGIQUES
// ===================================================

// --------------------------------------------------
unsigned int readAnalog(int num_eana)
{
    ADC_ChannelConfTypeDef sConfig = {0};
    int adc_channel;
    switch(num_eana)
    {
    case 1: adc_channel = ADC_CHANNEL_16;   break;  // Eana1 : PA0
    case 2: adc_channel = ADC_CHANNEL_15;   break;  // Eana2 : PA3
    case 3: adc_channel = ADC_CHANNEL_5;    break;  // Eana3 : PB1
    case 4: adc_channel = ADC_CHANNEL_3;    break;  // Eana4 : PA6
    case 5: adc_channel = ADC_CHANNEL_18;   break;  // Enan5 : PA4
    case 6: adc_channel = ADC_CHANNEL_10;   break;  // Vbat :  PC0
    default :  // entrée Eana inexistante
        return 0;
    }

    sConfig.Channel = adc_channel;
    sConfig.Rank = ADC_REGULAR_RANK_1;
    sConfig.SamplingTime = ADC_SAMPLETIME_16CYCLES_5;
    sConfig.SingleDiff = ADC_SINGLE_ENDED;
    //sConfig.OffsetNumber = ADC_OFFSET_NONE;
    //sConfig.Offset = 0;
    //sConfig.OffsetSignedSaturation = DISABLE;
    if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
    {
        Error_Handler();
    }
    HAL_ADC_Start(&hadc1);
    HAL_ADC_PollForConversion(&hadc1, 1000);
    uint32_t analog_value = HAL_ADC_GetValue(&hadc1);
    HAL_ADC_Stop(&hadc1);
    return analog_value;
}

// --------------------------------------------------
#define COEF_ADC_VOLTS (3.3f/4096)
float readAnalogVolt(int num_eana)
{
    return readAnalog(num_eana) * COEF_ADC_VOLTS;
}

// ===================================================
//              SERVO MOTEURS
// ===================================================

// _______________________________________________
//!
//! \brief Commande d'un servo moteur
//! \param num_servo numéro du servo moteur (entre 1 et 8)
//! \param pulse_usec largeur d'impulsion souhaitée en [µsec]
//! Pulse = ARR * (largeur d’impulsion voulue  en µsec / 20 000µsec)
//! Pour les 4 servo du TIM2 (32 bits)
//!     Pulse = (3 840 000/20 000) * largeur d’impulsion voulue  en µsec
//!     Pulse = 192 * largeur d’impulsion voulue  en µsec
//! Pour les 3 servo du TIM12, 13, 14 (16 bits)
//!     Pulse = (64 000/20 000) * largeur d’impulsion voulue  en µsec
//!     Pulse = 3.2 * largeur d’impulsion voulue  en µsec

//!
void CdeServo(unsigned char num_servo, unsigned int pulse_usec)
{
    const float COEF_TIM32bits = 192; // 191.5;
    const float COEF_TIM16bits = 3.2; // 3.193;

    switch(num_servo)
    {
    case 1 : // Servo1: PB15
        __HAL_TIM_SET_COMPARE(&htim12, TIM_CHANNEL_2, COEF_TIM16bits*pulse_usec);
        break;
    case 2 : // Servo2: PB3
        __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_2, COEF_TIM32bits*pulse_usec);
        break;
    case 3 : // Servo3: PA5
        __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1, COEF_TIM32bits*pulse_usec);
        break;
    case 4 : // Servo4: PB11
        __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_4, COEF_TIM32bits*pulse_usec);
        break;
    case 5 : // Servo5: PB10
        __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_3, COEF_TIM32bits*pulse_usec);
        break;
    case 6 : // Servo6: PF8
        __HAL_TIM_SET_COMPARE(&htim13, TIM_CHANNEL_1, COEF_TIM16bits*pulse_usec);
        break;
    case 7 : // Servo7: PF9
        __HAL_TIM_SET_COMPARE(&htim14, TIM_CHANNEL_1, COEF_TIM16bits*pulse_usec);
        break;
    default :
        break;
    }
}
// ===================================================
//                  Time
// ===================================================
unsigned long getTime()
{
    return HAL_GetTick();
}

void wait_ms(unsigned int ms)
{
    HAL_Delay(ms);
}

// ===================================================
//                  Reset CPU
// ===================================================
void reset_cpu(unsigned int secure_code)
{
    if (secure_code == RESET_CPU_SECURE_CODE)  NVIC_SystemReset();
}
