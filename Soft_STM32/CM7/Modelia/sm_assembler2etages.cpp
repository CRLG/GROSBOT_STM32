/**
 * Generated 30_05_2025 at 13_04
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
		case STATE_20 :		return "STATE_20";
		case STATE_21 :		return "STATE_21";
		case STATE_22 :		return "STATE_22";
		case STATE_23 :		return "STATE_23";
		case STATE_24 :		return "STATE_24";
		case STATE_25 :		return "STATE_25";
		case STATE_26 :		return "STATE_26";
		case STATE_27 :		return "STATE_27";
		case STATE_28 :		return "STATE_28";
		case STATE_29 :		return "STATE_29";
		case STATE_30 :		return "STATE_30";
		case STATE_31 :		return "STATE_31";
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
			Application.m_servos.CommandePositionVitesse(1,1500,255);/*PINCE_PLANCHE OUVERTE*/
		}

			gotoStateAfter(STATE_2,20);
		if (onExit()) {  }
		break;
	// ___________________________
	case STATE_2 :
		if (onEntry()) {
			outputs()->CommandeMouvementXY_TETA_sym(-39,40,-1.57);/*On se place face aux éléments de jeux*/
		}

			gotoStateIfConvergence(STATE_3,5000);
		if (onExit()) {  }
		break;
	// ___________________________
	case STATE_3 :
		if (onEntry()) {
			outputs()->CommandeMouvementXY_TETA_sym(-39,8,-1.57);/**/
		}

			gotoStateIfConvergence(STATE_4,5000);
		if (onExit()) {  }
		break;
	// ___________________________
	case STATE_4 :
		if (onEntry()) {
			Application.m_asservissement.CommandeManuelle(8,8);/*on accoste les colonnes en boucle ouverte*/
		}

			gotoStateAfter(STATE_5,1000);
		if (onExit()) {  }
		break;
	// ___________________________
	case STATE_5 :
		if (onEntry()) {
			Application.m_asservissement.CommandeManuelle(0,0);/**/
		}

			gotoStateAfter(STATE_6,20);
		if (onExit()) {  }
		break;
	// ___________________________
	case STATE_6 :
		if (onEntry()) {
			Application.m_servos.CommandePositionVitesse(7,1150,255);/*VERIN POSITION_BAS*/
		}

			gotoStateAfter(STATE_7,3000);
		if (onExit()) {  }
		break;
	// ___________________________
	case STATE_7 :
		if (onEntry()) {
			Application.m_servos.CommandePositionVitesse(1,2450,255);/*PINCE_PLANCHE FERMEE*/
		}

			gotoStateAfter(STATE_8,500);
		if (onExit()) {  }
		break;
	// ___________________________
	case STATE_8 :
		if (onEntry()) {
			Application.m_servos.CommandePositionVitesse(4,1150,255);/*CAN_MOVER_EXT OFF*/
		}

			gotoStateAfter(STATE_9,20);
		if (onExit()) {  }
		break;
	// ___________________________
	case STATE_9 :
		if (onEntry()) {
			Application.m_servos.CommandePositionVitesse(7,1590,255);/*VERIN POSITION_INTERMEDIARE*/
		}

			gotoStateAfter(STATE_10,2000);
		if (onExit()) {  }
		break;
	// ___________________________
	case STATE_10 :
		if (onEntry()) {
			Application.m_asservissement.CommandeMouvementDistanceAngle(-50,-1.57);/*on recule, suffisamment pour faire les manoeuvre après*/
		}

			gotoStateIfConvergence(STATE_11,5000);
		if (onExit()) {  }
		break;
	// ___________________________
	case STATE_11 :
		if (onEntry()) {
			Application.m_asservissement.CommandeMouvementDistanceAngle(0,1.57);/*on tourne*/
		}

			gotoStateIfConvergence(STATE_12,5000);
		if (onExit()) {  }
		break;
	// ___________________________
	case STATE_12 :
		if (onEntry()) {
			Application.m_servos.CommandePositionVitesse(1,1500,255);/*PINCE_PLANCHE OUVERTE*/
		}

			gotoStateAfter(STATE_13,500);
		if (onExit()) {  }
		break;
	// ___________________________
	case STATE_13 :
		if (onEntry()) {
			Application.m_servos.CommandePositionVitesse(3,1150,255);/*CAN_MOVER_INT OFF*/
		}

			gotoStateAfter(STATE_14,350);
		if (onExit()) {  }
		break;
	// ___________________________
	case STATE_14 :
		if (onEntry()) {
			Application.m_servos.CommandePositionVitesse(1,2450,255);/*PINCE_PLANCHE FERMEE*/
		}

			gotoStateAfter(STATE_15,500);
		if (onExit()) {  }
		break;
	// ___________________________
	case STATE_15 :
		if (onEntry()) {
			Application.m_servos.CommandePositionVitesse(7,2000,255);/*VERIN POSITION_HAUT*/
		}

			gotoStateAfter(STATE_16,500);
		if (onExit()) {  }
		break;
	// ___________________________
	case STATE_16 :
		if (onEntry()) {
			Application.m_asservissement.CommandeMouvementDistanceAngle(-25,1.57);/*on recule avec le bon angle et à mi-distance pour pouvoir tourner sans tout défoncer*/
		}

			gotoStateIfConvergence(STATE_17,5000);
		if (onExit()) {  }
		break;
	// ___________________________
	case STATE_17 :
		if (onEntry()) {
			Application.m_asservissement.CommandeMouvementDistanceAngle(0,-1.57);/*on tourne*/
		}

			gotoStateIfConvergence(STATE_18,5000);
		if (onExit()) {  }
		break;
	// ___________________________
	case STATE_18 :
		if (onEntry()) {
			Application.m_servos.CommandePositionVitesse(7,1590,255);/*VERIN POSITION_INTERMEDIARE*/
			Application.m_asservissement.CommandeMouvementDistanceAngle(25,-1.57);/*on avance avec le bon angle*/
		}

			gotoStateIfConvergence(STATE_19,5000);
		if (onExit()) {  }
		break;
	// ___________________________
	case STATE_19 :
		if (onEntry()) {
			Application.m_servos.CommandePositionVitesse(1,1500,255);/*PINCE_PLANCHE OUVERTE*/
		}

			gotoStateAfter(STATE_20,100);
		if (onExit()) {  }
		break;
	// ___________________________
	case STATE_20 :
		if (onEntry()) {
			Application.m_servos.CommandePositionVitesse(6,1300,255);/*PINCE_ARD INTERMEDIAIRE*/
		}

			gotoStateAfter(STATE_21,40);
		if (onExit()) {  }
		break;
	// ___________________________
	case STATE_21 :
		if (onEntry()) {
			Application.m_servos.CommandePositionVitesse(2,1300,255);/*PINCE_ARG INTERMEDIAIRE*/
		}

			gotoStateAfter(STATE_22,40);
		if (onExit()) {  }
		break;
	// ___________________________
	case STATE_22 :
		if (onEntry()) {
			Application.m_asservissement.CommandeMouvementDistanceAngle(-55,-1.57);/*on recule un peu plus qu'avant*/
		}

			gotoStateIfConvergence(STATE_23,5000);
		if (onExit()) {  }
		break;
	// ___________________________
	case STATE_23 :
		if (onEntry()) {
			Application.m_servos.CommandePositionVitesse(6,1500,255);/*PINCE_ARD FERMEE*/
		}

			gotoStateAfter(STATE_24,200);
		if (onExit()) {  }
		break;
	// ___________________________
	case STATE_24 :
		if (onEntry()) {
			Application.m_servos.CommandePositionVitesse(2,1500,255);/*PINCE_ARG FERMEE*/
		}

			gotoStateAfter(STATE_25,200);
		if (onExit()) {  }
		break;
	// ___________________________
	case STATE_25 :
		if (onEntry()) {
			Application.m_servos.CommandePositionVitesse(1,2350,255);/*PINCE_PLANCHE REPOS*/
			Application.m_asservissement.CommandeMouvementDistanceAngle(0,1.57);/*on tourne avant de lever la planche*/
		}

			gotoStateIfConvergence(STATE_26,5000);
		if (onExit()) {  }
		break;
	// ___________________________
	case STATE_26 :
		if (onEntry()) {
			Application.m_asservissement.CommandeMouvementDistanceAngle(-55,1.57);/*on recule*/
			
			Application.m_ascenseur.up();

			
			Application.m_detection_obstacles.inhibeDetection(true);

		}

			gotoStateIfConvergence(STATE_27,5000);
		if (onExit()) {  }
		break;
	// ___________________________
	case STATE_27 :
		if (onEntry()) {
			Application.m_servos.CommandePositionVitesse(2,1300,255);/*PINCE_ARG INTERMEDIAIRE*/
		}

			gotoStateAfter(STATE_28,20);
		if (onExit()) {  }
		break;
	// ___________________________
	case STATE_28 :
		if (onEntry()) {
			Application.m_servos.CommandePositionVitesse(6,1300,255);/*PINCE_ARD INTERMEDIAIRE*/
		}

			gotoStateAfter(STATE_29,100);
		if (onExit()) {  }
		break;
	// ___________________________
	case STATE_29 :
		if (onEntry()) {
			Application.m_asservissement.CommandeMouvementDistanceAngle(30,1.57);/*on avance pour libérer l'empilement*/
		}

			gotoStateIfConvergence(STATE_30,5000);
		if (onExit()) {  }
		break;
	// ___________________________
	case STATE_30 :
		if (onEntry()) {
			
			Application.m_ascenseur.down();

		}

			gotoStateAfter(STATE_31,1500);
		if (onExit()) {  }
		break;
	// ___________________________
	case STATE_31 :
		if (onEntry()) {
			
			Application.m_detection_obstacles.inhibeDetection(false);

		}

			gotoStateAfter(FIN_MISSION, 4000);
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
