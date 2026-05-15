/**
* Built on 20260514_183704
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
    	  // votre code ici
  	}
  	//Transitions vers les autres états
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
