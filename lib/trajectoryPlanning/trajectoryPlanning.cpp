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
        case StateMachine::StateEnum::NavByLine:
            navigateByLine();
            break;    
        //add more cases as neccesary. 
        //presumably that means enabling more states.

    }

    StateData::driveSpeed = speed;
    StateData::driveSteer = steer;

    
}

void TrajectoryManager::setup(){
    StateData::reflectances::kp = line_kp_default;
    StateData::reflectances::kd = line_kd_default;
    StateData::reflectances::setpoint = line_setpoint_default;
    StateData::reflectances::lasterror = 0;
}

/*** Various functions for determining speeds and steers ***/

// which one is being used would be dependant on the state.

void TrajectoryManager::allStop(){
    speed = 0;
    steer = 0;
}

void TrajectoryManager::navigateByLine() {
    int error = (StateData::reflectances::lineLeft - StateData::reflectances::lineRight) - StateData::reflectances::setpoint;
    int p = StateData::reflectances::kp*error;
    int d = StateData::reflectances::kd*(error-StateData::reflectances::lasterror);

    StateData::reflectances::lasterror = error;
    float correction = p + d;

    speed = TrajectoryManager::line_speed_default;

    int _steer = (float)speed*correction/1000.0;
    if (_steer > 127) _steer = 127;
    else if (_steer < -127) _steer = -127;

    steer = _steer;
}