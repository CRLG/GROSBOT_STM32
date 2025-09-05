#ifndef IA_H
#define IA_H

#include "iabase.h"
#include "sm_autotest.h"

#include "sm_debuginterface.h"
#include "sm_retourzonearrivee.h"
#include "sm_chasseneige.h"
#include "sm_deposerbanderole.h"
#include "sm_deposerpilebordure.h"
#include "sm_deposerpilecentrale.h"
#include "sm_deposerpilebasdepente.h"
#include "sm_assembler2etages.h"
#include "sm_blockly_debutant.h"

class IA : public IABase
{
public:
    IA();

    // States machines
    SM_Autotest                         m_sm_autotest;
    SM_ChasseNeige                      m_sm_chasse_neige;
    SM_DeposerBanderole                 m_sm_deposer_banderole;
    SM_DeposerPileBordure               m_sm_deposer_pile_bordure;
    SM_DeposerPileCentrale              m_sm_deposer_pile_centrale;
    SM_DeposerPileBasDePente            m_sm_deposer_pile_bas_de_pente;
    SM_RetourZoneArrivee                m_sm_retour_zone_arrivee;
    SM_Assembler2Etages                 m_sm_assembler_2_etages;
    SM_Tache1                           m_sm_tache1;
    SM_Tache2                           m_sm_tache2;
    SM_Tache3                           m_sm_tache3;
    SM_Tache4                           m_sm_tache4;
    SM_Tache5                           m_sm_tache5;
    SM_Tache6                           m_sm_tache6;
    SM_Tache7                           m_sm_tache7;
    SM_Tache8                           m_sm_tache8;
    SM_Tache9                           m_sm_tache9;
    SM_Tache10                          m_sm_tache10;

    void step();
    void init();
    void match_started();
    void match_finished();

    void setStrategie(unsigned char strategie);
    void setMaxScores();
};

#endif // IA_H
