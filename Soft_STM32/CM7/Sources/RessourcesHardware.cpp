/*! \file RessoucesHardware.cpp
	\brief Déclare les ressources hardware du MBED utilisées par le reste du logiciel
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
 * \brief Commande de liteyr
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
               HAL_GPIO_WritePin(Mot2_Sens1_GPIO_Port, Mot2_Sens1_Pin, GPIO_PIN_SET);
               HAL_GPIO_WritePin(Mot2_Sens2_GPIO_Port, Mot2_Sens2_Pin, GPIO_PIN_RESET);
               __HAL_TIM_SET_COMPARE(&htim15, TIM_CHANNEL_2, COEF_CDE_MOTEUR * cde_pourcent);
           }
           else {
               HAL_GPIO_WritePin(Mot2_Sens1_GPIO_Port, Mot2_Sens1_Pin, GPIO_PIN_RESET);
               HAL_GPIO_WritePin(Mot2_Sens2_GPIO_Port, Mot2_Sens2_Pin, GPIO_PIN_SET);
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

// --------------------------------------------------
int getCodeur1()
{
    return 0; //__HAL_TIM_GET_COUNTER(&htim2);
}

// --------------------------------------------------
int getCodeur2()
{
    return 0; //__HAL_TIM_GET_COUNTER(&htim3);
}


// ===================================================
//              ENTREES ANALOGIQUES
// ===================================================

// --------------------------------------------------
int readAnalog(int channel)
{
/*
    ADC_ChannelConfTypeDef sConfig = {0};

    sConfig.Channel = channel;
    sConfig.Rank = ADC_REGULAR_RANK_1;
    sConfig.SamplingTime = ADC_SAMPLETIME_12CYCLES_5;
    sConfig.SingleDiff = ADC_SINGLE_ENDED;
    //sConfig.OffsetNumber = ADC_OFFSET_NONE;
    //sConfig.Offset = 0;
    //sConfig.OffsetSignedSaturation = DISABLE;
    if (HAL_ADC_ConfigChannel(&hadc2, &sConfig) != HAL_OK)
    {
        Error_Handler();
    }
    HAL_ADC_Start(&hadc2);
    HAL_ADC_PollForConversion(&hadc2, 1000);
    uint32_t analog_value = HAL_ADC_GetValue(&hadc2);
    HAL_ADC_Stop(&hadc2);
    return analog_value;
*/
	return 0;
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
    case 1 :
        __HAL_TIM_SET_COMPARE(&htim12, TIM_CHANNEL_2, COEF_TIM16bits*pulse_usec);
        break;
    case 2 :
        __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_2, COEF_TIM32bits*pulse_usec);
        break;
    case 3 :
        __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1, COEF_TIM32bits*pulse_usec);
        break;
    case 4 :
        __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_4, COEF_TIM32bits*pulse_usec);
        break;
    case 5 :
        __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_3, COEF_TIM32bits*pulse_usec);
        break;
    case 6 :
        __HAL_TIM_SET_COMPARE(&htim13, TIM_CHANNEL_1, COEF_TIM16bits*pulse_usec);
        break;
    case 7 :
        __HAL_TIM_SET_COMPARE(&htim14, TIM_CHANNEL_1, COEF_TIM16bits*pulse_usec);
        break;
    default :
        break;
    }
}
