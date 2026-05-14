/**
 * Built on 20260514_082800
 */

#ifndef SM_DEPOSERPILECENTRALE_H
#define SM_DEPOSERPILECENTRALE_H

#include "sm_statemachinebase.h"

class SM_DeposerPileCentrale : public SM_StateMachineBase
{
public:
	SM_DeposerPileCentrale();
	void step();
	const char* getName();
	const char* stateToName(unsigned short state);

	typedef enum {
	ETAT_1 = SM_StateMachineBase::SM_FIRST_STATE,
	ETAT_2,
	ETAT_3,
	ETAT_4,
	ETAT_5,
	ETAT_6,
	ETAT_7,

	FIN_MISSION
	}tState;
};

#endif // SM_DEPOSERPILECENTRALE_H
