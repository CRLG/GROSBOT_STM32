/**
* Built on 20260516_012004
*/

#include "sm_petitebordure.h"
#include "CGlobale.h"

SM_PetiteBordure::SM_PetiteBordure()
{
	m_main_mission_type = true;
	m_max_score = 0;
}

const char* SM_PetiteBordure::getName()
{
	return "SM_PetiteBordure";
}

const char* SM_PetiteBordure::stateToName(unsigned short state)
{
	switch(state)
	{
		case ETAT_1 :	return "ETAT_1";
		case ETAT_2 :	return "ETAT_2";
		case ETAT_3 :	return "ETAT_3";
		case ETAT_4 :	return "ETAT_4";
		case ETAT_5 :	return "ETAT_5";
		case ETAT_6 :	return "ETAT_6";
		case ETAT_7 :	return "ETAT_7";
		case ETAT_8 :	return "ETAT_8";
		case ETAT_9 :	return "ETAT_9";
		case ETAT_10 :	return "ETAT_10";
		case ETAT_11 :	return "ETAT_11";
		case ETAT_12 :	return "ETAT_12";
		case ETAT_13 :	return "ETAT_13";
		case ETAT_14 :	return "ETAT_14";
		case ETAT_15 :	return "ETAT_15";
		case ETAT_16 :	return "ETAT_16";
		case ETAT_17 :	return "ETAT_17";
		case ETAT_18 :	return "ETAT_18";
		case ETAT_19 :	return "ETAT_19";
		case ETAT_20 :	return "ETAT_20";

		case FIN_MISSION :	return "FIN_MISSION";
	}
	return "UNKNOWN_STATE";
}

// _____________________________________
void SM_PetiteBordure::step()
{
	switch (m_state)
	{
			
// _____________________________________

  case ETAT_1 :
  	if (onEntry()) {
  	  //Actions en entrée de l état
    	  outputs()->CommandeMouvementXY_TETA_sym(105 , -122 , 3.14002);

  	}
  	//Transitions vers les autres états
    	gotoStateIfConvergence(ETAT_2, 7000);
  	if (onExit()) {
  	  //TODO : pouvoir intégrer des actions en sortie d état
  	}
  	break;

  case ETAT_2 :
  	if (onEntry()) {
  	  //Actions en entrée de l état
    	  Application.m_servos.CommandePositionVitesse(5,1501,255);
    	  Application.m_servos.CommandePositionVitesse(6,1500,255);
  	}
  	//Transitions vers les autres états
    	gotoStateAfter(ETAT_3, 500);
  	if (onExit()) {
  	  //TODO : pouvoir intégrer des actions en sortie d état
  	}
  	break;

  case ETAT_3 :
  	if (onEntry()) {
  	  //Actions en entrée de l état
    	  outputs()->CommandeMouvementXY_TETA_sym(-2 , -142 , 3.14002);

  	}
  	//Transitions vers les autres états
    	gotoStateIfConvergence(ETAT_4, 7000);
  	if (onExit()) {
  	  //TODO : pouvoir intégrer des actions en sortie d état
  	}
  	break;

  case ETAT_4 :
  	if (onEntry()) {
  	  //Actions en entrée de l état
    	  Application.m_servos.CommandePositionVitesse(5,800,255);
    	  Application.m_servos.CommandePositionVitesse(6,2150,255);
  	}
  	//Transitions vers les autres états
    	gotoStateIfConvergence(ETAT_5, 1500);
  	if (onExit()) {
  	  //TODO : pouvoir intégrer des actions en sortie d état
  	}
  	break;

  case ETAT_5 :
  	if (onEntry()) {
  	  //Actions en entrée de l état
    	  outputs()->CommandeMouvementXY_TETA_sym(5 , -93 , 3.14002);

  	}
  	//Transitions vers les autres états
    	gotoStateIfConvergence(ETAT_6, 7000);
  	if (onExit()) {
  	  //TODO : pouvoir intégrer des actions en sortie d état
  	}
  	break;

  case ETAT_6 :
  	if (onEntry()) {
  	  //Actions en entrée de l état
    	  outputs()->CommandeMouvementXY_TETA_sym(-12 , -93 , 3.14002);

    	  Application.m_servos.CommandePositionVitesse(5,1501,255);
    	  Application.m_servos.CommandePositionVitesse(6,1500,255);
  	}
  	//Transitions vers les autres états
    	gotoStateIfConvergence(ETAT_7, 7000);
  	if (onExit()) {
  	  //TODO : pouvoir intégrer des actions en sortie d état
  	}
  	break;

  case ETAT_7 :
  	if (onEntry()) {
  	  //Actions en entrée de l état
    	  outputs()->CommandeMouvementXY_TETA_sym(11 , -93 , 3.14002);

    	  Application.m_servos.CommandePositionVitesse(5,511,255);
    	  Application.m_servos.CommandePositionVitesse(6,2500,255);
  	}
  	//Transitions vers les autres états
    	gotoStateIfConvergence(ETAT_8, 7000);
  	if (onExit()) {
  	  //TODO : pouvoir intégrer des actions en sortie d état
  	}
  	break;

  case ETAT_8 :
  	if (onEntry()) {
  	  //Actions en entrée de l état
    	  outputs()->CommandeMouvementXY_TETA_sym(-17 , -149 , -0.01902);

    	  Application.m_servos.CommandePositionVitesse(5,511,255);
    	  Application.m_servos.CommandePositionVitesse(6,2500,255);
  	}
  	//Transitions vers les autres états
    	gotoStateIfConvergence(ETAT_9, 7000);
  	if (onExit()) {
  	  //TODO : pouvoir intégrer des actions en sortie d état
  	}
  	break;

  case ETAT_9 :
  	if (onEntry()) {
  	  //Actions en entrée de l état
    	  outputs()->CommandeMouvementXY_TETA_sym(-30 , -149 , -0.01902);

    	  Application.m_servos.CommandePositionVitesse(7,1170,255);
  	}
  	//Transitions vers les autres états
    	gotoStateIfConvergence(ETAT_10, 7000);
  	if (onExit()) {
  	  //TODO : pouvoir intégrer des actions en sortie d état
  	}
  	break;

  case ETAT_10 :
  	if (onEntry()) {
  	  //Actions en entrée de l état
    	  outputs()->CommandeMouvementXY_TETA_sym(25 , -149 , -0.01902);

    	  Application.m_servos.CommandePositionVitesse(7,510,255);
  	}
  	//Transitions vers les autres états
    	gotoStateIfConvergence(ETAT_11, 7000);
  	if (onExit()) {
  	  //TODO : pouvoir intégrer des actions en sortie d état
  	}
  	break;

  case ETAT_11 :
  	if (onEntry()) {
  	  //Actions en entrée de l état
    // Pourquoi ?
    // Pour pousser les caisse noisettes dans la zone ?
    	  outputs()->CommandeMouvementXY_TETA_sym(91 , -149 , -0.01902);

  	}
  	//Transitions vers les autres états
    	gotoStateIfConvergence(ETAT_12, 7000);
  	if (onExit()) {
  	  //TODO : pouvoir intégrer des actions en sortie d état
  	}
  	break;

  case ETAT_12 :
  	if (onEntry()) {
  	  //Actions en entrée de l état
    	  outputs()->CommandeMouvementXY_TETA_sym(54 , -149 , -0.00157);

  	}
  	//Transitions vers les autres états
    	gotoStateIfConvergence(ETAT_13, 7000);
  	if (onExit()) {
  	  //TODO : pouvoir intégrer des actions en sortie d état
  	}
  	break;

  case ETAT_13 :
  	if (onEntry()) {
  	  //Actions en entrée de l état
    	  outputs()->CommandeMouvementXY_TETA_sym(12 , -53 , 3.14002);

  	}
  	//Transitions vers les autres états
    	gotoStateIfConvergence(ETAT_14, 7000);
  	if (onExit()) {
  	  //TODO : pouvoir intégrer des actions en sortie d état
  	}
  	break;

  case ETAT_14 :
  	if (onEntry()) {
  	  //Actions en entrée de l état
    	  outputs()->CommandeMouvementXY_TETA_sym(-8 , -53 , 3.14002);

    	  Application.m_servos.CommandePositionVitesse(5,850,255);
    	  Application.m_servos.CommandePositionVitesse(6,2100,255);
  	}
  	//Transitions vers les autres états
    	gotoStateIfConvergence(ETAT_15, 7000);
  	if (onExit()) {
  	  //TODO : pouvoir intégrer des actions en sortie d état
  	}
  	break;

  case ETAT_15 :
  	if (onEntry()) {
  	  //Actions en entrée de l état
    	  outputs()->CommandeMouvementXY_TETA_sym(84 , -53 , 1.56923);

  	}
  	//Transitions vers les autres états
    	gotoStateIfConvergence(ETAT_16, 7000);
  	if (onExit()) {
  	  //TODO : pouvoir intégrer des actions en sortie d état
  	}
  	break;

  case ETAT_16 :
  	if (onEntry()) {
  	  //Actions en entrée de l état
    	  outputs()->CommandeMouvementXY_TETA_sym(83 , -44 , 1.56923);

    	  Application.m_servos.CommandePositionVitesse(5,1500,255);
    	  Application.m_servos.CommandePositionVitesse(6,1500,255);
  	}
  	//Transitions vers les autres états
    	gotoStateIfConvergence(ETAT_17, 7000);
  	if (onExit()) {
  	  //TODO : pouvoir intégrer des actions en sortie d état
  	}
  	break;

  case ETAT_17 :
  	if (onEntry()) {
  	  //Actions en entrée de l état
    	  outputs()->CommandeMouvementXY_TETA_sym(83 , -60 , 1.56923);

    	  Application.m_servos.CommandePositionVitesse(5,511,255);
    	  Application.m_servos.CommandePositionVitesse(6,2500,255);
  	}
  	//Transitions vers les autres états
    	gotoStateIfConvergence(ETAT_18, 7000);
  	if (onExit()) {
  	  //TODO : pouvoir intégrer des actions en sortie d état
  	}
  	break;

  case ETAT_18 :
  	if (onEntry()) {
  	  //Actions en entrée de l état
    	  outputs()->CommandeMouvementXY_TETA_sym(36 , -42 , 3.10512);

  	}
  	//Transitions vers les autres états
    	gotoStateIfConvergence(ETAT_19, 7000);
  	if (onExit()) {
  	  //TODO : pouvoir intégrer des actions en sortie d état
  	}
  	break;

  case ETAT_19 :
  	if (onEntry()) {
  	  //Actions en entrée de l état
    	  outputs()->CommandeMouvementXY_TETA_sym(-8 , -41 , 1.56923);

  	}
  	//Transitions vers les autres états
    	gotoStateIfConvergence(ETAT_20, 7000);
  	if (onExit()) {
  	  //TODO : pouvoir intégrer des actions en sortie d état
  	}
  	break;

  case ETAT_20 :
  	if (onEntry()) {
  	  //Actions en entrée de l état
    // A voir comment optimiser les déplacments amonts
    // car en testant pas le temps d'arriver ici
    	  outputs()->CommandeMouvementXY_TETA_sym(-8 , -9 , 1.56923);

  	}
  	//Transitions vers les autres états
    	gotoStateIfConvergence(FIN_MISSION, 7000);
  	if (onExit()) {
  	  //TODO : pouvoir intégrer des actions en sortie d état
  	}
  	break;

// ___________________________
case FIN_MISSION :
		m_succes = true;
		m_score = m_max_score;
		stop();
		break;


	}
}
