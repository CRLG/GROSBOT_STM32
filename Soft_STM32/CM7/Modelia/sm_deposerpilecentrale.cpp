/**
* Built on 20260514_082800
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
		case ETAT_1 :	return "ETAT_1";
		case ETAT_2 :	return "ETAT_2";
		case ETAT_3 :	return "ETAT_3";
		case ETAT_4 :	return "ETAT_4";
		case ETAT_5 :	return "ETAT_5";
		case ETAT_6 :	return "ETAT_6";
		case ETAT_7 :	return "ETAT_7";

		case FIN_MISSION :	return "FIN_MISSION";
	}
	return "UNKNOWN_STATE";
}

// _____________________________________
void SM_DeposerPileCentrale::step()
{
	switch (m_state)
	{
			
// _____________________________________

  case ETAT_1 :
  	if (onEntry()) {
  	  //Actions en entrée de l état
    	  outputs()->CommandeMouvementXY_TETA_sym(30 , -114 , 0);

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
    	  outputs()->CommandeMouvementXY_TETA_sym(110 , -114 , 1.57);

  	}
  	//Transitions vers les autres états
    	gotoStateIfConvergence(ETAT_3, 7000);
  	if (onExit()) {
  	  //TODO : pouvoir intégrer des actions en sortie d état
  	}
  	break;

  case ETAT_3 :
  	if (onEntry()) {
  	  //Actions en entrée de l état
    	  outputs()->CommandeMouvementXY_TETA_sym(110 , -83 , -3.14);

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
    	  outputs()->CommandeMouvementXY_TETA_sym(53 , -83 , -3.14);

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
    	  outputs()->CommandeMouvementXY_TETA_sym(110 , -83 , 0);

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
    	  outputs()->CommandeMouvementXY_TETA_sym(165 , -83 , 0);

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
    	  outputs()->CommandeMouvementXY_TETA_sym(110 , -83 , 0);

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
