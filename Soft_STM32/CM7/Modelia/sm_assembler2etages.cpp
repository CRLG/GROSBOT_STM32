/**
 * Generated 30_05_2025 at 15_28
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
		case COULEUR_01_DEBUT :		return "COULEUR_01_DEBUT";
		case JAUNE_01 :		return "JAUNE_01";
		case STATE_12 :		return "STATE_12";
		case BLEU_01 :		return "BLEU_01";
		case STATE_14 :		return "STATE_14";
		case COULEUR_01_FIN :		return "COULEUR_01_FIN";
		case STATE_16 :		return "STATE_16";
		case STATE_17 :		return "STATE_17";
		case STATE_18 :		return "STATE_18";
		case COULEUR_02_DEBUT :		return "COULEUR_02_DEBUT";
		case JAUNE_02 :		return "JAUNE_02";
		case STATE_21 :		return "STATE_21";
		case STATE_22 :		return "STATE_22";
		case BLEU_02 :		return "BLEU_02";
		case STATE_24 :		return "STATE_24";
		case STATE_25 :		return "STATE_25";
		case COULEUR_02_FIN :		return "COULEUR_02_FIN";
		case STATE_27 :		return "STATE_27";
		case STATE_28 :		return "STATE_28";
		case COULEUR_03_DEBUT :		return "COULEUR_03_DEBUT";
		case JAUNE_03 :		return "JAUNE_03";
		case BLEU_03 :		return "BLEU_03";
		case COULEUR_03_FIN :		return "COULEUR_03_FIN";
		case STATE_33 :		return "STATE_33";
		case STATE_34 :		return "STATE_34";
		case JAUNE_04 :		return "JAUNE_04";
		case STATE_36 :		return "STATE_36";
		case BLEU_04 :		return "BLEU_04";
		case STATE_38 :		return "STATE_38";
		case COULEUR_04_FIN :		return "COULEUR_04_FIN";
		case STATE_40 :		return "STATE_40";
		case COULEUR_05_DEBUT :		return "COULEUR_05_DEBUT";
		case JAUNE_05 :		return "JAUNE_05";
		case BLEU_05 :		return "BLEU_05";
		case COULEUR_05_FIN :		return "COULEUR_05_FIN";
		case STATE_45 :		return "STATE_45";
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

			gotoStateAfter(COULEUR_01_DEBUT,2000);
		if (onExit()) {  /*Un seul lien vers un noeud: Ne rien mettre ici  (cf doc Modélia)*/  }
		break;
	// ___________________________
	case COULEUR_01_DEBUT :
		if (onEntry()) {
			/*Ne rien mettre ici (cf doc Modélia)*/
		}

			gotoStateIfTrue(JAUNE_01,internals()->couleur_equipe == SM_DatasInterface::EQUIPE_COULEUR_1);
			gotoStateIfTrue(BLEU_01,internals()->couleur_equipe == SM_DatasInterface::EQUIPE_COULEUR_2);
		if (onExit()) {  /* Mettre ici le code du onExit de létat STATE_9 car un seul lien avant le noeud (cf doc Modélia)*/  }
		break;
	// ___________________________
	case JAUNE_01 :
		if (onEntry()) {
			Application.m_asservissement.CommandeMouvementDistanceAngle(-50,-1.57);/*on recule, suffisamment pour faire les manoeuvre après*/
		}

			gotoStateIfConvergence(STATE_12,5000);
		if (onExit()) {  }
		break;
	// ___________________________
	case STATE_12 :
		if (onEntry()) {
			Application.m_asservissement.CommandeMouvementDistanceAngle(0,1.57);/*on tourne*/
		}

			gotoStateIfConvergence(COULEUR_01_FIN,5000);
		if (onExit()) {  }
		break;
	// ___________________________
	case BLEU_01 :
		if (onEntry()) {
			Application.m_asservissement.CommandeMouvementDistanceAngle(-50,1.57);/**/
		}

			gotoStateIfConvergence(STATE_14,5000);
		if (onExit()) {  }
		break;
	// ___________________________
	case STATE_14 :
		if (onEntry()) {
			Application.m_asservissement.CommandeMouvementDistanceAngle(0,-1.57);/**/
		}

			gotoStateIfConvergence(COULEUR_01_FIN,5000);
		if (onExit()) {  }
		break;
	// ___________________________
	case COULEUR_01_FIN :
		if (onEntry()) {
			/*Ne rien mettre ici (cf doc Modélia)*/
			Application.m_servos.CommandePositionVitesse(1,1500,255);/*PINCE_PLANCHE OUVERTE*/
		}

			gotoStateAfter(STATE_16,500);
		if (onExit()) {  /*Ne rien mettre ici  (cf doc Modélia)*/  }
		break;
	// ___________________________
	case STATE_16 :
		if (onEntry()) {
			Application.m_servos.CommandePositionVitesse(3,1150,255);/*CAN_MOVER_INT OFF*/
		}

			gotoStateAfter(STATE_17,350);
		if (onExit()) {  }
		break;
	// ___________________________
	case STATE_17 :
		if (onEntry()) {
			Application.m_servos.CommandePositionVitesse(1,2450,255);/*PINCE_PLANCHE FERMEE*/
		}

			gotoStateAfter(STATE_18,500);
		if (onExit()) {  }
		break;
	// ___________________________
	case STATE_18 :
		if (onEntry()) {
			Application.m_servos.CommandePositionVitesse(7,2000,255);/*VERIN POSITION_HAUT*/
		}

			gotoStateAfter(COULEUR_02_DEBUT,500);
		if (onExit()) {  /*Un seul lien vers un noeud: Ne rien mettre ici  (cf doc Modélia)*/  }
		break;
	// ___________________________
	case COULEUR_02_DEBUT :
		if (onEntry()) {
			/*Ne rien mettre ici (cf doc Modélia)*/
		}

			gotoStateIfTrue(JAUNE_02,internals()->couleur_equipe == SM_DatasInterface::EQUIPE_COULEUR_1);
			gotoStateIfTrue(BLEU_02,internals()->couleur_equipe == SM_DatasInterface::EQUIPE_COULEUR_2);
		if (onExit()) {  /* Mettre ici le code du onExit de létat STATE_18 car un seul lien avant le noeud (cf doc Modélia)*/  }
		break;
	// ___________________________
	case JAUNE_02 :
		if (onEntry()) {
			Application.m_asservissement.CommandeMouvementDistanceAngle(-25,1.57);/*on recule avec le bon angle et à mi-distance pour pouvoir tourner sans tout défoncer*/
		}

			gotoStateIfConvergence(STATE_21,5000);
		if (onExit()) {  }
		break;
	// ___________________________
	case STATE_21 :
		if (onEntry()) {
			Application.m_asservissement.CommandeMouvementDistanceAngle(0,-1.57);/*on tourne*/
		}

			gotoStateIfConvergence(STATE_22,5000);
		if (onExit()) {  }
		break;
	// ___________________________
	case STATE_22 :
		if (onEntry()) {
			Application.m_servos.CommandePositionVitesse(7,1590,255);/*VERIN POSITION_INTERMEDIARE*/
			Application.m_asservissement.CommandeMouvementDistanceAngle(25,-1.57);/*on avance avec le bon angle*/
		}

			gotoStateIfConvergence(COULEUR_02_FIN,5000);
		if (onExit()) {  }
		break;
	// ___________________________
	case BLEU_02 :
		if (onEntry()) {
			Application.m_asservissement.CommandeMouvementDistanceAngle(-25,-1.57);/*on recule avec le bon angle et à mi-distance pour pouvoir tourner sans tout défoncer*/
		}

			gotoStateIfConvergence(STATE_24,5000);
		if (onExit()) {  }
		break;
	// ___________________________
	case STATE_24 :
		if (onEntry()) {
			Application.m_asservissement.CommandeMouvementDistanceAngle(0,1.57);/*on tourne*/
		}

			gotoStateIfConvergence(STATE_25,5000);
		if (onExit()) {  }
		break;
	// ___________________________
	case STATE_25 :
		if (onEntry()) {
			Application.m_servos.CommandePositionVitesse(7,1590,255);/*VERIN POSITION_INTERMEDIARE*/
			Application.m_asservissement.CommandeMouvementDistanceAngle(25,1.57);/*on avance avec le bon angle*/
		}

			gotoStateIfConvergence(COULEUR_02_FIN,5000);
		if (onExit()) {  }
		break;
	// ___________________________
	case COULEUR_02_FIN :
		if (onEntry()) {
			/*Ne rien mettre ici (cf doc Modélia)*/
			Application.m_servos.CommandePositionVitesse(1,1500,255);/*PINCE_PLANCHE OUVERTE*/
		}

			gotoStateAfter(STATE_27,100);
		if (onExit()) {  /*Ne rien mettre ici  (cf doc Modélia)*/  }
		break;
	// ___________________________
	case STATE_27 :
		if (onEntry()) {
			Application.m_servos.CommandePositionVitesse(6,1300,255);/*PINCE_ARD INTERMEDIAIRE*/
		}

			gotoStateAfter(STATE_28,40);
		if (onExit()) {  }
		break;
	// ___________________________
	case STATE_28 :
		if (onEntry()) {
			Application.m_servos.CommandePositionVitesse(2,1300,255);/*PINCE_ARG INTERMEDIAIRE*/
		}

			gotoStateAfter(COULEUR_03_DEBUT,40);
		if (onExit()) {  /*Un seul lien vers un noeud: Ne rien mettre ici  (cf doc Modélia)*/  }
		break;
	// ___________________________
	case COULEUR_03_DEBUT :
		if (onEntry()) {
			/*Ne rien mettre ici (cf doc Modélia)*/
		}

			gotoStateIfTrue(JAUNE_03,internals()->couleur_equipe == SM_DatasInterface::EQUIPE_COULEUR_1);
			gotoStateIfTrue(BLEU_03,internals()->couleur_equipe == SM_DatasInterface::EQUIPE_COULEUR_2);
		if (onExit()) {  /* Mettre ici le code du onExit de létat STATE_28 car un seul lien avant le noeud (cf doc Modélia)*/  }
		break;
	// ___________________________
	case JAUNE_03 :
		if (onEntry()) {
			Application.m_asservissement.CommandeMouvementDistanceAngle(-55,-1.57);/*on recule un peu plus qu'avant*/
		}

			gotoStateIfConvergence(COULEUR_03_FIN,5000);
		if (onExit()) {  }
		break;
	// ___________________________
	case BLEU_03 :
		if (onEntry()) {
			Application.m_asservissement.CommandeMouvementDistanceAngle(-55,1.57);/**/
		}

			gotoStateIfConvergence(COULEUR_03_FIN,5000);
		if (onExit()) {  }
		break;
	// ___________________________
	case COULEUR_03_FIN :
		if (onEntry()) {
			/*Ne rien mettre ici (cf doc Modélia)*/
			Application.m_servos.CommandePositionVitesse(6,1500,255);/*PINCE_ARD FERMEE*/
		}

			gotoStateAfter(STATE_33,200);
		if (onExit()) {  /*Ne rien mettre ici  (cf doc Modélia)*/  }
		break;
	// ___________________________
	case STATE_33 :
		if (onEntry()) {
			Application.m_servos.CommandePositionVitesse(2,1500,255);/*PINCE_ARG FERMEE*/
		}

			gotoStateAfter(STATE_34,200);
		if (onExit()) {  }
		break;
	// ___________________________
	case STATE_34 :
		if (onEntry()) {
			Application.m_servos.CommandePositionVitesse(1,2350,255);/*PINCE_PLANCHE REPOS*/
			/*Ne rien mettre ici (cf doc Modélia)*/
		}

			gotoStateIfTrue(JAUNE_04,internals()->couleur_equipe == SM_DatasInterface::EQUIPE_COULEUR_1);
			gotoStateIfTrue(BLEU_04,internals()->couleur_equipe == SM_DatasInterface::EQUIPE_COULEUR_2);
		if (onExit()) {  /*Un seul lien vers un noeud: Ne rien mettre ici  (cf doc Modélia)*/  }
		break;
	// ___________________________
	case JAUNE_04 :
		if (onEntry()) {
			Application.m_asservissement.CommandeMouvementDistanceAngle(0,1.57);/*on tourne avant de lever la planche*/
		}

			gotoStateIfConvergence(STATE_36,5000);
		if (onExit()) {  /* Mettre ici le code du onExit de létat STATE_34 car un seul lien avant le noeud (cf doc Modélia)*/  }
		break;
	// ___________________________
	case STATE_36 :
		if (onEntry()) {
			Application.m_asservissement.CommandeMouvementDistanceAngle(-55,1.57);/*on recule*/
			
			Application.m_ascenseur.up();

			
			Application.m_detection_obstacles.inhibeDetection(true);

		}

			gotoStateIfConvergence(COULEUR_04_FIN,5000);
		if (onExit()) {  }
		break;
	// ___________________________
	case BLEU_04 :
		if (onEntry()) {
			Application.m_asservissement.CommandeMouvementDistanceAngle(0,-1.57);/**/
		}

			gotoStateIfConvergence(STATE_38,5000);
		if (onExit()) {  }
		break;
	// ___________________________
	case STATE_38 :
		if (onEntry()) {
			Application.m_asservissement.CommandeMouvementDistanceAngle(-55,-1.57);/*on recule*/
			
			Application.m_ascenseur.up();

			
			Application.m_detection_obstacles.inhibeDetection(true);

		}

			gotoStateIfConvergence(COULEUR_04_FIN,5000);
		if (onExit()) {  }
		break;
	// ___________________________
	case COULEUR_04_FIN :
		if (onEntry()) {
			/*Ne rien mettre ici (cf doc Modélia)*/
			Application.m_servos.CommandePositionVitesse(2,1300,255);/*PINCE_ARG INTERMEDIAIRE*/
		}

			gotoStateAfter(STATE_40,20);
		if (onExit()) {  /*Ne rien mettre ici  (cf doc Modélia)*/  }
		break;
	// ___________________________
	case STATE_40 :
		if (onEntry()) {
			Application.m_servos.CommandePositionVitesse(6,1300,255);/*PINCE_ARD INTERMEDIAIRE*/
		}

			gotoStateAfter(COULEUR_05_DEBUT,100);
		if (onExit()) {  /*Un seul lien vers un noeud: Ne rien mettre ici  (cf doc Modélia)*/  }
		break;
	// ___________________________
	case COULEUR_05_DEBUT :
		if (onEntry()) {
			/*Ne rien mettre ici (cf doc Modélia)*/
		}

			gotoStateIfTrue(JAUNE_05,internals()->couleur_equipe == SM_DatasInterface::EQUIPE_COULEUR_1);
			gotoStateIfTrue(BLEU_05,internals()->couleur_equipe == SM_DatasInterface::EQUIPE_COULEUR_2);
		if (onExit()) {  /* Mettre ici le code du onExit de létat STATE_40 car un seul lien avant le noeud (cf doc Modélia)*/  }
		break;
	// ___________________________
	case JAUNE_05 :
		if (onEntry()) {
			Application.m_asservissement.CommandeMouvementDistanceAngle(30,1.57);/*on avance pour libérer l'empilement*/
		}

			gotoStateIfConvergence(COULEUR_05_FIN,5000);
		if (onExit()) {  }
		break;
	// ___________________________
	case BLEU_05 :
		if (onEntry()) {
			Application.m_asservissement.CommandeMouvementDistanceAngle(30,-1.57);/**/
		}

			gotoStateIfConvergence(COULEUR_05_FIN,5000);
		if (onExit()) {  }
		break;
	// ___________________________
	case COULEUR_05_FIN :
		if (onEntry()) {
			/*Ne rien mettre ici (cf doc Modélia)*/
			
			Application.m_ascenseur.down();

		}

			gotoStateAfter(STATE_45,1500);
		if (onExit()) {  /*Ne rien mettre ici  (cf doc Modélia)*/  }
		break;
	// ___________________________
	case STATE_45 :
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
