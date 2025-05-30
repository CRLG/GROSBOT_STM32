/**
 * Generated 29_05_2025 at 19_12
 */

#include "sm_assembler2etages.h"
#include "CGlobale.h"

SM_Assembler2Etages::SM_Assembler2Etages()
{
	m_main_mission_type = true;
	m_max_score = 0;
}

const char* SM_Assembler2Etages::getName()
{
    return "SM_Assembler2Etages";
}

const char* SM_Assembler2Etages::stateToName(unsigned short state)
{
	switch(state)
	{
		case STATE_1 :		return "STATE_1";
		case STATE_2 :		return "STATE_2";
		case STATE_3 :		return "STATE_3";
		case STATE_4 :		return "STATE_4";
		case FIN_MISSION :	return "FIN_MISSION";
	}
	return "UNKNOWN_STATE";
}

// _____________________________________
void SM_Assembler2Etages::step()
{
	switch (m_state)
	{

	// ___________________________
	case STATE_1 :
		if (onEntry()) {
		}

		if (onExit()) {  }
		break;
	// ___________________________
	case STATE_2 :
		if (onEntry()) {
		}

		if (onExit()) {  }
		break;
	// ___________________________
	case STATE_3 :
		if (onEntry()) {
		}

		if (onExit()) {  }
		break;
	// ___________________________
	case STATE_4 :
		if (onEntry()) {
		}

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
