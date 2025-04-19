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
    unsigned short magic_read;

    if (!_read_uint16(ADDR_MAGIC_NUMBER, &magic_read)) return false;
    if (magic_read != MAGIC_NUMBER) return false;

    if (!_read_uint32(ADDR_CHECKSUM_MSB, &cs_read)) return false;
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
    for(unsigned int i=0; i<ADDR_MAGIC_NUMBER; i++) {
        if (!_write_uint16(i, 0, false)) return false;
    }
    if (!_write_uint16(ADDR_MAGIC_NUMBER, MAGIC_NUMBER, false)) return false;
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
    unsigned short usval;

    for (unsigned int i=0; i<ADDR_CHECKSUM_MSB; i++) { // toute la plage jusqu'au checksum (exclu)
        _read_uint16(i, &usval);
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
    if (idx >= NB_FLOAT) return false;

    uEETypes u;
    if (!__EE_ReadVariable(ADDR_BEGIN_FLOAT+idx, &u.buff[0])) return false;
    if (!__EE_ReadVariable(ADDR_BEGIN_FLOAT+idx+1, &u.buff[1])) return false;
    if (val) *val = u.f_val;
    return true;
}

//___________________________________________________________________________
bool CEEPROM::read_uint32(unsigned int idx, unsigned long *val)
{
    if (idx >= NB_UINT32) return false;
    return _read_uint32(ADDR_BEGIN_UINT32+idx, val);
}

//___________________________________________________________________________
bool CEEPROM::_read_uint32(unsigned int addr, unsigned long *val)
{
    uEETypes u;
    if (!__EE_ReadVariable(addr, &u.buff[0])) return false;
    if (!__EE_ReadVariable(addr+1, &u.buff[1])) return false;
    if (val) *val = u.uint32_val;
    return true;
}

//___________________________________________________________________________
bool CEEPROM::read_int32(unsigned int idx, long *val)
{
    if (idx >= NB_INT32) return false;

    uEETypes u;
    if (!__EE_ReadVariable(ADDR_BEGIN_INT32+idx, &u.buff[0])) return false;
    if (!__EE_ReadVariable(ADDR_BEGIN_INT32+idx+1, &u.buff[1])) return false;
    if (val) *val = u.int32_val;
    return true;
}

//___________________________________________________________________________
bool CEEPROM::read_uint16(unsigned int idx, unsigned short *val)
{
    if (idx >= NB_UINT16) return false;
    return _read_uint16(ADDR_BEGIN_UINT16+idx, val);
}

//___________________________________________________________________________
bool CEEPROM::_read_uint16(unsigned int addr, unsigned short *val)
{
    uEETypes u;
    if (!__EE_ReadVariable(addr, &u.buff[0])) return false;
    if (val) *val = u.uint16_val;
    return true;
}

//___________________________________________________________________________
bool CEEPROM::read_int16(unsigned int idx, short *val)
{
    if (idx >= NB_INT16) return false;

    uEETypes u;
    if (!__EE_ReadVariable(ADDR_BEGIN_INT16+idx, &u.buff[0])) return false;
    if (val) *val = u.int16_val;
    return true;
}

//___________________________________________________________________________
bool CEEPROM::read_buff(unsigned int start_addr, unsigned short *buff, unsigned int size)
{
    for (unsigned int i=0; i<size; i++) {
        if (!_read_uint16(start_addr+i, &buff[i])) return false;
    }
    return true;
}

// ===========================================================================
//                              ECRITURE
// ===========================================================================

//___________________________________________________________________________
bool CEEPROM::write_float(unsigned int idx, float val)
{
    if (idx >= NB_FLOAT) return false;

    uEETypes u;
    u.f_val = val;
    if (!__EE_WriteVariable(ADDR_BEGIN_FLOAT+idx, u.buff[0])) return false;
    if (!__EE_WriteVariable(ADDR_BEGIN_FLOAT+idx+1, u.buff[1])) return false;
    if (!update_checksum()) return false;
    return true;
}

//___________________________________________________________________________
bool CEEPROM::write_uint32(unsigned int idx, unsigned long val)
{
    if (idx >= NB_UINT32) return false;
    return _write_uint32(ADDR_BEGIN_UINT32+idx, val);
}

//___________________________________________________________________________
bool CEEPROM::_write_uint32(unsigned int addr, unsigned long val, bool update_cs/*=true*/)
{
    uEETypes u;
    u.uint32_val = val;
    if (!__EE_WriteVariable(addr, u.buff[0])) return false;
    if (!__EE_WriteVariable(addr+1, u.buff[1])) return false;
    if (update_cs) {
        if (!update_checksum()) return false;
    }
    return true;
}

//___________________________________________________________________________
bool CEEPROM::write_int32(unsigned int idx, long val)
{
    if (idx >= NB_INT32) return false;

    uEETypes u;
    u.int32_val = val;
    if (!__EE_WriteVariable(ADDR_BEGIN_INT32+idx, u.buff[0])) return false;
    if (!__EE_WriteVariable(ADDR_BEGIN_INT32+idx+1, u.buff[1])) return false;
    if (!update_checksum()) return false;
    return true;
}

//___________________________________________________________________________
bool CEEPROM::write_uint16(unsigned int idx, unsigned short val)
{
    if (idx >= NB_UINT16) return false;
    return _write_uint16(ADDR_BEGIN_UINT16+idx, val);
}

//___________________________________________________________________________
bool CEEPROM::_write_uint16(unsigned int addr, unsigned short val, bool update_cs/*=true*/)
{
    uEETypes u;
    u.uint16_val = val;
    if (!__EE_WriteVariable(addr, u.buff[0])) return false;
    if (update_cs) {
        if (!update_checksum()) return false;
    }
    return true;
}

//___________________________________________________________________________
bool CEEPROM::update_checksum()
{
    return _write_uint32(ADDR_CHECKSUM_MSB, compute_checksum(), false);
}

//___________________________________________________________________________
bool CEEPROM::write_int16(unsigned int idx, short val)
{
    if (idx >= NB_INT16) return false;

    uEETypes u;
    u.int16_val = val;
    if (!__EE_WriteVariable(ADDR_BEGIN_INT16+idx, u.buff[0])) return false;
    if (!update_checksum()) return false;
    return true;
}

//___________________________________________________________________________
bool CEEPROM::write_buff(unsigned int start_addr, unsigned short *buff, unsigned int size)
{
    for (unsigned int i=0; i<size; i++) {
        if (!__EE_WriteVariable(start_addr+i, buff[i])) return false;
    }
    if (!update_checksum()) return false;
    return true;
}


// ==================================================================
//    Appel des fonctions bas niveaux avec plusieurs tentatives
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
