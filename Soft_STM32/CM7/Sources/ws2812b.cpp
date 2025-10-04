#include "ws2812b.h"
#include "RessourcesHardware.h"

WS2812b::WS2812b()
{
}

// ---------------------------------------
void WS2812b::send_buffer_dma()
{
    HAL_UART_Transmit_DMA(&huart5, m_led_ws2812b_dma_buffer, LED_DMA_BUFFER_SIZE);
}

// ---------------------------------------
unsigned int WS2812b::getNumberOfLed()
{
    return NB_OF_LEDS;
}

// ---------------------------------------
unsigned char *WS2812b::getDmaBuffer()
{
    return m_led_ws2812b_dma_buffer;
}

// ---------------------------------------
WS2812UartBase::tWS2812BPattern *WS2812b::getPatternBuffer()
{
    return m_led_ws2812b;
}
