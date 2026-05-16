/**
* Built on 20260516_094629
*/

#include "sm_curseur.h"
#include "CGlobale.h"

SM_Curseur::SM_Curseur()
{
	m_main_mission_type = true;
	m_max_score = 0;
}

const char* SM_Curseur::getName()
{
	return "SM_Curseur";
}

const char* SM_Curseur::stateToName(unsigned short state)
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
		case ETAT_21 :	return "ETAT_21";
		case ETAT_22 :	return "ETAT_22";
		case ETAT_23 :	return "ETAT_23";
		case ETAT_24 :	return "ETAT_24";
		case ETAT_25 :	return "ETAT_25";
		case ETAT_26 :	return "ETAT_26";
		case ETAT_27 :	return "ETAT_27";
		case ETAT_28 :	return "ETAT_28";
		case ETAT_29 :	return "ETAT_29";
		case ETAT_30 :	return "ETAT_30";
		case ETAT_31 :	return "ETAT_31";
		case ETAT_32 :	return "ETAT_32";
		case ETAT_33 :	return "ETAT_33";
		case ETAT_34 :	return "ETAT_34";
		case ETAT_35 :	return "ETAT_35";
		case ETAT_36 :	return "ETAT_36";
		case ETAT_37 :	return "ETAT_37";

		case FIN_MISSION :	return "FIN_MISSION";
	}
	return "UNKNOWN_STATE";
}

// _____________________________________
void SM_Curseur::step()
{
	switch (m_state)
	{
			
// _____________________________________

  case ETAT_1 :
  	if (onEntry()) {
  	  //Actions en entrée de l état
    	  outputs()->CommandeMouvementXY_TETA_sym(0 , 0 , -1.56992);

  	}
  	//Transitions vers les autres états
    	gotoStateIfConvergence(ETAT_2, 7000);
  	if (onExit()) {
  	  //TODO : pouvoir intégrer des actions en sortie d état
  	}
  	break;
  // Avance un peu pour éviter la bordure

  case ETAT_2 :
  	if (onEntry()) {
  	  //Actions en entrée de l état
    	  outputs()->CommandeMouvementXY_TETA_sym(0 , -40 , -1.56992);

  	}
  	//Transitions vers les autres états
    	gotoStateIfConvergenceRapide(ETAT_3, 3000);
  	if (onExit()) {
  	  //TODO : pouvoir intégrer des actions en sortie d état
  	}
  	break;

  case ETAT_3 :
  	if (onEntry()) {
  	  //Actions en entrée de l état
    	  outputs()->CommandeMouvementXY_TETA_sym(30 , -122 , 0);

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
    	  outputs()->CommandeMouvementXY_TETA_sym(110 , -122 , 1.56992);

  	}
  	//Transitions vers les autres états
    	gotoStateIfConvergence(ETAT_5, 7000);
  	if (onExit()) {
  	  //TODO : pouvoir intégrer des actions en sortie d état
  	}
  	break;

  case ETAT_5 :
  	if (onEntry()) {
  	  //Actions en entrée de l état
    	  outputs()->CommandeMouvementXY_TETA_sym(110 , -91 , -3.14002);

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
    	  outputs()->CommandeMouvementXY_TETA_sym(57 , -91 , -3.14002);

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
    	  outputs()->CommandeMouvementXY_TETA_sym(110 , -91 , 0);

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
    	  outputs()->CommandeMouvementXY_TETA_sym(155 , -91 , 0);

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
    	  outputs()->CommandeMouvementXY_TETA_sym(105 , -91 , 0);

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
    	  outputs()->CommandeMouvementXY_TETA_sym(70 , -91 , -1.57);

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
    	  Application.m_servos.CommandePositionVitesse(5,1501,255);
    	  Application.m_servos.CommandePositionVitesse(6,1500,255);
  	}
  	//Transitions vers les autres états
    	gotoStateAfter(ETAT_12, 500);
  	if (onExit()) {
  	  //TODO : pouvoir intégrer des actions en sortie d état
  	}
  	break;

  case ETAT_12 :
  	if (onEntry()) {
  	  //Actions en entrée de l état
    	  outputs()->CommandeMouvementXY_TETA_sym(68 , -137 , -1.57);

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
    	  Application.m_servos.CommandePositionVitesse(5,800,255);
    	  Application.m_servos.CommandePositionVitesse(6,2150,255);
  	}
  	//Transitions vers les autres états
    	gotoStateIfConvergence(ETAT_14, 1500);
  	if (onExit()) {
  	  //TODO : pouvoir intégrer des actions en sortie d état
  	}
  	break;

  case ETAT_14 :
  	if (onEntry()) {
  	  //Actions en entrée de l état
    	  outputs()->CommandeMouvementXY_TETA_sym(92 , -104 , 0.98);

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
    	  Application.m_servos.CommandePositionVitesse(5,1501,255);
    	  Application.m_servos.CommandePositionVitesse(6,1500,255);
  	}
  	//Transitions vers les autres états
    	gotoStateAfter(ETAT_16, 500);
  	if (onExit()) {
  	  //TODO : pouvoir intégrer des actions en sortie d état
  	}
  	break;

  case ETAT_16 :
  	if (onEntry()) {
  	  //Actions en entrée de l état
    	  Application.m_asservissement.CommandeMouvementDistanceAngle(-40 , -0.98);

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
    	  Application.m_servos.CommandePositionVitesse(5,480,255);
    	  Application.m_servos.CommandePositionVitesse(6,2500,255);
  	}
  	//Transitions vers les autres états
    	gotoStateIfConvergence(ETAT_18, 500);
  	if (onExit()) {
  	  //TODO : pouvoir intégrer des actions en sortie d état
  	}
  	break;

  case ETAT_18 :
  	if (onEntry()) {
  	  //Actions en entrée de l état
    	  Application.m_asservissement.CommandeMouvementDistanceAngle(0 , -2.4);

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
    	  Application.m_asservissement.CommandeMouvementDistanceAngle(-18 , -2.4);

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
    	  Application.m_asservissement.CommandeMouvementDistanceAngle(0 , -3.141516);

  	}
  	//Transitions vers les autres états
    	gotoStateIfConvergence(ETAT_21, 7000);
  	if (onExit()) {
  	  //TODO : pouvoir intégrer des actions en sortie d état
  	}
  	break;

  case ETAT_21 :
  	if (onEntry()) {
  	  //Actions en entrée de l état
    	  Application.m_servos.CommandePositionVitesse(7,1170,255);
  	}
  	//Transitions vers les autres états
    	gotoStateIfConvergence(ETAT_22, 1000);
  	if (onExit()) {
  	  //TODO : pouvoir intégrer des actions en sortie d état
  	}
  	break;

  case ETAT_22 :
  	if (onEntry()) {
  	  //Actions en entrée de l état
    	  Application.m_asservissement.CommandeMouvementDistanceAngle(55 , -3.141516);

  	}
  	//Transitions vers les autres états
    	gotoStateIfConvergence(ETAT_23, 7000);
  	if (onExit()) {
  	  //TODO : pouvoir intégrer des actions en sortie d état
  	}
  	break;

  case ETAT_23 :
  	if (onEntry()) {
  	  //Actions en entrée de l état
    	  Application.m_servos.CommandePositionVitesse(7,512,255);
  	}
  	//Transitions vers les autres états
    	gotoStateAfter(ETAT_24, 1500);
  	if (onExit()) {
  	  //TODO : pouvoir intégrer des actions en sortie d état
  	}
  	break;

  case ETAT_24 :
  	if (onEntry()) {
  	  //Actions en entrée de l état
    	  Application.m_asservissement.CommandeMouvementDistanceAngle(0 , -1.57);

  	}
  	//Transitions vers les autres états
    	gotoStateIfConvergence(ETAT_25, 7000);
  	if (onExit()) {
  	  //TODO : pouvoir intégrer des actions en sortie d état
  	}
  	break;

  case ETAT_25 :
  	if (onEntry()) {
  	  //Actions en entrée de l état
    	  outputs()->CommandeMouvementXY_TETA_sym(28 , -133 , 3.14);

  	}
  	//Transitions vers les autres états
    	gotoStateIfConvergence(ETAT_26, 7000);
  	if (onExit()) {
  	  //TODO : pouvoir intégrer des actions en sortie d état
  	}
  	break;

  case ETAT_26 :
  	if (onEntry()) {
  	  //Actions en entrée de l état
    	  Application.m_servos.CommandePositionVitesse(5,1501,255);
    	  Application.m_servos.CommandePositionVitesse(6,1500,255);
  	}
  	//Transitions vers les autres états
    	gotoStateIfConvergence(ETAT_27, 500);
  	if (onExit()) {
  	  //TODO : pouvoir intégrer des actions en sortie d état
  	}
  	break;

  case ETAT_27 :
  	if (onEntry()) {
  	  //Actions en entrée de l état
    	  outputs()->CommandeMouvementXY_TETA_sym(-10 , -133 , 3.14);

  	}
  	//Transitions vers les autres états
    	gotoStateIfConvergence(ETAT_28, 7000);
  	if (onExit()) {
  	  //TODO : pouvoir intégrer des actions en sortie d état
  	}
  	break;

  case ETAT_28 :
  	if (onEntry()) {
  	  //Actions en entrée de l état
    	  Application.m_servos.CommandePositionVitesse(5,800,255);
    	  Application.m_servos.CommandePositionVitesse(6,2150,255);
  	}
  	//Transitions vers les autres états
    	gotoStateIfConvergence(ETAT_29, 500);
  	if (onExit()) {
  	  //TODO : pouvoir intégrer des actions en sortie d état
  	}
  	break;

  case ETAT_29 :
  	if (onEntry()) {
  	  //Actions en entrée de l état
    	  outputs()->CommandeMouvementXY_TETA_sym(-10 , -92 , 3.14);

  	}
  	//Transitions vers les autres états
    	gotoStateIfConvergence(ETAT_30, 7000);
  	if (onExit()) {
  	  //TODO : pouvoir intégrer des actions en sortie d état
  	}
  	break;

  case ETAT_30 :
  	if (onEntry()) {
  	  //Actions en entrée de l état
    	  Application.m_servos.CommandePositionVitesse(5,1501,255);
    	  Application.m_servos.CommandePositionVitesse(6,1500,255);
  	}
  	//Transitions vers les autres états
    	gotoStateIfConvergence(ETAT_31, 500);
  	if (onExit()) {
  	  //TODO : pouvoir intégrer des actions en sortie d état
  	}
  	break;

  case ETAT_31 :
  	if (onEntry()) {
  	  //Actions en entrée de l état
    	  outputs()->CommandeMouvementXY_TETA_sym(6 , -92 , 3.14);

  	}
  	//Transitions vers les autres états
    	gotoStateIfConvergence(ETAT_32, 7000);
  	if (onExit()) {
  	  //TODO : pouvoir intégrer des actions en sortie d état
  	}
  	break;

  case ETAT_32 :
  	if (onEntry()) {
  	  //Actions en entrée de l état
    	  Application.m_servos.CommandePositionVitesse(5,480,255);
    	  Application.m_servos.CommandePositionVitesse(6,2500,255);
  	}
  	//Transitions vers les autres états
    	gotoStateIfConvergence(ETAT_33, 500);
  	if (onExit()) {
  	  //TODO : pouvoir intégrer des actions en sortie d état
  	}
  	break;

  case ETAT_33 :
  	if (onEntry()) {
  	  //Actions en entrée de l état
    	  outputs()->CommandeMouvementXY_TETA_sym(7 , -70 , 1.57);

  	}
  	//Transitions vers les autres états
    	gotoStateIfConvergence(ETAT_34, 7000);
  	if (onExit()) {
  	  //TODO : pouvoir intégrer des actions en sortie d état
  	}
  	break;

  case ETAT_34 :
  	if (onEntry()) {
  	  //Actions en entrée de l état
    	  outputs()->CommandeMouvementXY_TETA_sym(45 , -39 , 3.14);

  	}
  	//Transitions vers les autres états
    	gotoStateIfConvergence(ETAT_35, 7000);
  	if (onExit()) {
  	  //TODO : pouvoir intégrer des actions en sortie d état
  	}
  	break;

  case ETAT_35 :
  	if (onEntry()) {
  	  //Actions en entrée de l état
    	  outputs()->CommandeMouvementXY_TETA_sym(45 , -39 , 3.14);

  	}
  	//Transitions vers les autres états
    	gotoStateAfter(ETAT_36, 23000);
  	if (onExit()) {
  	  //TODO : pouvoir intégrer des actions en sortie d état
  	}
  	break;

  case ETAT_36 :
  	if (onEntry()) {
  	  //Actions en entrée de l état
    	  outputs()->CommandeMouvementXY_TETA_sym(13 , -39 , 3.14);

  	}
  	//Transitions vers les autres états
    	gotoStateIfConvergence(ETAT_37, 7000);
  	if (onExit()) {
  	  //TODO : pouvoir intégrer des actions en sortie d état
  	}
  	break;

  case ETAT_37 :
  	if (onEntry()) {
  	  //Actions en entrée de l état
    	  outputs()->CommandeMouvementXY_TETA_sym(-6 , -26 , 2.35);

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
