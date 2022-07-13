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

/** Actual States **/

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

// Leaving these as comments for now, we can fill them in as we need them but I
// I think this early in testing it's just going to cause confusion.

/*StateMachine::State* StateMachine::States::SeekLine::evaluateTransition(){
    return new StateMachine::States::Error();
}
StateMachine::State* StateMachine::States::NavByLine::evaluateTransition(){
    return new StateMachine::States::Error();
}
StateMachine::State* StateMachine::States::RampTransition::evaluateTransition(){
    return new StateMachine::States::Error();
}
StateMachine::State* StateMachine::States::TraverseArch::evaluateTransition(){
    return new StateMachine::States::Error();
}
StateMachine::State* StateMachine::States::NavByIR::evaluateTransition(){
    return new StateMachine::States::Error();
}
StateMachine::State* StateMachine::States::SeekIR::evaluateTransition(){
    return new StateMachine::States::NavByIR();
}
StateMachine::State* StateMachine::States::TerminalMiniTreasureGuidance::evaluateTransition(){
    return new StateMachine::States::Error();
}
StateMachine::State* StateMachine::States::MiniTreasureCapture::evaluateTransition(){
    return new StateMachine::States::Error();
}
StateMachine::State* StateMachine::States::SeekBridgeAlignment::evaluateTransition(){
    return new StateMachine::States::Error();
}
StateMachine::State* StateMachine::States::DeployBridge::evaluateTransition(){
    return new StateMachine::States::Error();
}
StateMachine::State* StateMachine::States::NavByFaith::evaluateTransition(){
    return new StateMachine::States::Error();
}
StateMachine::State* StateMachine::States::TerminalBigTreasureGuidance::evaluateTransition(){
    return new StateMachine::States::Error();
}
StateMachine::State* StateMachine::States::BigTreasureCapture::evaluateTransition(){
    return new StateMachine::States::Error();
}
StateMachine::State* StateMachine::States::SeekCPERM::evaluateTransition(){
    return new StateMachine::States::Error();
}
StateMachine::State* StateMachine::States::Party::evaluateTransition(){
    return new StateMachine::States::Error();
} */
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
