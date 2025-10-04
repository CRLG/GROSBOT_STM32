#ifndef _LEDS_WS2812B_H_
#define	_LEDS_WS2812B_H_

#include "ws2812b_uart_base.h"

class WS2812b : public WS2812UartBase
{
public :
    WS2812b();

protected :
    static const unsigned int NB_OF_LEDS = 50;     // 16 LED à contrôler
    static const unsigned int BITS_PER_LED = 24;   // 1 LED = 24 bits (1 octet UART utilisé pour coder 1 bit)
    static const unsigned int LED_DMA_BUFFER_SIZE = (NB_OF_LEDS*BITS_PER_LED);

    unsigned char m_led_ws2812b_dma_buffer[LED_DMA_BUFFER_SIZE];
    tWS2812BPattern m_led_ws2812b[NB_OF_LEDS];

    unsigned int getNumberOfLed();
    unsigned char *getDmaBuffer();
    tWS2812BPattern *getPatternBuffer();
    void send_buffer_dma();

};
#endif	// _LEDS_WS2812B_H_
