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
}

/***** Actual States *****/


/** Startup **/
StateMachine::States::Startup::Startup()
{
    this->stateEntryTime = millis();
}

StateMachine::AbstractState *StateMachine::States::Startup::evaluateTransition()
{
    if (millis() >= stateEntryTime + 5000 /*just some random constant*/)
    {
        StateMachine::States::Error* newState = new StateMachine::States::Error();
        *StateData::state = StateMachine::StateEnum::Error;
        StateData::debugStateName = newState->getDebugStateName();
        return newState;
    }
    else
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

/** Seek Line **/
StateMachine::States::SeekLine::SeekLine()
{
    this->stateEntryTime = millis();
}

StateMachine::AbstractState *StateMachine::States::SeekLine::evaluateTransition()
{
    if (millis() >= stateEntryTime + 5000 /*just some random constant*/)
    {
        *StateData::state = StateMachine::StateEnum::Error;
        StateMachine::States::Error* newState = new StateMachine::States::Error();
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
/** Nav By Line **/
StateMachine::States::NavByLine::NavByLine()
{
    this->stateEntryTime = millis();
}

StateMachine::AbstractState *StateMachine::States::NavByLine::evaluateTransition()
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
        *StateData::state = StateMachine::StateEnum::NavByLine;
        return this;
    }
}

std::string StateMachine::States::NavByLine::getDebugStateName()
{
    return "Nav By Line";
}

/** Ramp Transition **/
StateMachine::States::RampTransition::RampTransition()
{
    this->stateEntryTime = millis();
}

StateMachine::AbstractState *StateMachine::States::RampTransition::evaluateTransition()
{
    if (millis() >= stateEntryTime + 5000 /*just some random constant*/)
    {
        *StateData::state = StateMachine::StateEnum::Error;
        StateMachine::States::Error* newState = new StateMachine::States::Error();
        StateData::debugStateName = newState->getDebugStateName();
        return newState;
    }
    else
    {
        StateData::debugStateName = this->getDebugStateName();
        *StateData::state = StateMachine::StateEnum::RampTransition;
        return this;
    }
}

std::string StateMachine::States::RampTransition::getDebugStateName()
{
    return "Ramp Transition";
}

/** Seek IR **/
StateMachine::States::SeekIR::SeekIR()
{
    this->stateEntryTime = millis();
}

StateMachine::AbstractState *StateMachine::States::SeekIR::evaluateTransition()
{
    if (millis() >= stateEntryTime + 5000 /*just some random constant*/)
    {
       *StateData::state = StateMachine::StateEnum::Error;
        StateMachine::States::Error* newState = new StateMachine::States::Error();
        StateData::debugStateName = newState->getDebugStateName();
        return newState;
    }
    else
    {
        StateData::debugStateName = this->getDebugStateName();
        *StateData::state = StateMachine::StateEnum::SeekIR;
        return this;
    }
}

std::string StateMachine::States::SeekIR::getDebugStateName()
{
    return "Seek IR";
}

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
        *StateData::state = StateMachine::StateEnum::Startup;
        StateData::debugStateName = this->getDebugStateName();
        return this;
    }
}

std::string StateMachine::States::Error::getDebugStateName()
{
    return "Error";
}
