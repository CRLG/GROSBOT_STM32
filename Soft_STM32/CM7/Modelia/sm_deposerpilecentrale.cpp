/**
 * Generated 29_05_2025 at 07_59
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
		case JAUNE :		return "JAUNE";
		case BLEU :		return "BLEU";
		case NODE_1 :		return "NODE_1";
		case STATE_19 :		return "STATE_19";
		case STATE_20 :		return "STATE_20";
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
			outputs()->CommandeMouvementXY_TETA_sym(-7,80,1.57);/*on va prendre les colonnes au centre du terrain*/
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
			outputs()->CommandeMouvementXY_TETA_sym(-7,60,-1.57);/**/
		}

			gotoStateIfConvergence(STATE_11,5000);
		if (onExit()) {  }
		break;
	// ___________________________
	case STATE_11 :
		if (onEntry()) {
			outputs()->CommandeMouvementXY_TETA_sym(5,20,-1.57);/*on revient dans la zone de départ pour déposer le gradin*/
		}

			gotoStateIfConvergence(STATE_12,5000);
		if (onExit()) {  }
		break;
	// ___________________________
	case STATE_12 :
		if (onEntry()) {
			Application.m_servos.CommandePositionVitesse(1,1500,255);/*SERVO_PINCE_PLANCHE values=SERVO_PINCE_PLANCHE_OUVERTE*/
		}

			gotoStateAfter(STATE_13,2000);
		if (onExit()) {  }
		break;
	// ___________________________
	case STATE_13 :
		if (onEntry()) {
			Application.m_servos.CommandePositionVitesse(7,2000,255);/*SERVO_VERIN values=VERRIN_POSITION_HAUT*/
		}

			gotoStateAfter(STATE_14,3500);
		if (onExit()) {  }
		break;
	// ___________________________
	case STATE_14 :
		if (onEntry()) {
			Application.m_servos.CommandePositionVitesse(3,1150,255);/*SERVO_CAN_MOVER_INT values=SERVO_CAN_MOVER_INT_OFF*/
		}

			gotoStateAfter(STATE_15,200);
		if (onExit()) {  }
		break;
	// ___________________________
	case STATE_15 :
		if (onEntry()) {
			Application.m_servos.CommandePositionVitesse(4,1150,255);/*SERVO_CAN_MOVER_EXT values=SERVO_CAN_MOVER_EXT_OFF*/
			/*Ne rien mettre ici (cf doc Modélia)*/
		}

			gotoStateIfTrue(JAUNE,internals()->couleur_equipe == SM_DatasInterface::EQUIPE_COULEUR_1);
			gotoStateIfTrue(BLEU,internals()->couleur_equipe == SM_DatasInterface::EQUIPE_COULEUR_2);
		if (onExit()) {  /*Un seul lien vers un noeud: Ne rien mettre ici  (cf doc Modélia)*/  }
		break;
	// ___________________________
	case JAUNE :
		if (onEntry()) {
			Application.m_asservissement.CommandeMouvementDistanceAngle(-20,-1.57);/**/
		}

			gotoStateIfConvergence(NODE_1,5000);
		if (onExit()) {  /* Mettre ici le code du onExit de létat STATE_15 car un seul lien avant le noeud (cf doc Modélia)*/  }
		break;
	// ___________________________
	case BLEU :
		if (onEntry()) {
			Application.m_asservissement.CommandeMouvementDistanceAngle(-20,1.57);/**/
		}

			gotoStateIfConvergence(NODE_1,5000);
		if (onExit()) {  }
		break;
	// ___________________________
	case NODE_1 :
		if (onEntry()) {
			/*Ne rien mettre ici (cf doc Modélia)*/
			Application.m_servos.CommandePositionVitesse(3,1500,255);/*SERVO_CAN_MOVER_INT values=SERVO_CAN_MOVER_INT_ON*/
		}

			gotoStateAfter(STATE_19,400);
		if (onExit()) {  /*Ne rien mettre ici  (cf doc Modélia)*/  }
		break;
	// ___________________________
	case STATE_19 :
		if (onEntry()) {
			Application.m_servos.CommandePositionVitesse(4,1500,255);/*SERVO_CAN_MOVER_EXT values=SERVO_CAN_MOVER_EXT_ON*/
		}

			gotoStateAfter(STATE_20,400);
		if (onExit()) {  }
		break;
	// ___________________________
	case STATE_20 :
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
