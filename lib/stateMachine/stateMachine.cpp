#include "stateMachine.h"

/*  Ugh, OK, this is a workaround that I am not super pleased about but:
    There needs to be something to hold the enum state value so that we can get
    a pointer to it, so that we can access it from stateData. But I don't
    **THINK** that this should be accessable from outside this file/translation
    unit */
StateMachine::StateEnum currentEnumState;

StateMachine::StateManager::StateManager()
{
    currentState = new StateMachine::States::Startup();
    // currentState = new StateMachine::States::NavByLine();
    StateMachine::StateEnum newStateEnumValue = StateMachine::StateEnum::Startup;
    // StateMachine::StateEnum newStateEnumValue = StateMachine::StateEnum::NavByLine;
    StateData::state = &newStateEnumValue;
}

StateMachine::AbstractState *StateMachine::StateManager::getCurrentState()
{
    return this->currentState;
}

std::string StateMachine::StateManager::getCurrentStateDebugName()
{
    return this->currentState->getDebugStateName();
}

void StateMachine::StateManager::poll()
{
    currentState = currentState->evaluateTransition();
    // currentState = new StateMachine::States::NavByLine();
}

/***** Actual States *****/


/** Startup **/
StateMachine::States::Startup::Startup()
{
    this->stateEntryTime = millis();
    StateData::state = &currentEnumState;
}

StateMachine::AbstractState *StateMachine::States::Startup::evaluateTransition()
{
    if (millis() >= stateEntryTime + 000 /*just some random constant*/)
    {
        StateMachine::AbstractState* newState = new StateMachine::States::NavByLine();
        *StateData::state = StateMachine::StateEnum::NavByLine;
        StateData::debugStateName = newState->getDebugStateName();
        return newState;
    }
    // else
    {
        *StateData::state = StateMachine::StateEnum::Startup;
        StateData::debugStateName = this->getDebugStateName();
        return this;
    }
}

std::string StateMachine::States::Startup::getDebugStateName()
{
    return "Startup";
}

/** Nav By Line **/
StateMachine::States::NavByLine::NavByLine()
{
    this->stateEntryTime = millis();
}

StateMachine::AbstractState *StateMachine::States::NavByLine::evaluateTransition()
{
    if (millis() > stateEntryTime + StateData::persistent::storedSettings.preRampTime)
    {
        *StateData::state = StateMachine::StateEnum::NavByLineRamp;
        StateMachine::AbstractState* newState = new StateMachine::States::NavByLineRamp();
        StateData::debugStateName = newState->getDebugStateName();
        return newState;
    }
    else
    {
        StateData::debugStateName = this->getDebugStateName();
        *StateData::state = StateMachine::StateEnum::NavByLine;
        return this;
    }
}

std::string StateMachine::States::NavByLine::getDebugStateName()
{
    return "Nav By Line";
}

/** On Ramp Line Following **/
StateMachine::States::NavByLineRamp::NavByLineRamp()
{
    this->stateEntryTime = millis();
}

StateMachine::AbstractState *StateMachine::States::NavByLineRamp::evaluateTransition()
{
    if (millis() > stateEntryTime + StateData::persistent::storedSettings.onRampTime)
    {
        *StateData::state = StateMachine::StateEnum::SeekTreasure;
        StateMachine::AbstractState* newState = new StateMachine::States::SeekTreasure();
        StateData::debugStateName = newState->getDebugStateName();
        return newState;
    }
    else
    {
        StateData::debugStateName = this->getDebugStateName();
        *StateData::state = StateMachine::StateEnum::NavByLineRamp;
        return this;
    }
}

std::string StateMachine::States::NavByLineRamp::getDebugStateName()
{
    return "Nav By Line On Ramp";
}

/** Seek Treasure **/
StateMachine::States::SeekTreasure::SeekTreasure()
{
    this->stateEntryTime = millis();
}

StateMachine::AbstractState *StateMachine::States::SeekTreasure::evaluateTransition()
{
    //PLACEHOLDER
    if (millis() > stateEntryTime + 5000 /* arbitrary constant, change later to when in position for claw*/)
    {
        *StateData::state = StateMachine::StateEnum::PickupTreasure;
        StateMachine::AbstractState* newState = new StateMachine::States::PickupTreasure();
        StateData::debugStateName = newState->getDebugStateName();
        return newState;
    }
    else
    {
        StateData::debugStateName = this->getDebugStateName();
        *StateData::state = StateMachine::StateEnum::SeekTreasure;
        return this;
    }
}

std::string StateMachine::States::SeekTreasure::getDebugStateName()
{
    return "Seek Treasure";
}

/** Pickup Treasure **/
StateMachine::States::PickupTreasure::PickupTreasure()
{
    this->stateEntryTime = millis();
}

StateMachine::AbstractState *StateMachine::States::PickupTreasure::evaluateTransition()
{
    {
        *StateData::state = StateMachine::StateEnum::SeekLine;
        StateMachine::AbstractState* newState = new StateMachine::States::SeekLine();
        StateData::debugStateName = newState->getDebugStateName();
        return newState;
    }
}

std::string StateMachine::States::PickupTreasure::getDebugStateName()
{
    return "Pickup Treasure";
}

/** Seek Line **/
StateMachine::States::SeekLine::SeekLine()
{
    this->stateEntryTime = millis();
}

StateMachine::AbstractState *StateMachine::States::SeekLine::evaluateTransition()
{
    if (StateData::reflectances::lineLeft > StateData::persistent::storedSettings.lineLThresh || 
    StateData::reflectances::lineRight > StateData::persistent::storedSettings.lineRThresh)
    {
        *StateData::state = StateMachine::StateEnum::NavByLinePost;
        StateMachine::AbstractState* newState = new StateMachine::States::NavByLinePost();
        StateData::debugStateName = newState->getDebugStateName();
        return newState;
    }
    else
    {
        StateData::debugStateName = this->getDebugStateName();
        *StateData::state = StateMachine::StateEnum::SeekLine;
        return this;
    }
}

std::string StateMachine::States::SeekLine::getDebugStateName()
{
    return "Seek Line";
}

/** Nav By Line Post **/
StateMachine::States::NavByLinePost::NavByLinePost()
{
    this->stateEntryTime = millis();
}

StateMachine::AbstractState *StateMachine::States::NavByLinePost::evaluateTransition()
{
    if (millis() > stateEntryTime + StateData::persistent::storedSettings.postRampTime)
    {
        *StateData::state = StateMachine::StateEnum::SeekTreasure;
        StateMachine::AbstractState* newState = new StateMachine::States::SeekTreasure();
        StateData::debugStateName = newState->getDebugStateName();
        return newState;
    }
    else
    {
        StateData::debugStateName = this->getDebugStateName();
        *StateData::state = StateMachine::StateEnum::NavByLinePost;
        return this;
    }
}

std::string StateMachine::States::NavByLinePost::getDebugStateName()
{
    return "Nav By Line Post";
}


// /** Ramp Transition **/
// StateMachine::States::RampTransition::RampTransition()
// {
//     this->stateEntryTime = millis();
// }

// StateMachine::AbstractState *StateMachine::States::RampTransition::evaluateTransition()
// {
//     if (millis() >= stateEntryTime + 5000 /*just some random constant*/)
//     {
//         *StateData::state = StateMachine::StateEnum::Error;
//         StateMachine::States::Error* newState = new StateMachine::States::Error();
//         StateData::debugStateName = newState->getDebugStateName();
//         return newState;
//     }
//     else
//     {
//         StateData::debugStateName = this->getDebugStateName();
//         *StateData::state = StateMachine::StateEnum::RampTransition;
//         return this;
//     }
// }

// std::string StateMachine::States::RampTransition::getDebugStateName()
// {
//     return "Ramp Transition";
// }

// /** Seek IR **/
// StateMachine::States::SeekIR::SeekIR()
// {
//     this->stateEntryTime = millis();
// }

// StateMachine::AbstractState *StateMachine::States::SeekIR::evaluateTransition()
// {
//     if (millis() >= stateEntryTime + 5000 /*just some random constant*/)
//     {
//        *StateData::state = StateMachine::StateEnum::Error;
//         StateMachine::States::Error* newState = new StateMachine::States::Error();
//         StateData::debugStateName = newState->getDebugStateName();
//         return newState;
//     }
//     else
//     {
//         StateData::debugStateName = this->getDebugStateName();
//         *StateData::state = StateMachine::StateEnum::SeekIR;
//         return this;
//     }
// }

// std::string StateMachine::States::SeekIR::getDebugStateName()
// {
//     return "Seek IR";
// }

/** Nav by IR **/
StateMachine::States::NavByIR::NavByIR()
{
    this->stateEntryTime = millis();
}

StateMachine::AbstractState *StateMachine::States::NavByIR::evaluateTransition()
{
    if (millis() >= stateEntryTime + 5000 /*just some random constant*/)
    {
        *StateData::state = StateMachine::StateEnum::Error;
        StateMachine::States::Error* newState =  new StateMachine::States::Error();
        StateData::debugStateName = newState->getDebugStateName();
        return newState;
    }
    else
    {
        StateData::debugStateName = this->getDebugStateName();
        *StateData::state = StateMachine::StateEnum::NavByIR;
        return this;
    }
}

std::string StateMachine::States::NavByIR::getDebugStateName()
{
    return "Nav By IR";
}

/** Error **/
StateMachine::States::Error::Error()
{
    this->stateEntryTime = millis();
}

StateMachine::AbstractState *StateMachine::States::Error::evaluateTransition()
{
    if (millis() >= stateEntryTime + 5000 /*just some random constant*/)
    {
        *StateData::state = StateMachine::StateEnum::Startup;
        StateMachine::States::Startup* newState =  new StateMachine::States::Startup();
        StateData::debugStateName = newState->getDebugStateName();
        return newState;

    }
    else
    {
        StateData::HMI::HMIDisplayEnabled = true;
        *StateData::state = StateMachine::StateEnum::Error;
        StateData::debugStateName = this->getDebugStateName();
        return this;
    }
}

std::string StateMachine::States::Error::getDebugStateName()
{
    return "Error";
}
