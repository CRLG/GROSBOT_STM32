/**
 * Generated 29_05_2025 at 21_57
 */

#include "sm_deposerpilebasdepente.h"
#include "CGlobale.h"

SM_DeposerPileBasDePente::SM_DeposerPileBasDePente()
{
	m_main_mission_type = true;
	m_max_score = 0;
}

const char* SM_DeposerPileBasDePente::getName()
{
	return "SM_DeposerPileBasDePente";
}

const char* SM_DeposerPileBasDePente::stateToName(unsigned short state)
{
	switch(state)
	{
		case STATE_1 :		return "STATE_1";
		case STATE_2 :		return "STATE_2";
		case STATE_3 :		return "STATE_3";
		case STATE_4 :		return "STATE_4";
		case STATE_5 :		return "STATE_5";
		case STATE_6 :		return "STATE_6";
		case NODE_2 :		return "NODE_2";
		case JAUNE_1 :		return "JAUNE_1";
		case BLEU_1 :		return "BLEU_1";
		case NODE_3 :		return "NODE_3";
		case STATE_11 :		return "STATE_11";
		case STATE_12 :		return "STATE_12";
		case STATE_13 :		return "STATE_13";
		case STATE_14 :		return "STATE_14";
		case STATE_15 :		return "STATE_15";
		case JAUNE_2 :		return "JAUNE_2";
		case BLEU_2 :		return "BLEU_2";
		case NODE_5 :		return "NODE_5";
		case STATE_19 :		return "STATE_19";
		case STATE_20 :		return "STATE_20";
		case FIN_MISSION :	return "FIN_MISSION";
	}
	return "UNKNOWN_STATE";
}

// _____________________________________
void SM_DeposerPileBasDePente::step()
{
	switch (m_state)
	{

	// ___________________________
	case STATE_1 :
		if (onEntry()) {
			outputs()->CommandeMouvementXY_TETA_sym(-32,125,1.57);/*valeur x mesurée en réelle avec la dérive*/
		}

			gotoStateIfConvergence(STATE_2,8000);
		if (onExit()) {  }
		break;
	// ___________________________
	case STATE_2 :
		if (onEntry()) {
			
			Application.m_detection_obstacles.inhibeDetection(true);

			outputs()->CommandeMouvementXY_TETA_sym(-32,145,1.57);/*valeur x mesurée en réelle avec la dérive*/
		}

			gotoStateIfConvergence(STATE_3,7000);
		if (onExit()) {  }
		break;
	// ___________________________
	case STATE_3 :
		if (onEntry()) {
			Application.m_servos.CommandePositionVitesse(1,1500,255);/*SERVO_PINCE_PLANCHE values=SERVO_PINCE_PLANCHE_OUVERTE*/
			Application.m_asservissement.CommandeManuelle(7,7);/**/
		}

			gotoStateAfter(STATE_4,2000);
		if (onExit()) {  }
		break;
	// ___________________________
	case STATE_4 :
		if (onEntry()) {
			Application.m_asservissement.CommandeManuelle(0,0);/**/
		}

			gotoStateAfter(STATE_5,1000);
		if (onExit()) {  }
		break;
	// ___________________________
	case STATE_5 :
		if (onEntry()) {
			Application.m_servos.CommandePositionVitesse(7,1000,255);/*SERVO_VERIN values=VERRIN_POSITION_BAS*/
		}

			gotoStateAfter(STATE_6,2000);
		if (onExit()) {  }
		break;
	// ___________________________
	case STATE_6 :
		if (onEntry()) {
			Application.m_servos.CommandePositionVitesse(1,2450,255);/*SERVO_PINCE_PLANCHE values=SERVO_PINCE_PLANCHE_FERMEE*/
		}

			gotoStateAfter(NODE_2,1000);
		if (onExit()) {  /*Un seul lien vers un noeud: Ne rien mettre ici  (cf doc Modélia)*/  }
		break;
	// ___________________________
	case NODE_2 :
		if (onEntry()) {
			/*Ne rien mettre ici (cf doc Modélia)*/
		}

			gotoStateIfTrue(JAUNE_1,internals()->couleur_equipe == SM_DatasInterface::EQUIPE_COULEUR_1);
			gotoStateIfTrue(BLEU_1,internals()->couleur_equipe == SM_DatasInterface::EQUIPE_COULEUR_2);
		if (onExit()) {  /* Mettre ici le code du onExit de létat STATE_6 car un seul lien avant le noeud (cf doc Modélia)*/  }
		break;
	// ___________________________
	case JAUNE_1 :
		if (onEntry()) {
			Application.m_asservissement.CommandeMouvementDistanceAngle(-42,1.57);/**/
		}

			gotoStateIfConvergence(NODE_3,5000);
		if (onExit()) {  }
		break;
	// ___________________________
	case BLEU_1 :
		if (onEntry()) {
			Application.m_asservissement.CommandeMouvementDistanceAngle(-42,-1.57);/**/
		}

			gotoStateIfConvergence(NODE_3,5000);
		if (onExit()) {  }
		break;
	// ___________________________
	case NODE_3 :
		if (onEntry()) {
			/*Ne rien mettre ici (cf doc Modélia)*/
			
			Application.m_detection_obstacles.inhibeDetection(false);

			outputs()->CommandeMouvementXY_TETA_sym(6,44,-1.57);/**/
		}

			gotoStateIfConvergence(STATE_11,5000);
		if (onExit()) {  /*Ne rien mettre ici  (cf doc Modélia)*/  }
		break;
	// ___________________________
	case STATE_11 :
		if (onEntry()) {
			outputs()->CommandeMouvementXY_TETA_sym(6,38,-1.57);/*on revient dans la zone de départ pour déposer le gradin*/
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

			gotoStateIfTrue(JAUNE_2,internals()->couleur_equipe == SM_DatasInterface::EQUIPE_COULEUR_1);
			gotoStateIfTrue(BLEU_2,internals()->couleur_equipe == SM_DatasInterface::EQUIPE_COULEUR_2);
		if (onExit()) {  /*Un seul lien vers un noeud: Ne rien mettre ici  (cf doc Modélia)*/  }
		break;
	// ___________________________
	case JAUNE_2 :
		if (onEntry()) {
			Application.m_asservissement.CommandeMouvementDistanceAngle(-20,-1.57);/**/
		}

			gotoStateIfConvergence(NODE_5,5000);
		if (onExit()) {  /* Mettre ici le code du onExit de létat STATE_15 car un seul lien avant le noeud (cf doc Modélia)*/  }
		break;
	// ___________________________
	case BLEU_2 :
		if (onEntry()) {
			Application.m_asservissement.CommandeMouvementDistanceAngle(-20,1.57);/**/
		}

			gotoStateIfConvergence(NODE_5,5000);
		if (onExit()) {  }
		break;
	// ___________________________
	case NODE_5 :
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
