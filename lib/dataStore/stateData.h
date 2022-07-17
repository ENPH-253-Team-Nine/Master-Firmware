#ifndef STATE_DATA_H
#define STATE_DATA_H

#include <stdint.h>

// kinda gross but neccesary, AFAIK, forward declaration.
namespace StateMachine
{
    enum class StateEnum;
}

// Data about the current state of the robot
// I'm using state very generally to mean 'current situation' not just the state
// from the state machine. Open to better name suggestions.
namespace StateData
{
    // This has to be a pointer (in conjuntion with the forward declaration above)
    // so that it can 'exist' without including stateMachine.h, which is not
    // possible to include for fun circular dependancy reasons.
    extern StateMachine::StateEnum *state;

    extern int8_t driveSpeed;
    extern int8_t driveSteer;

    namespace servo
    {
        extern uint8_t elbowPos;
        extern uint8_t elbowSpeed;
        extern uint8_t clawPos;
        extern uint8_t clawSpeed;
    }
}

#endif