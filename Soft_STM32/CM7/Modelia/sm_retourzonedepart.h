/**
 * Built on 20260514_183726
 */

#ifndef SM_RETOURZONEDEPART_H
#define SM_RETOURZONEDEPART_H

#include "sm_statemachinebase.h"

class SM_RetourZoneDepart : public SM_StateMachineBase
{
public:
	SM_RetourZoneDepart();
	void step();
	const char* getName();
	const char* stateToName(unsigned short state);

	typedef enum {
	ETAT_1 = SM_StateMachineBase::SM_FIRST_STATE,

	FIN_MISSION
	}tState;
};

#endif // SM_RETOURZONEDEPART_H
