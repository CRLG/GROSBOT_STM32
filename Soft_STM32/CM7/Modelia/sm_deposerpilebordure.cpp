/**
 * Generated 17_04_2025 at 13_24
 */

#include "sm_deposerpilebordure.h"
#include "CGlobale.h"

SM_DeposerPileBordure::SM_DeposerPileBordure()
{
	m_main_mission_type = true;
	m_max_score = 0;
}

const char* SM_DeposerPileBordure::getName()
{
    return "SM_DeposerPileBordure";
}

const char* SM_DeposerPileBordure::stateToName(unsigned short state)
{
	switch(state)
	{
		case STATE_1 :		return "STATE_1";
		case FIN_MISSION :	return "FIN_MISSION";
	}
	return "UNKNOWN_STATE";
}

// _____________________________________
void SM_DeposerPileBordure::step()
{
	switch (m_state)
	{

	// ___________________________
	case STATE_1 :
		if (onEntry()) {
            Application.m_asservissement.CommandeMouvementXY(160,0);/**/
		}

            gotoStateAfter(FIN_MISSION, 20000);
		if (onExit()) {  }
		break;

	// ___________________________
	case FIN_MISSION :
		m_succes = true;
		m_score = m_max_score;
		stop();
		break;
	}
}
