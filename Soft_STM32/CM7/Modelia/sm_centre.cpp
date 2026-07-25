/**
* Built on 20260720_131357
*/

#include "sm_centre.h"
#include "CGlobale.h"

SM_Centre::SM_Centre()
{
	m_main_mission_type = true;
	m_max_score = 0;
}

const char* SM_Centre::getName()
{
	return "SM_Centre";
}

const char* SM_Centre::stateToName(unsigned short state)
{
	switch(state)
	{
		case ETAT_1 :	return "ETAT_1";
		case ETAT_2 :	return "ETAT_2";
		case ETAT_3 :	return "ETAT_3";

		case FIN_MISSION :	return "FIN_MISSION";
	}
	return "UNKNOWN_STATE";
}

// _____________________________________
void SM_Centre::step()
{
	switch (m_state)
	{
			
// _____________________________________

  case ETAT_1 :
  	if (onEntry()) {
  	  //Actions en entrée de l état
    	  Application.m_asservissement.CommandeMouvementXY_TETA(66 , -58 , 0);

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
    	  Application.m_asservissement.CommandeMouvementXY_TETA(160 , -58 , 0);

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
    	  Application.m_asservissement.CommandeMouvementXY_TETA(217 , -27 , 1.57);

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
