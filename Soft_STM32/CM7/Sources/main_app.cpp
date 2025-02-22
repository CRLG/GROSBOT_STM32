/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include "main.h"

/* Private includes ----------------------------------------------------------*/
#include "CGlobale.h"
#include "retarget.h"

CGlobale Application;

// --------------------------------------------------
uint8_t uart_irq_rxbuff[1];
void irq_uart3()
{
    HAL_UART_Receive_IT(&huart3, uart_irq_rxbuff, 1);
    if (Application.ModeFonctionnement == MODE_AUTONOME) {
        Application.ReceiveRS232_ModeAutonome(uart_irq_rxbuff[0]);
    }
    else if (Application.ModeFonctionnement == MODE_PILOTE_LABOTBOX) {
        Application.ReceiveRS232_ModePiloteLabotbox(uart_irq_rxbuff[0]);
    }
    else if (Application.ModeFonctionnement == MODE_PILOTE_TERMINAL) {
        Application.ReceiveRS232_ModePiloteTerminal(uart_irq_rxbuff[0]);
    }
}

// =====================================================
int main_app(void)
{
	  // Entrees codeurs
	  HAL_TIM_Encoder_Start(&htim1, TIM_CHANNEL_1);
	  HAL_TIM_Encoder_Start(&htim1, TIM_CHANNEL_2);

	  HAL_TIM_Encoder_Start(&htim3, TIM_CHANNEL_1);
	  HAL_TIM_Encoder_Start(&htim3, TIM_CHANNEL_2);

	  HAL_TIM_Encoder_Start(&htim4, TIM_CHANNEL_1);
	  HAL_TIM_Encoder_Start(&htim4, TIM_CHANNEL_2);

	  HAL_TIM_Encoder_Start(&htim8, TIM_CHANNEL_1);
	  HAL_TIM_Encoder_Start(&htim8, TIM_CHANNEL_2);

	  // Sorties PWM servo
	  HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);
	  HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_2);
	  HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_3);
	  HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_4);

	  HAL_TIM_PWM_Start(&htim12, TIM_CHANNEL_2);
	  HAL_TIM_PWM_Start(&htim13, TIM_CHANNEL_1);
	  HAL_TIM_PWM_Start(&htim14, TIM_CHANNEL_1);

	  // Sorties PMW moteurs
	  HAL_TIM_PWM_Start(&htim15, TIM_CHANNEL_1);
	  HAL_TIM_PWM_Start(&htim15, TIM_CHANNEL_2);
	  HAL_TIM_PWM_Start(&htim16, TIM_CHANNEL_1);
	  HAL_TIM_PWM_Start(&htim17, TIM_CHANNEL_1);

	// Redirection du printf vers l'UART3 (USB)
	RetargetInit(&huart3);

	// Active la reception en IRQ sur l'UART
    HAL_UART_Receive_IT(&huart3, uart_irq_rxbuff, 1);

    Application.Run();
    while (1)
    {
    	// on ne devrait jamais arriver dans cette boucle
    }
    return 0;
}

