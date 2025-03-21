#ifndef IA_H
#define IA_H

#include "iabase.h"
#include "sm_autotest.h"

#include "sm_retourzonedepart.h"
#include "sm_chasseneige.h"
#include "sm_debuginterface.h"

class IA : public IABase
{
public:
    IA();

    // States machines
    SM_Autotest                         m_sm_autotest;
    SM_ChasseNeige                      m_sm_chasse_neige;
    SM_RetourZoneDepart                 m_sm_retour_zone_depart;

    void step();
    void init();
    void match_started();
    void match_finished();

    void setStrategie(unsigned char strategie);
    void setMaxScores();
};

#endif // IA_H
