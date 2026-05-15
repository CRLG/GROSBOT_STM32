/**
 * Built on 20260514_183754
 */

#ifndef SM_PETITEBORDURE_H
#define SM_PETITEBORDURE_H

#include "sm_statemachinebase.h"

class SM_PetiteBordure : public SM_StateMachineBase
{
public:
	SM_PetiteBordure();
	void step();
	const char* getName();
	const char* stateToName(unsigned short state);

	typedef enum {
	ETAT_1 = SM_StateMachineBase::SM_FIRST_STATE,

	FIN_MISSION
	}tState;
};

#endif // SM_PETITEBORDURE_H
