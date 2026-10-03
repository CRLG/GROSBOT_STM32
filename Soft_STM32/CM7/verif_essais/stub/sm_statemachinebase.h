// Atelier evitement 2027 -- substitut minimal de SM_StateMachineBase pour verif_essais : seuls les
// scripts (essais_atelier.cpp) sont compiles hors cible, la mission elle-meme ne l'est pas.
#ifndef SM_STATEMACHINEBASE_STUB_H
#define SM_STATEMACHINEBASE_STUB_H

class SM_StateMachineBase
{
public:
    enum { SM_FIRST_STATE = 16 };
    virtual ~SM_StateMachineBase() {}
    virtual void step() = 0;
protected:
    unsigned short m_state;
    bool m_main_mission_type;
    unsigned short m_max_score;
};

#endif
