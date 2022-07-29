#include <trajectoryPlanning.h>

using namespace trajectory;

TrajectoryManager::TrajectoryManager(){};

TrajectoryManager::~TrajectoryManager(){};

void TrajectoryManager::setup()
{
    StateData::reflectances::kp = kp_default;
    StateData::reflectances::kd = kd_default;
    StateData::reflectances::setpoint = setpoint_default;
    StateData::reflectances::lasterror = 0;
    StateData::reflectances::detectedThreshold = 20;
}

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
    case StateMachine::StateEnum::SeekLine:
        seekLine();
        break;
        // add more cases as neccesary.
        // presumably that means enabling more states.
    }

    StateData::driveSpeed = speed;
    StateData::driveSteer = steer;
}

/*** Various functions for determining speeds and steers ***/

// which one is being used would be dependant on the state.

void TrajectoryManager::allStop()
{
    speed = 0;
    steer = 0;
}

void TrajectoryManager::navigateByLine()
{
    int error = (StateData::reflectances::leftReflectance - StateData::reflectances::rightReflectance) - StateData::reflectances::setpoint;
    int p = StateData::reflectances::kp * error;
    int d = StateData::reflectances::kd * (error - StateData::reflectances::lasterror);

    StateData::reflectances::lasterror = error;
    int correction = p + d;

    speed = 70;

    int _steer = speed * correction / 1000;
    if (_steer > 127)
        _steer = 127;
    else if (_steer < -127)
        _steer = -127;

    steer = _steer;
}

void TrajectoryManager::seekLine()
{
    if (StateData::reflectances::leftReflectance < StateData::reflectances::detectedThreshold &&
        StateData::reflectances::rightReflectance < StateData::reflectances::detectedThreshold)
    {
        StateData::lineLastNoContactTime = millis();
        switch (lastSeen)
        {
        case LastSeenSide::NEVER:
            speed = 60;
            if (millis() >= turnStartTime + turnSteerLength_ms && inTurn)
            {
                inTurn = false;
                inSeek = true;
                seekStartTime = millis();
            }
            if (millis() >= seekStartTime + seekSegmentLength_ms && inSeek)
            {
                inSeek = false;
                inTurn = true;
                turnSteerAmount *=-1;
                turnStartTime = millis();
            }

            steer = inTurn ? turnSteerAmount : 0;

            break;
        case LastSeenSide::LEFT:
            steer = -10;
            break;
        case LastSeenSide::RIGHT:
            steer = 10;
            break;
        }
    } else {
        if(StateData::reflectances::leftReflectance>=StateData::reflectances::rightReflectance){
            lastSeen = LastSeenSide::LEFT;
            steer = 2;
        } else {
            steer = -2;
            lastSeen = LastSeenSide::RIGHT;
        }
    }
}