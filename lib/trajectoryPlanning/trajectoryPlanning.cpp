#include <trajectoryPlanning.h>

using namespace trajectory;

TrajectoryManager::TrajectoryManager(){};

TrajectoryManager::~TrajectoryManager(){};

void TrajectoryManager::poll()
{

    //... some code to determine what those should be ...

    switch (*StateData::state)
    {
    case StateMachine::StateEnum::Error:
        // Fallthrough
    case StateMachine::StateEnum::Startup:
        allStop();
        break;
    case StateMachine::StateEnum::NavByLine:
        navigateByLine();
        break;
        // add more cases as neccesary.
        // presumably that means enabling more states.
    }

    // StateData::driveSpeed = speed;
    StateData::driveSteer = steer;
}

void TrajectoryManager::setup()
{
    // StateData::persistent::storedSettings.lineKP = line_kp_default;
    // StateData::persistent::storedSettings.lineKD = line_kd_default;
    // StateData::reflectances::setpoint = line_setpoint_default;
    StateData::reflectances::lasterror = 0;
    // StateData::reflectances::corrScale = line_corrScale_default;
}

/*** Various functions for determining speeds and steers ***/

// which one is being used would be dependant on the state.

void TrajectoryManager::allStop()
{
    speed = 0;
    steer = 0;
}

// void TrajectoryManager::navigateByLine() {
//     int error = (StateData::reflectances::lineLeft - StateData::reflectances::lineRight) - StateData::reflectances::setpoint;
//     int p = StateData::reflectances::kp*error;
//     int d = StateData::reflectances::kd*(error-StateData::reflectances::lasterror);

//     StateData::reflectances::lasterror = error;
//     int correction = p + d;

//     speed = TrajectoryManager::line_speed_default;

//     int8_t _steer = (float)speed*(float)correction/((float)StateData::reflectances::corrScale);
//     StateData::reflectances::correction = correction;
//     if (_steer > 127) _steer = 127;
//     else if (_steer < -127) _steer = -127;

//     steer = _steer;
// }

void TrajectoryManager::navigateByLine()
{
    // int leftThresh = 420;
    // int rightThresh = 85;
    int error = 0;

    if (StateData::reflectances::lineLeft > StateData::persistent::storedSettings.lineLThresh && StateData::reflectances::lineRight > StateData::persistent::storedSettings.lineRThresh)
    {
        error = 0;
    }
    else if (StateData::reflectances::lineLeft > StateData::persistent::storedSettings.lineLThresh && StateData::reflectances::lineRight <= StateData::persistent::storedSettings.lineRThresh)
    {
        error = -1;
    }
    else if (StateData::reflectances::lineLeft <= StateData::persistent::storedSettings.lineLThresh && StateData::reflectances::lineRight > StateData::persistent::storedSettings.lineRThresh)
    {
        error = 1;
    }
    else if (StateData::reflectances::lineLeft <= StateData::persistent::storedSettings.lineLThresh && StateData::reflectances::lineRight <= StateData::persistent::storedSettings.lineRThresh)
    {
        if (abs(StateData::reflectances::lasterror) <= 1) {
            error = StateData::reflectances::lasterror * StateData::persistent::storedSettings.lineCorCoeff;
        } else {
            error = StateData::reflectances::lasterror;
        }
    }

    int p = StateData::persistent::storedSettings.lineKP * error;
    int d = StateData::persistent::storedSettings.lineKD * (error - StateData::reflectances::lasterror);

    StateData::reflectances::lasterror = error;
    int correction = p + d;

    speed = StateData::persistent::storedSettings.manualMotorSpeed;

    int8_t _steer = (float)speed * (float)correction / ((float)StateData::persistent::storedSettings.lineCScale);
    StateData::reflectances::correction = correction;
    if (_steer > 127)
        _steer = 127;
    else if (_steer < -127)
        _steer = -127;

    steer = _steer;
}