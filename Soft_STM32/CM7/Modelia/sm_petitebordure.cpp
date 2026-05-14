/**
* Built on 20260514_183754
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
