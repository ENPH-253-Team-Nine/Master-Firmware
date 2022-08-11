#include <trajectoryPlanning.h>

using namespace trajectory;

TrajectoryManager::TrajectoryManager() {};

TrajectoryManager::~TrajectoryManager() {};

void TrajectoryManager::poll(){

    //... some code to determine what those should be ...

    switch(*StateData::state){
        case StateMachine::StateEnum::Error:
            // Fallthrough
        case StateMachine::StateEnum::Startup:
            allStop();
            break;
        case StateMachine::StateEnum::AlignTreasure:    
            alignTreasure();

    }

    StateData::driveSpeed = speed;
    StateData::driveSteer = steer;

    
}

/*** Various functions for determining speeds and steers ***/

// which one is being used would be dependant on the state.

void TrajectoryManager::allStop(){
    speed = 0;
    steer = 0;
}

void TrajectoryManager::alignTreasure(){
    speed = 55;
    steer = 0;
}