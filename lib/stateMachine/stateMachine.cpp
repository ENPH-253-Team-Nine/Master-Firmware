#include "stateMachine.h"

/*  Ugh, OK, this is a workaround that I am not super pleased about but:
    There needs to be something to hold the enum state value so that we can get
    a pointer to it, so that we can access it from stateData. But I don't
    **THINK** that this should be accessable from outside this file/translation
    unit */
StateMachine::StateEnum currentEnumState;

StateMachine::StateManager::StateManager()
{
    // currentState = new StateMachine::States::Startup();
    currentState = new StateMachine::States::NavByLine();

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
}

StateMachine::AbstractState *StateMachine::States::Startup::evaluateTransition()
{
    if (millis() >= stateEntryTime + 5000 /*just some random constant*/)
    {
        currentEnumState = StateMachine::StateEnum::Error;
        StateData::state = &currentEnumState;
        StateData::debugStateName = this->getDebugStateName();
        return new StateMachine::States::Error();
    }
    else
    {
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
        currentEnumState = StateMachine::StateEnum::Error;
        StateData::state = &currentEnumState;
        return new StateMachine::States::Error();
    }
    else
    {
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
    {
        currentEnumState = StateMachine::StateEnum::NavByLine;
        StateData::state = &currentEnumState;
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
        currentEnumState = StateMachine::StateEnum::Error;
        StateData::state = &currentEnumState;
        return new StateMachine::States::Error();
    }
    else
    {
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
        currentEnumState = StateMachine::StateEnum::Error;
        StateData::state = &currentEnumState;
        return new StateMachine::States::Error();
    }
    else
    {
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
        currentEnumState = StateMachine::StateEnum::Error;
        StateData::state = &currentEnumState;
        return new StateMachine::States::Error();
    }
    else
    {
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
        currentEnumState = StateMachine::StateEnum::Startup;
        StateData::state = &currentEnumState;
        StateData::debugStateName = this->getDebugStateName();
        return new StateMachine::States::Startup();
    }
    else
    {
        return this;
    }
}

std::string StateMachine::States::Error::getDebugStateName()
{
    return "Error";
}
