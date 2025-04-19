/*! \file CEEPROM.cpp
    \brief Classe de gestion de l'EEPROM
*/

#include "CEEPROM.h"
#include "eeprom_emul.h"

//___________________________________________________________________________
CEEPROM::CEEPROM()
{
}

//___________________________________________________________________________
bool CEEPROM::init()
{
    if (HAL_FLASH_Unlock() != HAL_OK) return false;
    if (!__EE_Init()) return false;
    return true;
}

//___________________________________________________________________________
bool CEEPROM::lock()
{
    return HAL_FLASH_Lock();
}

//___________________________________________________________________________
/*!
 * \brief Vérifie si l'EEPROM est valide ou corrompue
 * \return true si valide / false sinon (ou si lecture impossible)
 * \remark l'EEPROM est considérée valide si :
 *      - Présence du MAGIC_NUMBER à l'endroit attendu
 *      et
 *      - Le checksum calculé correspond au checksum lue à l'emplacement dédié
 */
bool CEEPROM::is_valid()
{
    unsigned long cs_computed = compute_checksum();
    unsigned long cs_read;
    unsigned long magic_read;

    if (!_read_uint32(EEPROM_MAPPING::ADDR_MAGIC_NUMBER, &magic_read)) return false;
    if (magic_read != MAGIC_NUMBER) return false;

    if (!_read_uint32(EEPROM_MAPPING::ADDR_CHECKSUM, &cs_read)) return false;
    if (cs_read != cs_computed) return false;

    return true;
}

//___________________________________________________________________________
/*!
* \brief Formate l'EEPROM
* \return true si le formatage s'est bien passé / false sinon
* \remark le formatage consiste uniquement à :
*       - écrire 0 dans les cases mémoires des données
*       - écrire le MAGIC_NUMBER à l'empalcement dédié
*       - calculer et écrire le checksum à l'emplacement dédié
*  ATTENTION : il est indispensable d'écrire une valeur dans chaque emplacement
*              au moins une fois, sinon, la lecture de cet emplacement est impossible
*/
bool CEEPROM::format()
{
    for(unsigned int i=0; i<EEPROM_MAPPING::ADDR_MAGIC_NUMBER; i++) {
        if (!_write_uint32(i, 0, false)) return false;
    }
    if (!_write_uint32(EEPROM_MAPPING::ADDR_MAGIC_NUMBER, MAGIC_NUMBER, false)) return false;
    if (!update_checksum()) return false;
    return is_valid();  // refait un test de validité
}

//___________________________________________________________________________
/*!
 * \brief Calcul le checksum sur un mot de 32 bits
 * \return le checksum calculé
 * \remark le checksum prend en compte toute la plage de données EEPROM et le MAGIC_NUMBER
 */
unsigned long CEEPROM::compute_checksum()
{
    unsigned long cs = 0;
    unsigned long usval;

    for (unsigned int i=0; i<EEPROM_MAPPING::ADDR_CHECKSUM; i++) { // toute la plage jusqu'au checksum (exclu)
        _read_uint32(i, &usval);
        cs += usval;
    }
    return cs;
}

// ===========================================================================
//                              LECTURE
// ===========================================================================

//___________________________________________________________________________
bool CEEPROM::read_float(unsigned int idx, float *val)
{
    if (idx >= EEPROM_MAPPING::NB_MAX_EE_DATA) return false;

    uEETypes u;
    if (!_read_2words(idx, u.buff)) return false;
    if (val) *val = u.f_val;
    return true;
}

//___________________________________________________________________________
bool CEEPROM::read_uint32(unsigned int idx, unsigned long *val)
{
    if (idx >= EEPROM_MAPPING::NB_MAX_EE_DATA) return false;
    return _read_uint32(idx, val);
}

//___________________________________________________________________________
bool CEEPROM::_read_uint32(unsigned int idx, unsigned long *val)
{
    uEETypes u;
    if (!_read_2words(idx, u.buff)) return false;
    if (val) *val = u.uint32_val;
    return true;
}

//___________________________________________________________________________
bool CEEPROM::read_int32(unsigned int idx, long *val)
{
    if (idx >= EEPROM_MAPPING::NB_MAX_EE_DATA) return false;

    uEETypes u;
    if (!_read_2words(idx, u.buff)) return false;
    if (val) *val = u.int32_val;
    return true;
}



//___________________________________________________________________________
bool CEEPROM::read_buff(unsigned int start_idx, unsigned long *buff, unsigned int size)
{
    for (unsigned int i=0; i<size; i++) {
        if (!_read_uint32(start_idx+i, &buff[i])) return false;
    }
    return true;
}

//___________________________________________________________________________
bool CEEPROM::read_magic_number(unsigned long *val)
{
    return _read_uint32(EEPROM_MAPPING::ADDR_MAGIC_NUMBER, val);
}

//___________________________________________________________________________
bool CEEPROM::read_checksum(unsigned long *val)
{
    return _read_uint32(EEPROM_MAPPING::ADDR_CHECKSUM, val);
}

//___________________________________________________________________________
bool CEEPROM::_read_2words(unsigned int idx, unsigned short *buff)
{
    if (!__EE_ReadVariable(2*idx, &buff[0])) return false;  // *2 car idx est un numéro d'index de variable 32 bits alors que la mémoire bas niveau est gérée en mots de 16 bits
    if (!__EE_ReadVariable(2*idx+1, &buff[1])) return false;
    return true;
}


// ===========================================================================
//                              ECRITURE
// ===========================================================================

//___________________________________________________________________________
bool CEEPROM::write_float(unsigned int idx, float val)
{
    if (idx >= EEPROM_MAPPING::NB_MAX_EE_DATA) return false;

    uEETypes u;
    u.f_val = val;
    if (!_write_2words(idx, u.buff)) return false;
    return true;
}

//___________________________________________________________________________
bool CEEPROM::write_uint32(unsigned int idx, unsigned long val)
{
    if (idx >= EEPROM_MAPPING::NB_MAX_EE_DATA) return false;
    return _write_uint32(idx, val);
}

//___________________________________________________________________________
bool CEEPROM::_write_uint32(unsigned int idx, unsigned long val, bool update_cs/*=true*/)
{
    uEETypes u;
    u.uint32_val = val;
    if (!_write_2words(idx, u.buff, update_cs)) return false;
    return true;
}

//___________________________________________________________________________
bool CEEPROM::write_int32(unsigned int idx, long val)
{
    if (idx >= EEPROM_MAPPING::NB_MAX_EE_DATA) return false;

    uEETypes u;
    u.int32_val = val;
    if (!_write_2words(idx, u.buff)) return false;
    return true;
}

//___________________________________________________________________________
bool CEEPROM::update_checksum()
{
    return _write_uint32(EEPROM_MAPPING::ADDR_CHECKSUM, compute_checksum(), false);
}

//___________________________________________________________________________
bool CEEPROM::write_buff(unsigned int start_idx, unsigned long *buff, unsigned int size)
{
    for (unsigned int i=0; i<size; i++) {
        if (!_write_uint32(start_idx+i, buff[i], false)) return false; // pas d'écriture du checksum à chaque fois mais une seule fois à la fin
    }
    if (!update_checksum()) return false;
    return true;
}


//___________________________________________________________________________
bool CEEPROM::_write_2words(unsigned int idx, unsigned short *buff, bool update_cs/*=true*/)
{
    if (!__EE_WriteVariable(2*idx, buff[0])) return false;  // *2 car idx est un numéro d'index de variable 32 bits alors que la mémoire bas niveau est gérée en mots de 16 bits
    if (!__EE_WriteVariable(2*idx+1, buff[1])) return false;
    if (update_cs) {
        if (!update_checksum()) return false;
    }
    return true;
}

// ==================================================================
//    Appel des fonctions bas niveaux 16 bits avec plusieurs tentatives
// ==================================================================
//___________________________________________________________________________
bool CEEPROM::__EE_ReadVariable(unsigned short VirtAddress, unsigned short *Data)
{
    unsigned int attemp=0;
    unsigned short status;
    do {
        status = EE_ReadVariable(VirtAddress, Data);
        attemp++;
    } while ( (status != HAL_OK) && (attemp < MAX_RETRY));
    return (status == HAL_OK);
}

//___________________________________________________________________________
bool CEEPROM::__EE_WriteVariable(unsigned short VirtAddress, unsigned short Data)
{
    unsigned int attemp=0;
    unsigned short status;
    unsigned short read_value;

    // fait une première lecture de la donnée pour préserver le nombre de cycle d'écriture
    // si la donnée a déjà la valeur attendue
    if (__EE_ReadVariable(VirtAddress, &read_value)) {  // si la lecture échoue, c'est peut être que la mémoire n'est pas encore formatée
        if (read_value == Data) return true;
    }

    do {
        status = EE_WriteVariable(VirtAddress, Data);
        attemp++;
    } while ( (status != HAL_OK) && (attemp < MAX_RETRY));
    return (status == HAL_OK);
}

//___________________________________________________________________________
bool CEEPROM::__EE_Init()
{
    unsigned int attemp=0;
    unsigned short status;
    do {
        status = EE_Init();
        attemp++;
    } while ( (status != HAL_OK) && (attemp < MAX_RETRY));
    return (status == HAL_OK);
}
