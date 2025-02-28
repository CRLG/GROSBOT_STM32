/*! \file CCodeurs.cpp
    \brief Classe qui contient toute l'application
*/

#include "CCodeurs.h"
#include "RessourcesHardware.h"

//___________________________________________________________________________
CCodeurs::CCodeurs()
    : m_CumulCodeurPosition1(0),
      m_CumulCodeurPosition2(0),
      m_CumulCodeurPosition3(0),
      m_CumulCodeurPosition4(0),
      m_old_codeur1(0),
      m_old_codeur2(0),
      m_old_codeur3(0),
      m_old_codeur4(0)
{
}

// ____________________________________________
/*!
 * \brief Cumul les codeurs 16 bits dans des données 32 bits
 */

void CCodeurs::Traitement(void)
{
    signed short _codeur;

    _codeur = getCodeur(CODEUR_1);
    m_CumulCodeurPosition1 += (signed short)(_codeur - m_old_codeur1);
    m_old_codeur1 = _codeur;

    _codeur = getCodeur(CODEUR_2);
    m_CumulCodeurPosition2 += (signed short)(_codeur - m_old_codeur2);
    m_old_codeur2 = _codeur;

    _codeur = getCodeur(CODEUR_3);
    m_CumulCodeurPosition3 += (signed short)(_codeur - m_old_codeur3);
    m_old_codeur3 = _codeur;

    _codeur = getCodeur(CODEUR_4);
    m_CumulCodeurPosition4 += (signed short)(_codeur - m_old_codeur4);
    m_old_codeur4 = _codeur;
}

// ____________________________________________
/*!
 * \brief Fixe la valeur du codeur à une valeur
 * \param num_codeur le numéro du codeur
 * \param valla valeur de reset
 */
void CCodeurs::reset(unsigned char num_codeur, signed long val /*=0*/)
{
    switch(num_codeur)
    {
    case CODEUR_1: m_CumulCodeurPosition1 = val; break;
    case CODEUR_2: m_CumulCodeurPosition2 = val; break;
    case CODEUR_3: m_CumulCodeurPosition3 = val; break;
    case CODEUR_4: m_CumulCodeurPosition4 = val; break;
    default : break;
    }
}

