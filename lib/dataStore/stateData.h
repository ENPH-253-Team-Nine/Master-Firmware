#ifndef STATE_DATA_H
#define STATE_DATA_H

#include <stdint.h>

// kinda gross but neccesary, AFAIK, forward declaration.
namespace StateMachine{
    enum class StateEnum;
}

namespace sensors{
    enum class SwitchState;
}


// Data about the current state of the robot
// I'm using state very generally to mean 'current situation' not just the state
// from the state machine. Open to better name suggestions.
namespace StateData{

    // This has to be a pointer (in conjuntion with the forward declaration above)
    // so that it can 'exist' without including stateMachine.h, which is not 
    // possible to include for fun circular dependancy reasons.
    extern StateMachine::StateEnum* state;

    extern int8_t driveSpeed;
    extern int8_t driveSteer;

    namespace IR{
        extern double leftIRStrength;
        extern double rightIRStrength;
    }

    namespace switches{
        extern sensors::SwitchState clawLimitSwitch;
    }

    namespace reflectances{
        extern double clawReflectance;
        extern double leftReflectance;
        extern double rightReflectance;
    }

    namespace magnets{
        extern double clawHall;
    }

    namespace HMI{
        static constexpr char exposition[] = "IDK what to do with HMI at the moment";
    }

    namespace encoders{
        extern int leftEncoderCount;
        extern int rightEncoderCount;
    }
    extern uint8_t elbowServoPos;
    extern uint8_t clawServoPos;
}


#endif