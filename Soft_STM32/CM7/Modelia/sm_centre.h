/**
 * Built on 20260516_012012
 */

#ifndef SM_CENTRE_H
#define SM_CENTRE_H

#include "sm_statemachinebase.h"

class SM_Centre : public SM_StateMachineBase
{
public:
	SM_Centre();
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
	ETAT_8,
	ETAT_9,
	ETAT_10,
	ETAT_11,
	ETAT_12,
	ETAT_13,
	ETAT_14,
	ETAT_15,
	ETAT_16,
	ETAT_17,
	ETAT_18,
	ETAT_19,
	ETAT_20,
	ETAT_21,

	FIN_MISSION
	}tState;
};

#endif // SM_CENTRE_H
