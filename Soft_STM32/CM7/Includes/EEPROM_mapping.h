/*! \file EEPROM_mapping.h
    \brief Mapping EEPROM
*/
#ifndef _EEPROM_MAPPING_H_
#define _EEPROM_MAPPING_H_

// Toutes les données sont sur 32 bits
class EEPROM_MAPPING {
public :
    static const unsigned int NB_MAX_EE_DATA = 100;
    typedef enum {
        MODE_FONCTIONNEMENT,
        // ASSERV
        CDE_MAX,
        CDE_MIN,
        KP_DISTANCE,
        KI_DISTANCE,
        KP_ANGLE,
        KI_ANGLE,
        K_ANGLE,
        SEUIL_CONV_DISTANCE,
        SEUIL_CONV_ANGLE,
        COMPTEUR_MAX,
        ZONE_MORTE_D,
        ZONE_MORTE_G,
        // ______________________________
        ADDR_MAGIC_NUMBER = NB_MAX_EE_DATA,
        // ______________________________
        ADDR_CHECKSUM,
        // ==================================
        EEPROM_MAX_SIZE
    }tEE_WORD_VIRTUAL_ADDR;
};
#endif


