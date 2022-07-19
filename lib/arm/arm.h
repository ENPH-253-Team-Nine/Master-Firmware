#ifndef ARM_H
#define ARM_H

#include <stateData.h>
#include <stateMachine.h>

namespace arm
{
    class ArmManager
    {
    public:
        //just using the default implicit constructor
        void poll();

    private:
        void deployArm();
        void graspTreasure();
        void checkForBomb();
        void stowTreasure();
        void armIdle();
    };
}

#endif