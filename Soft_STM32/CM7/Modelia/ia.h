#ifndef IA_H
#define IA_H

#include "iabase.h"
#include "sm_autotest.h"

#include "sm_debuginterface.h"
#include "sm_retour_zone_arrivee.h"
#include "sm_chasseneige.h"
#include "sm_deposer_banderole.h"
#include "sm_deposer_pile_bordure.h"
#include "sm_deposer_pile_centrale.h"
#include "sm_deposer_pile_bas_de_pente.h"

class IA : public IABase
{
public:
    IA();

    // States machines
    SM_Autotest                         m_sm_autotest;
    SM_ChasseNeige                      m_sm_chasse_neige;
    SM_DeposerBanderole                 m_deposer_banderole;
    SM_DeposerPileBordure               m_deposer_pile_bordure;
    SM_DeposerPileCentrale              m_deposer_pile_centrale;
    SM_DeposerPileBasDePente            m_deposer_pile_bas_de_pente;
    SM_RetourZoneArrivee                m_sm_retour_zone_arrivee;

    void step();
    void init();
    void match_started();
    void match_finished();

    void setStrategie(unsigned char strategie);
    void setMaxScores();
};

#endif // IA_H
