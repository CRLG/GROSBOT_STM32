/**
 * Built on 20260516_094629
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
	ETAT_22,
	ETAT_23,
	ETAT_24,
	ETAT_25,
	ETAT_26,
	ETAT_27,
	ETAT_28,
	ETAT_29,
	ETAT_30,
	ETAT_31,
	ETAT_32,
	ETAT_33,
	ETAT_34,
	ETAT_35,
	ETAT_36,
	ETAT_37,

	FIN_MISSION
	}tState;
};

#endif // SM_CURSEUR_H
