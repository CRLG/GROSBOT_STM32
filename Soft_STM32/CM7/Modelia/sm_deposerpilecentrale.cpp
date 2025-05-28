/**
 * Generated 28_05_2025 at 19_37
 */

#include "sm_deposerpilecentrale.h"
#include "CGlobale.h"

SM_DeposerPileCentrale::SM_DeposerPileCentrale()
{
	m_main_mission_type = true;
	m_max_score = 0;
}

const char* SM_DeposerPileCentrale::getName()
{
	return "SM_DeposerPileCentrale";
}

const char* SM_DeposerPileCentrale::stateToName(unsigned short state)
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
		case STATE_9 :		return "STATE_9";
		case STATE_10 :		return "STATE_10";
		case STATE_11 :		return "STATE_11";
		case STATE_12 :		return "STATE_12";
		case STATE_13 :		return "STATE_13";
		case STATE_14 :		return "STATE_14";
		case STATE_15 :		return "STATE_15";
		case STATE_16 :		return "STATE_16";
		case STATE_17 :		return "STATE_17";
		case STATE_18 :		return "STATE_18";
		case STATE_19 :		return "STATE_19";
		case FIN_MISSION :	return "FIN_MISSION";
	}
	return "UNKNOWN_STATE";
}

// _____________________________________
void SM_DeposerPileCentrale::step()
{
	switch (m_state)
	{

	// ___________________________
	case STATE_1 :
		if (onEntry()) {
			Application.m_asservissement.CommandeManuelle(-8,-8);/**/
		}

			gotoStateAfter(STATE_2,1500);
		if (onExit()) {  }
		break;
	// ___________________________
	case STATE_2 :
		if (onEntry()) {
			Application.m_asservissement.CommandeManuelle(0,0);/**/
		}

			gotoStateAfter(STATE_3,400);
		if (onExit()) {  }
		break;
	// ___________________________
	case STATE_3 :
		if (onEntry()) {
			Application.m_servos.CommandePositionVitesse(5,750,3000);/*SERVO_BANDEROLE values=SERVO_BANDEROLE_DEPLOYEE*/
		}

			gotoStateAfter(STATE_4,2000);
		if (onExit()) {  }
		break;
	// ___________________________
	case STATE_4 :
		if (onEntry()) {
			
			Application.m_ascenseur.down();

			outputs()->CommandeMouvementXY_TETA_sym(-7,60,1.57);/**/
		}

			gotoStateAfter(STATE_5,1500);
		if (onExit()) {  }
		break;
	// ___________________________
	case STATE_5 :
		if (onEntry()) {
			
			Application.m_detection_obstacles.inhibeDetection(false);

		}

			gotoStateIfConvergence(STATE_6,5000);
		if (onExit()) {  }
		break;
	// ___________________________
	case STATE_6 :
		if (onEntry()) {
			outputs()->CommandeMouvementXY_TETA_sym(-7,80,1.57);/**/
		}

			gotoStateIfConvergence(STATE_7,5000);
		if (onExit()) {  }
		break;
	// ___________________________
	case STATE_7 :
		if (onEntry()) {
			Application.m_servos.CommandePositionVitesse(1,1500,255);/*SERVO_PINCE_PLANCHE values=SERVO_PINCE_PLANCHE_OUVERTE*/
		}

			gotoStateAfter(STATE_8,2000);
		if (onExit()) {  }
		break;
	// ___________________________
	case STATE_8 :
		if (onEntry()) {
			Application.m_servos.CommandePositionVitesse(7,1000,255);/*SERVO_VERIN values=VERRIN_POSITION_BAS*/
		}

			gotoStateAfter(STATE_9,3000);
		if (onExit()) {  }
		break;
	// ___________________________
	case STATE_9 :
		if (onEntry()) {
			Application.m_servos.CommandePositionVitesse(1,2450,255);/*SERVO_PINCE_PLANCHE values=SERVO_PINCE_PLANCHE_FERMEE*/
		}

			gotoStateAfter(STATE_10,2000);
		if (onExit()) {  }
		break;
	// ___________________________
	case STATE_10 :
		if (onEntry()) {
			outputs()->CommandeMouvementXY_TETA_sym(5,20,-1.57);/**/
		}

			gotoStateIfConvergence(STATE_11,5000);
		if (onExit()) {  }
		break;
	// ___________________________
	case STATE_11 :
		if (onEntry()) {
			Application.m_servos.CommandePositionVitesse(1,1500,255);/*SERVO_PINCE_PLANCHE values=SERVO_PINCE_PLANCHE_OUVERTE*/
		}

			gotoStateAfter(STATE_12,2000);
		if (onExit()) {  }
		break;
	// ___________________________
	case STATE_12 :
		if (onEntry()) {
			Application.m_servos.CommandePositionVitesse(7,2000,255);/*SERVO_VERIN values=VERRIN_POSITION_HAUT*/
		}

			gotoStateAfter(STATE_13,3500);
		if (onExit()) {  }
		break;
	// ___________________________
	case STATE_13 :
		if (onEntry()) {
			Application.m_servos.CommandePositionVitesse(3,1150,255);/*SERVO_CAN_MOVER_INT values=SERVO_CAN_MOVER_INT_OFF*/
		}

			gotoStateAfter(STATE_14,200);
		if (onExit()) {  }
		break;
	// ___________________________
	case STATE_14 :
		if (onEntry()) {
			Application.m_servos.CommandePositionVitesse(4,1150,255);/*SERVO_CAN_MOVER_EXT values=SERVO_CAN_MOVER_EXT_OFF*/
		}

			gotoStateAfter(STATE_15,2000);
		if (onExit()) {  }
		break;
	// ___________________________
	case STATE_15 :
		if (onEntry()) {
			Application.m_asservissement.CommandeManuelle(-6,-6);/**/
		}

			gotoStateAfter(STATE_16,1000);
		if (onExit()) {  }
		break;
	// ___________________________
	case STATE_16 :
		if (onEntry()) {
			Application.m_asservissement.CommandeManuelle(0,0);/**/
		}

			gotoStateAfter(STATE_17,400);
		if (onExit()) {  }
		break;
	// ___________________________
	case STATE_17 :
		if (onEntry()) {
			Application.m_servos.CommandePositionVitesse(3,1500,255);/*SERVO_CAN_MOVER_INT values=SERVO_CAN_MOVER_INT_ON*/
		}

			gotoStateAfter(STATE_18,400);
		if (onExit()) {  }
		break;
	// ___________________________
	case STATE_18 :
		if (onEntry()) {
			Application.m_servos.CommandePositionVitesse(4,1500,255);/*SERVO_CAN_MOVER_EXT values=SERVO_CAN_MOVER_EXT_ON*/
		}

			gotoStateAfter(STATE_19,400);
		if (onExit()) {  }
		break;
	// ___________________________
	case STATE_19 :
		if (onEntry()) {
			Application.m_servos.CommandePositionVitesse(1,2350,255);/*SERVO_PINCE_PLANCHE values=SERVO_PINCE_PLANCHE_REPOS*/
		}

			gotoStateAfter(FIN_MISSION,2000);
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
