#include "RessourcesHardware.h"
#include "ConfigSpecifiqueCoupe.h"
#include "CGlobale.h"
#include "CServoMoteursAX.h"

CServoMoteursAX::CServoMoteursAX()
{
    m_present_count = 0;
}

CServoMoteursAX::~CServoMoteursAX()
{
}

// ============================================================
//         IMPLEMENTATION DES METHODES VIRTUELLES PURES
//                  (en lien avec le hardware)
// ============================================================
// ______________________________________________________________
tAxErr CServoMoteursAX::read(unsigned char *buff_data, unsigned char size)
{
    unsigned long _timeout=0;
    unsigned char index=0;
    unsigned char _data;
    const unsigned int rx_timeout = 0; // msec

    const unsigned int rx_timeout_msec = 2; // constat en pratique que le servo répond toujours en moins de 2 msec
    unsigned long start_time = getTime(); // msec

    do {
        if (HAL_UART_Receive(&huart2, &_data, 1, 0) == HAL_OK) {
            buff_data[index++] = _data;
            start_time = getTime(); // msec / il y a plusieurs octets à recevoir, à chaque réception valide, recharge le timeout pour le prochain octet
        }
        if (index == size) return AX_OK;
    } while ( (getTime() - start_time) <= rx_timeout_msec );

    return AX_TIMEOUT;
}

// ______________________________________________________________
tAxErr CServoMoteursAX::write(unsigned char *buff_data, unsigned char size)
{
    const unsigned long _timeout=5;

    if (HAL_UART_Transmit(&huart2, buff_data, size, _timeout)== HAL_OK) return AX_OK;

    return AX_WRITE_ERROR;
}

// ______________________________________________________________
tAxErr CServoMoteursAX::flushSerialInput()
{
    __HAL_UART_SEND_REQ(&huart2, UART_RXDATA_FLUSH_REQUEST);
    return AX_OK;
}

// ______________________________________________________________
tAxErr CServoMoteursAX::waitTransmitComplete()
{
    // Pas besoin d'attendre.
    // Cette méthode n'est utilisée que pour être certain que les données soient transmisent
    // pour gérer la pin de direction (voir classe de base dans la méthode "write")
    // Mais avec le STM32, le mode RS485 est utilisé et la pin de direction est automatiquement gérée par le hardware
    return AX_OK;
}

// ______________________________________________________________
tAxErr CServoMoteursAX::setTxEnable(bool state)
{
    (void)state; // pour éviter les warnings

    // Cette méthode n'est utilisée que pour gérer la pin de direction
    // (voir classe de base dans la méthode "write" qui peut être utilisée sur des petits CPU n'ayant pas le mode RS485 intégré)
    // Mais avec le STM32, le mode RS485 est utilisé et la pin de direction est
    // automatiquement gérée par le hardware
    return AX_OK;
}

// ______________________________________________________________
void CServoMoteursAX::delay_us(unsigned long delay)
{
    // Pas besoin d'attendre.
    // Cette méthode n'est utilisée que pour créer un délai avant et après transmission des données
    // pour gérer la pin de direction (voir classe de base dans la méthode "write")
    // Mais avec le STM32, le mode RS485 est utilisé et la pin de direction est automatiquement gérée par le hardware
}


// ____________________________________________________________
// Detect all AX servo present
tAxErr CServoMoteursAX::checkPresents(unsigned char max_id)
{
    m_present_count = 0;
    for (unsigned char i=0; i<=max_id; i++)
    {
        if (isPresent(i)) m_presents_list[m_present_count++] = i;
        wait_ms(5);
    }
    return AX_OK;
}

// ______________________________________________________________
tAxErr CServoMoteursAX::Init(void)
{
    tAxErr err;
    err = readEEPROM(); // Lit l'EEPROM et configure le module

    for (unsigned char i=0; i<NBRE_SERVOS_AX; i++) m_presents_list[i] = -1;  // par défaut, aucun n'est détecté
    m_present_count = 0;
    checkPresents(20); // limite la recherche aux 20 premiers ID
    m_rx_err_count = 0; // efface les erreurs de communications normales durant la recherche de présents
    m_tx_err_count = 0;

    return err;
}

// ______________________________________________________________
// Point d'entrée à appeler périodiquement pour la lecture des positions
//  et autres infos sur le servo
// Ne nécessite pas d'être appelé si le servo AX est utilisé en TX uniquement (les infos du servo AX ne sont pas lues)
tAxErr CServoMoteursAX::compute()
{
    tAxErr err;
    int count_error =0;

    // Pour la sureté de fonctionnement et retour à un un fonctionnement nominal de l'UART en cas de mauvais contact avec le servo
    // En pratique, lorsque le fil est débranché, il arrive que la communication ne redémarre pas bien
    // et que cela plante l'UART. Dans ces cas, il faut réinitialiser l'UART
    if (m_rx_err_count > 200) {
        m_rx_err_count = 100;
        __HAL_UART_DISABLE(&huart2);
        __HAL_UART_ENABLE(&huart2);
    }

    for (int i=0; i<m_present_count;i++)
    {
        int position = getPosition(m_presents_list[i], &err);
        if (err == AX_OK)   m_positions[i] = position;
        else {
            m_positions[i] = 0xFFFF;
            count_error++;
        }
    }
    for (int i=0; i<m_present_count;i++)
    {
        bool ismoving= isMoving(m_presents_list[i], &err);
        if (err == AX_OK)   m_moving[i] = ismoving;
        else {
            m_moving[i] = 1;  // par défaut, si la lecture n'est pas possible, on considère que le servo est en mouvement
            count_error++;
        }
    }
    return count_error==0?AX_OK:AX_INVALID_VALUE;
}


// ______________________________________________________________
// Recherche dans la liste des présents, l'ID
int CServoMoteursAX::servo_id_to_index_present(unsigned char servo_id)
{
    int index = -1;
    for (unsigned int i=0; i<NBRE_SERVOS_AX; i++) {
        if(m_presents_list[i] == servo_id) {
            index = i;
            break; // pas la peine de rechercher plus loin, on a trouvé
        }
    }
    return index;
}

// ______________________________________________________________
tAxErr CServoMoteursAX::readEEPROM(void)
{

    // TODO : gérer l'EEPROM
/*
    tAxErr err;
    // _________________________
    // Lecture des parmaètres de configuration des servos dans l'EEPROM :
    //    - Butée min
    //    - Butée max
    //    - Position initiale à la mise sous tension
    char sBuff[64]="\0";
    unsigned int servo_val;
    for (unsigned int i=0; i<NBRE_SERVOS_AX; i++) {
        sprintf(sBuff, "butee_min_servo_ax_%d", i);
        if (Application.m_eeprom.getValue(sBuff, &servo_val)) {
            err = setLimitPositionMin(i, servo_val);
            if (err != AX_OK) return err;
        }

        sprintf(sBuff, "butee_max_servo_ax_%d", i);
        if (Application.m_eeprom.getValue(sBuff, &servo_val)) {
            err = setLimitPositionMax(i, servo_val);
            if (err != AX_OK) return err;
        }

        sprintf(sBuff, "position_initiale_servo_ax_%d", i);
        if (Application.m_eeprom.getValue(sBuff, &servo_val)) {
            err = setPosition(i, servo_val);
            if (err != AX_OK) return err;
            wait (0.4); // Tempo pour être certain que tous les servos ne bougent pas en même temps (surconsommation)
        }
    }
    */
    return AX_OK;
}
