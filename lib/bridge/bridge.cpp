#include "bridge.h"

void bridge::BridgeManager::poll()
{
    switch (*StateData::state)
    {
    case StateMachine::StateEnum::Error:
        // do nothing
        break;
    case StateMachine::StateEnum::Startup:
        // deploy the bridge
        // obviously not actually in this state

        bridge::BridgeManager::deplyBridge();
    }
}

void bridge::BridgeManager::deplyBridge()
{
    // idk how this algorithm will work.

    // maybe

    // check if lined up

    // actuate servo
}