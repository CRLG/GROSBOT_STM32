/*! \file CEEPROM.h
    \brief Classe EEPROM
*/
#ifndef _EEPROM_H_
#define _EEPROM_H_

#include "EEPROM_mapping.h"

/*  GESTION DE L'EEPROM POUR L'APPLICATIF
   Le driver bas niveau STM pour émuler l'EEPROM mobilise 2 pages de 128kb (soit 256kb d'EEPROM)
   Cette classe s'appuie sur le driver bas niveau STM pour :
    - mettre à disposition des fonctions facilitées pour l'écriture et la lecture de valeurs en EEPROM.
    - calculer un checksum
    - gérer le formatage
    - gérer la validité de l'EEPROM par contrôle du MAGIC_NUMBER et du CHECKSUM

   Le mapping des données en mémoire est dans un fichier séparé EEPROM_mapping.h pour faciliter les évolutions
    et prévoir la possibilité de le générer automatiquement par un outil externe

   Les données gérées sont sur 32 bits et le driver couvre UINT32, INT32, FLOAT

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
            unsigned long ulval;
            bool status;
            status = m_eeprom.read_float(12, &fval);                                // 12 = index de la donnée de type float
            status = m_eeprom.read_uint32(EEPROM_MAPPING::EEPROM_DATA_2, &ulval);   // EEPROM_DATA_2 = index de la donnée dans l'énuméré du mapping EEPROM
        }
*/

class CEEPROM
{
public :
    CEEPROM();

    static const unsigned long MAGIC_NUMBER = 0x5A96A569;   //! Valeur du Magic Number
    static const unsigned int MAX_RETRY = 3;                //! Nombre de tentatives d'écriture ou de lecture avant de considérer un échec

    bool init();
    bool lock();
    bool is_valid();
    bool format();
    unsigned long compute_checksum();

    bool read_float(unsigned int idx, float *val);
    bool read_uint32(unsigned int idx, unsigned long *val);
    bool read_int32(unsigned int idx, long *val);
    bool read_buff(unsigned int start_idx, unsigned long *buff, unsigned int size);
    bool read_magic_number(unsigned long *val);
    bool read_checksum(unsigned long *val);

    bool write_float(unsigned int idx, float val);
    bool write_uint32(unsigned int idx, unsigned long val);
    bool write_int32(unsigned int idx, long val);
    bool write_buff(unsigned int start_idx, unsigned long *buff, unsigned int size);

private :
    typedef union {
        float f_val;
        unsigned long uint32_val;
        signed long int32_val;

        unsigned short buff[2]; // 2 * 2 octets = 4 octets pour traiter le max des types gérés (float / int32)
    }uEETypes;

    // lecture et écriture sans contrôle de la valeur de d'index
    bool _read_uint32(unsigned int idx, unsigned long *val);
    bool _write_uint32(unsigned int idx, unsigned long val, bool update_cs=true);
    bool update_checksum();

    bool _read_2words(unsigned int idx, unsigned short *buff);
    bool _write_2words(unsigned int idx, unsigned short *buff, bool update_cs=true);

    // Appel des fonctions bas niveau avec retentatives
    bool __EE_ReadVariable(unsigned short VirtAddress, unsigned short* Data);
    bool __EE_WriteVariable(unsigned short VirtAddress, unsigned short Data);
    bool __EE_Init(void);

};
#endif


