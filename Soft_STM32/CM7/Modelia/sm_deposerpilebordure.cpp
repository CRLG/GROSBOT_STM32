/**
 * Generated 29_05_2025 at 08_25
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
		case STATE_2 :		return "STATE_2";
		case STATE_3 :		return "STATE_3";
		case STATE_4 :		return "STATE_4";
		case JAUNE :		return "JAUNE";
		case BLEU :		return "BLEU";
		case NODE_1 :		return "NODE_1";
		case STATE_8 :		return "STATE_8";
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
			outputs()->CommandeMouvementXY_TETA_sym(-39,40,-1.57);/*On se place face aux éléments de jeux*/
		}

			gotoStateIfConvergence(STATE_2,5000);
		if (onExit()) {  }
		break;
	// ___________________________
	case STATE_2 :
		if (onEntry()) {
			outputs()->CommandeMouvementXY_TETA_sym(-39,8,-1.57);/**/
		}

			gotoStateIfConvergence(STATE_3,5000);
		if (onExit()) {  }
		break;
	// ___________________________
	case STATE_3 :
		if (onEntry()) {
			Application.m_servos.CommandePositionVitesse(3,1150,255);/*SERVO_CAN_MOVER_INT values=SERVO_CAN_MOVER_INT_OFF*/
		}

			gotoStateAfter(STATE_4,200);
		if (onExit()) {  }
		break;
	// ___________________________
	case STATE_4 :
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
		if (onExit()) {  /* Mettre ici le code du onExit de létat STATE_4 car un seul lien avant le noeud (cf doc Modélia)*/  }
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

			gotoStateAfter(STATE_8,400);
		if (onExit()) {  /*Ne rien mettre ici  (cf doc Modélia)*/  }
		break;
	// ___________________________
	case STATE_8 :
		if (onEntry()) {
			Application.m_servos.CommandePositionVitesse(4,1500,255);/*SERVO_CAN_MOVER_EXT values=SERVO_CAN_MOVER_EXT_ON*/
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
