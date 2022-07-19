#ifndef BRIDGE_H
#define BRIDGE_H

#include <stateData.h>
#include <stateMachine.h>

namespace bridge
{
    class BridgeManager
    {
    public:
        void poll();

    private:
        void deplyBridge();
    };

}
#endif