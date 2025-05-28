/**
 * Generated 28_05_2025 at 17_02
 */

#include "sm_autotest.h"
#include "CGlobale.h"

SM_Autotest::SM_Autotest()
{
	m_main_mission_type = true;
	m_max_score = 0;
}

const char* SM_Autotest::getName()
{
	return "SM_Autotest";
}

const char* SM_Autotest::stateToName(unsigned short state)
{
	switch(state)
	{
		case STATE_1 :		return "STATE_1";
		case STATE_2 :		return "STATE_2";
		case STATE_3 :		return "STATE_3";
		case STATE_4 :		return "STATE_4";
		case STATE_5 :		return "STATE_5";
		case STATE_6 :		return "STATE_6";
		case STATE_7 :		return "STATE_7";
		case STATE_8 :		return "STATE_8";
		case FIN_MISSION :	return "FIN_MISSION";
	}
	return "UNKNOWN_STATE";
}

// _____________________________________
void SM_Autotest::step()
{
	switch (m_state)
	{

	// ___________________________
	case STATE_1 :
		if (onEntry()) {
			
            //TODO: On monte l'ascenseur à la main en attendant que Simulia le gère
            Application.m_ascenseur.up();

		}

            gotoStateAfter(STATE_2,400);
		if (onExit()) {  }
		break;
	// ___________________________
	case STATE_2 :
		if (onEntry()) {
            Application.m_servos.CommandePositionVitesse(2,SERVO_PINCE_ARG_OUVERTE,255);/*TODO SERVO_PINCE_ARG values=SERVO_PINCE_ARG_OUVERTE*/
		}

            gotoStateAfter(STATE_3,400);
		if (onExit()) {  }
		break;
	// ___________________________
	case STATE_3 :
		if (onEntry()) {
            Application.m_servos.CommandePositionVitesse(6,SERVO_PINCE_ARD_OUVERTE,255);/*TODO SERVO_PINCE_ARD values=SERVO_PINCE_ARD_OUVERTE*/
		}

            gotoStateAfter(STATE_4,400);
		if (onExit()) {  }
		break;
	// ___________________________
	case STATE_4 :
		if (onEntry()) {
			Application.m_servos.CommandePositionVitesse(7,2000,255);/*SERVO_VERIN values=VERRIN_POSITION_HAUT*/
		}

            gotoStateAfter(STATE_5,400);
		if (onExit()) {  }
		break;
	// ___________________________
	case STATE_5 :
		if (onEntry()) {
			Application.m_servos.CommandePositionVitesse(1,2350,255);/*SERVO_PINCE_PLANCHE values=SERVO_PINCE_PLANCHE_REPOS*/
		}

            gotoStateAfter(STATE_6,400);
		if (onExit()) {  }
		break;
	// ___________________________
	case STATE_6 :
		if (onEntry()) {
			Application.m_servos.CommandePositionVitesse(3,1500,255);/*SERVO_CAN_MOVER_INT values=SERVO_CAN_MOVER_INT_ON*/
		}

            gotoStateAfter(STATE_7,400);
		if (onExit()) {  }
		break;
	// ___________________________
	case STATE_7 :
		if (onEntry()) {
            Application.m_servos.CommandePositionVitesse(4,SERVO_CAN_MOVER_EXT_ON,255);/*TODO SERVO_CAN_TODO MOVER_EXT values=SERVO_CAN_MOVER_EXT_ON*/
		}

            gotoStateAfter(STATE_8,400);
		if (onExit()) {  }
		break;
	// ___________________________
	case STATE_8 :
		if (onEntry()) {
            Application.m_servos.CommandePositionVitesse(5,SERVO_BANDEROLE_RANGEE,255);/*TODO SERVO_BANDEROLE values=SERVO_BANDEROLE_RANGEE*/
		}

            gotoStateAfter(FIN_MISSION,400);
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
