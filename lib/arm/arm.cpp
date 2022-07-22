#include "arm.h"

void arm::ArmManager::poll(){
    switch(*StateData::state){
        //this is just an incredibly basic outline... obviously the actual how it should move
        // what needs to be added to the stateData for it to control and read from
        // will all have to come later
        case StateMachine::StateEnum::Error:
        case StateMachine::StateEnum::Startup:
            armIdle();
            break;
    }
}

void arm::ArmManager::armIdle(){
    //make the servos in a neutral position.
}