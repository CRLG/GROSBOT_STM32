/**
 * Generated 29_05_2025 at 19_12
 */

#include "sm_retourzonearrivee.h"
#include "CGlobale.h"

SM_RetourZoneArrivee::SM_RetourZoneArrivee()
{
	m_main_mission_type = true;
	m_max_score = 0;
}

const char* SM_RetourZoneArrivee::getName()
{
	return "SM_RetourZoneArrivee";
}

const char* SM_RetourZoneArrivee::stateToName(unsigned short state)
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
void SM_RetourZoneArrivee::step()
{
	switch (m_state)
	{

	// ___________________________
	case STATE_1 :
		if (onEntry()) {
			outputs()->CommandeMouvementXY_TETA_sym(-56,119,3.14);/**/
		}

			gotoStateIfConvergence(STATE_2,5000);
		if (onExit()) {  }
		break;
	// ___________________________
	case STATE_2 :
		if (onEntry()) {
			Application.m_asservissement.CommandeMouvementXY_TETA(-80,119,1.57);/**/
		}

			gotoStateIfConvergence(STATE_3,5000);
		if (onExit()) {  }
		break;
	// ___________________________
	case STATE_3 :
		if (onEntry()) {
			Application.m_servos.CommandePositionVitesse(1,1500,255);/*SERVO_PINCE_PLANCHE values=SERVO_PINCE_PLANCHE_OUVERTE*/
		}

			gotoStateIfTrue(STATE_4,internals()->TempsMatch>96.0);
		if (onExit()) {  }
		break;
	// ___________________________
	case STATE_4 :
		if (onEntry()) {
			Application.m_asservissement.CommandeMouvementXY_TETA(-80,164,1.57);/**/
		}

			gotoStateIfConvergence(FIN_MISSION,5000);
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
