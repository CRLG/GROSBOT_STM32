/**
 * Generated 29_05_2025 at 19_12
 */

#ifndef SM_RETOURZONEARRIVEE_H
#define SM_RETOURZONEARRIVEE_H

#include "sm_statemachinebase.h"

class SM_RetourZoneArrivee : public SM_StateMachineBase
{
public:
	SM_RetourZoneArrivee();
	void step();
	const char* getName();
	const char* stateToName(unsigned short state);

	typedef enum {
	STATE_1 = SM_StateMachineBase::SM_FIRST_STATE,
	STATE_2,
	STATE_3,
	STATE_4,
	STATE_5,
	STATE_6,
	STATE_7,
	STATE_8,
	STATE_9,
	STATE_10,
	STATE_11,
	STATE_12,
	STATE_13,
	STATE_14,
	STATE_15,
	STATE_16,
	STATE_17,
	STATE_18,
	FIN_MISSION
	}tState;
};

#endif // SM_RETOURZONEARRIVEE_H