/**
 * Built on 20260514_183704
 */

#ifndef SM_CURSEUR_H
#define SM_CURSEUR_H

#include "sm_statemachinebase.h"

class SM_Curseur : public SM_StateMachineBase
{
public:
	SM_Curseur();
	void step();
	const char* getName();
	const char* stateToName(unsigned short state);

	typedef enum {
	ETAT_1 = SM_StateMachineBase::SM_FIRST_STATE,

	FIN_MISSION
	}tState;
};

#endif // SM_CURSEUR_H
