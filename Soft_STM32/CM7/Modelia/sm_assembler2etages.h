/**
 * Generated 30_05_2025 at 13_04
 */

#ifndef SM_ASSEMBLER2ETAGES_H
#define SM_ASSEMBLER2ETAGES_H

#include "sm_statemachinebase.h"

class SM_Assembler2Etages : public SM_StateMachineBase
{
public:
	SM_Assembler2Etages();
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
	STATE_19,
	STATE_20,
	STATE_21,
	STATE_22,
	STATE_23,
	STATE_24,
	STATE_25,
	STATE_26,
	STATE_27,
	STATE_28,
	STATE_29,
	STATE_30,
	STATE_31,
	STATE_32,
	STATE_33,
	STATE_34,
	STATE_35,
	STATE_36,
	STATE_37,
	STATE_38,
	STATE_39,
	STATE_40,
	STATE_41,
	STATE_42,
	STATE_43,
	STATE_44,
	STATE_45,
	FIN_MISSION
	}tState;
};

#endif // SM_ASSEMBLER2ETAGES_H