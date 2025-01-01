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

// --------------------------------------------------
void CdeMoteur1(float cde_pourcent)
{
/*
   if (cde_pourcent == 0) {
       HAL_GPIO_WritePin(Mot1_Sens1_GPIO_Port, Mot1_Sens1_Pin, GPIO_PIN_RESET);
       HAL_GPIO_WritePin(Mot1_Sens2_GPIO_Port, Mot1_Sens2_Pin, GPIO_PIN_RESET);
       __HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_1, 0);
   }
   else if (cde_pourcent > 0) {
       HAL_GPIO_WritePin(Mot1_Sens1_GPIO_Port, Mot1_Sens1_Pin, GPIO_PIN_SET);
       HAL_GPIO_WritePin(Mot1_Sens2_GPIO_Port, Mot1_Sens2_Pin, GPIO_PIN_RESET);
       __HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_1, htim4.Init.Period/100. * cde_pourcent);
   }
   else {
       HAL_GPIO_WritePin(Mot1_Sens1_GPIO_Port, Mot1_Sens1_Pin, GPIO_PIN_RESET);
       HAL_GPIO_WritePin(Mot1_Sens2_GPIO_Port, Mot1_Sens2_Pin, GPIO_PIN_SET);
       __HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_1, htim4.Init.Period/100. * (-cde_pourcent));
   }
*/
}

// --------------------------------------------------
void CdeMoteur2(float cde_pourcent)
{
/*
   if (cde_pourcent == 0) {
       HAL_GPIO_WritePin(Mot2_Sens1_GPIO_Port, Mot2_Sens1_Pin, GPIO_PIN_RESET);
       HAL_GPIO_WritePin(Mot2_Sens2_GPIO_Port, Mot2_Sens2_Pin, GPIO_PIN_RESET);
       __HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_2, 0);
   }
   else if (cde_pourcent > 0) {
       HAL_GPIO_WritePin(Mot2_Sens1_GPIO_Port, Mot2_Sens1_Pin, GPIO_PIN_SET);
       HAL_GPIO_WritePin(Mot2_Sens2_GPIO_Port, Mot2_Sens2_Pin, GPIO_PIN_RESET);
       __HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_2, htim4.Init.Period/100. * cde_pourcent);
   }
   else {
       HAL_GPIO_WritePin(Mot2_Sens1_GPIO_Port, Mot2_Sens1_Pin, GPIO_PIN_RESET);
       HAL_GPIO_WritePin(Mot2_Sens2_GPIO_Port, Mot2_Sens2_Pin, GPIO_PIN_SET);
       __HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_2, htim4.Init.Period/100. * (-cde_pourcent));
   }
*/
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
#define T_PWM_SERVO (20e-3)
void CdeServo1(int ppm1500)
{
    //__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, (float)(ppm1500/1e6) / ((float)T_PWM_SERVO/64000));
}

void CdeServo2(int ppm1500)
{
    //__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_4, (float)(ppm1500/1e6) / ((float)T_PWM_SERVO/64000));
}

void CdeServo3(int ppm1500)
{
    //__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, (float)(ppm1500/1e6) / ((float)T_PWM_SERVO/64000));
}
