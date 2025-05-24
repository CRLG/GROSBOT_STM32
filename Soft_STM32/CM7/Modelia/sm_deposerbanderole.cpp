/**
 * Generated 17_04_2025 at 13_24
 */

#include "sm_deposerbanderole.h"
#include "CGlobale.h"

SM_DeposerBanderole::SM_DeposerBanderole()
{
	m_main_mission_type = true;
	m_max_score = 0;
}

const char* SM_DeposerBanderole::getName()
{
    return "SM_DeposerBanderole";
}

const char* SM_DeposerBanderole::stateToName(unsigned short state)
{
	switch(state)
	{
		case STATE_1 :		return "STATE_1";
		case FIN_MISSION :	return "FIN_MISSION";
	}
	return "UNKNOWN_STATE";
}

// _____________________________________
void SM_DeposerBanderole::step()
{
	switch (m_state)
	{

	// ___________________________
	case STATE_1 :
		if (onEntry()) {
            Application.m_asservissement.CommandeMouvementXY(0, 160);/**/
            Application.m_leds.setPattern(PATTERN_CLIGNO_12_34);
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
