/**
* Built on 20260514_183726
*/

#include "sm_retourzonedepart.h"
#include "CGlobale.h"

SM_RetourZoneDepart::SM_RetourZoneDepart()
{
	m_main_mission_type = true;
	m_max_score = 0;
}

const char* SM_RetourZoneDepart::getName()
{
	return "SM_RetourZoneDepart";
}

const char* SM_RetourZoneDepart::stateToName(unsigned short state)
{
	switch(state)
	{
		case ETAT_1 :	return "ETAT_1";

		case FIN_MISSION :	return "FIN_MISSION";
	}
	return "UNKNOWN_STATE";
}

// _____________________________________
void SM_RetourZoneDepart::step()
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
