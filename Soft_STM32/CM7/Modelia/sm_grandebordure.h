/**
 * Built on 20260514_183741
 */

#ifndef SM_GRANDEBORDURE_H
#define SM_GRANDEBORDURE_H

#include "sm_statemachinebase.h"

class SM_GrandeBordure : public SM_StateMachineBase
{
public:
	SM_GrandeBordure();
	void step();
	const char* getName();
	const char* stateToName(unsigned short state);

	typedef enum {
	ETAT_1 = SM_StateMachineBase::SM_FIRST_STATE,

	FIN_MISSION
	}tState;
};

#endif // SM_GRANDEBORDURE_H
