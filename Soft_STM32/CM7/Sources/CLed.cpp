/*! \file CLed.cpp
	\brief Classe qui contient toute l'application
*/
#include "CLed.h"

//___________________________________________________________________________
CLed::CLed(GPIO_TypeDef *GPIOx, int pin)
{
    m_port = GPIOx;
    m_pin = pin;
    m_mode = LEDMODE_MANUAL;
}

//___________________________________________________________________________
bool CLed::_read()
{
    return (bool)HAL_GPIO_ReadPin(m_port, m_pin);
}

//___________________________________________________________________________
void CLed::_write(bool val)
{
    return HAL_GPIO_WritePin(m_port, m_pin, (GPIO_PinState)val);
}
