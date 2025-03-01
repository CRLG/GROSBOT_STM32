/*! \file CEEPROM.h
    \brief Classe EEPROM
*/
#ifndef _EEPROM_H_
#define _EEPROM_H_

/*  GESTION DE L'EEPROM POUR L'APPLICATIF
   Le driver bas niveau STM pour émuler l'EEPROM mobilise 2 pages de 128kb (soit 256kb d'EEPROM)
   Cette classe s'appuie sur le driver bas niveau STM pour
    mettre à disposition des fonctions facilitées pour l'écriture et la lecture de valeurs en EEPROM.
   Un certain nombre de données sont possibles pour chaque type
   Les types suivants sont gérés :
    - Float (32 bits)
    - Entiers non signés 32 bits
    - Entiers signés 32 bits
    - Entiers non signés 16 bits
    - Entiers signés 16 bits

   Par défaut, le nombre de données gérées est identiques pour chaque type.
   Si besoin, il est possible de moduler ce nombre en changeant la constante NB_DATA_PER_TYPE
   Il est également possible d'affecter une taille différente pour chaque type en changeant
     les valeurs des constantes NB_FLOAT, NB_UINT32, NB_INT32, ...

   Utilisation :
     - Instanciation :
        CEEPROM m_eeprom;
     - Utilisation
        if (m_eeprom.init()) {
            if (!m_eeprom.is_valid()) m_eeprom.format(); // Formate l'EEPROM si invalide : c'est peut être la première fois (carte neuve, après un formatage de la flash)
        }
        if (m_eeprom.is_valid()) {
            // récupère les valeurs
            unsigned short usval;
            float fval;
            bool status;
            status = m_eeprom._read_uint16(12, &usval);   // 12 = index de la donnée de type unsigned short
            status = m_eeprom._read_float(12, &fval);     // 12 = index de la donnée de type float
            //  => Dans les 2 cas ci-dessus, c'est le même index 12, mais ça pointe sur des emplacements différents
        }.
*/

class CEEPROM
{
public :
    CEEPROM();

    static const unsigned int NB_DATA_PER_TYPE = 50;
    static const unsigned int NB_FLOAT     = NB_DATA_PER_TYPE;  //! Nombre de données EEPROM de type FLOAT32
    static const unsigned int NB_UINT32    = NB_DATA_PER_TYPE;  //! Nombre de données EEPROM de type UINT32
    static const unsigned int NB_INT32     = NB_DATA_PER_TYPE;  //! Nombre de données EEPROM de type INT32
    static const unsigned int NB_UINT16    = NB_DATA_PER_TYPE;  //! Nombre de données EEPROM de type UINT16
    static const unsigned int NB_INT16     = NB_DATA_PER_TYPE;  //! Nombre de données EEPROM de type INT16

    typedef enum {
        ADDR_BEGIN_FLOAT = 0,
        ADDR_END_FLOAT = ADDR_BEGIN_FLOAT + (NB_FLOAT*sizeof(float)/2) - 1,     // /2 car l'EEPROM fournit des mots de 16 bits
        // ______________________________
        ADDR_BEGIN_UINT32,
        ADDR_END_UINT32 = ADDR_BEGIN_UINT32 + (NB_UINT32*sizeof(unsigned long)/2) - 1,
        // ______________________________
        ADDR_BEGIN_INT32,
        ADDR_END_INT32 = ADDR_BEGIN_INT32 + (NB_INT32*sizeof(long)/2) - 1,
        // ______________________________
        ADDR_BEGIN_UINT16,
        ADDR_END_UINT16 = ADDR_BEGIN_UINT16 + (NB_UINT16*sizeof(unsigned short)/2) - 1,
        // ______________________________
        ADDR_BEGIN_INT16,
        ADDR_END_INT16 = ADDR_BEGIN_INT16 + (NB_INT16*sizeof(short)/2) - 1,
        // ______________________________
        ADDR_MAGIC_NUMBER,
        // ______________________________
        ADDR_CHECKSUM_MSB,
        ADDR_CHECKSUM_LSB,
        // ==================================
        EEPROM_MAX_SIZE
    }tEE_WORD_VIRTUAL_ADDR;

    static const unsigned short MAGIC_NUMBER = 0x5A96;  //! Valeur du Magic Number
    static const unsigned int MAX_RETRY = 3;            //! Nombre de tentatives d'écriture ou de lecture avant de considérer un échec

    bool init();
    bool lock();
    bool is_valid();
    bool format();
    unsigned long compute_checksum();

    bool read_float(unsigned int idx, float *val);
    bool read_uint32(unsigned int idx, unsigned long *val);
    bool read_int32(unsigned int idx, long *val);
    bool read_uint16(unsigned int idx, unsigned short *val);
    bool read_int16(unsigned int idx, short *val);
    bool read_buff(unsigned int start_addr, unsigned short *buff, unsigned int size);

    bool write_float(unsigned int idx, float val);
    bool write_uint32(unsigned int idx, unsigned long val);
    bool write_int32(unsigned int idx, long val);
    bool write_uint16(unsigned int idx, unsigned short val);
    bool write_int16(unsigned int idx, short val);
    bool write_buff(unsigned int start_addr, unsigned short *buff, unsigned int size);

    typedef union {
        float f_val;
        unsigned long uint32_val;
        signed long int32_val;
        unsigned short uint16_val;
        signed short int16_val;

        unsigned short buff[2]; // 2 * 2 octets = 4 octets pour traiter le max des types gérés (float / int32)
    }uEETypes;

    // lecture et écriture sans contrôle de la valeur de d'index
    bool _read_uint32(unsigned int addr, unsigned long *val);
    bool _read_uint16(unsigned int addr, unsigned short *val);
    bool _write_uint32(unsigned int addr, unsigned long val, bool update_cs=true);
    bool _write_uint16(unsigned int addr, unsigned short val, bool update_cs=true);
    bool update_checksum();

    // Appel des fonctions bas niveau avec retentatives
    bool __EE_ReadVariable(unsigned short VirtAddress, unsigned short* Data);
    bool __EE_WriteVariable(unsigned short VirtAddress, unsigned short Data);
    bool __EE_Init(void);

};
#endif


