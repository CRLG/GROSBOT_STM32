#include "ws2812b.h"
#include "RessourcesHardware.h"
#include "CGlobale.h"

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


// ---------------------------------------
// Les LED tournent dans le sens horaire
void WS2812b::compute_bandeau()
{
    // ____________________________________________
    // Priorité 1 : batterie critique

    if ( (Application.m_power_electrobot.getBatteryVoltage() < SEUIL_TENSION_BATTERIE_CRITIQUE) && (getTime() > 4000) ){
        m_mode_bandeau = BANDEAU_BATTERIE_CRITIQUE;
    }
    if (m_old_mode_bandeau != m_mode_bandeau) {
        m_duree_mode_bandeau = 0;
        for (int i=0; i<NB_OF_LEDS; i++) setState(i, 0); // réinit de toutes les LED
    }

    switch(m_mode_bandeau) {
    // _________________________________________
    case BANDEAU_INIT :
        if (m_duree_mode_bandeau <= (6000/PERIODE_APPEL_GESTION_BANDEAU)) {
            setColor(m_duree_mode_bandeau, RGBColor::BLUE, 10);
            setColor(m_duree_mode_bandeau+1, RGBColor::GREEN, 10);
            setColor(m_duree_mode_bandeau+2, RGBColor::RED, 10);
        }
        else {
            m_mode_bandeau = BANDEAU_RETOUR_DETECTION_OBASTACLE_MODELIA;
        }
        break;

        // _________________________________________
    case BANDEAU_RETOUR_LIDAR :
        break;

        // _________________________________________
    case BANDEAU_RETOUR_DETECTION_OBASTACLE_MODELIA :
        for (int i=0; i<NB_OF_LEDS; i++) setColor(i, 0);
        setColor(INDEX_LED_BANDEAU_OBSTACLE_AVG, Application.m_modelia.m_inputs_interface.obstacle_AVG==true ? RGBColor::RED : RGBColor::OFF_BLACK);
        setColor(INDEX_LED_BANDEAU_OBSTACLE_AVD, Application.m_modelia.m_inputs_interface.obstacle_AVD==true ? RGBColor::RED : RGBColor::OFF_BLACK);
        setColor(INDEX_LED_BANDEAU_OBSTACLE_ARG, Application.m_modelia.m_inputs_interface.obstacle_ARG==true ? RGBColor::RED : RGBColor::OFF_BLACK);
        setColor(INDEX_LED_BANDEAU_OBSTACLE_ARD, Application.m_modelia.m_inputs_interface.obstacle_ARD==true ? RGBColor::RED : RGBColor::OFF_BLACK);
        break;

        // _________________________________________
    case BANDEAU_AUTOTEST_SYSTEM :
        break;


        // _________________________________________
    case BANDEAU_BATTERIE_CRITIQUE :
    default :
        for (int i=0; i<NB_OF_LEDS; i++) {
            configOnOffColor(i, RGBColor::RED, RGBColor::OFF_BLACK);
            setPattern(i, (100/PERIODE_APPEL_GESTION_BANDEAU), 10);
        }
        break;

    }
    // calcul la durée dans le mode courant
    m_duree_mode_bandeau++;
    m_old_mode_bandeau = m_mode_bandeau;
}
