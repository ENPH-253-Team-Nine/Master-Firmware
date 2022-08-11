#ifndef ARM_H
#define ARM_H

#include <stateData.h>
#include <stateMachine.h>
#include <sensors.h>
#include <servoControl.h>
#include <sensors.h>

namespace arm
{
    class ArmManager
    {
    public:
        //just using the default implicit constructor
        void poll();
        void setup(servos::ServoManager *servoManager,sensors::SensorManager* sensorManager);

    private:
        void deployArm();
        void graspTreasure();
        void checkForBomb();
        void stowTreasure();
        void armIdle();
        void clawClose();
        void grabStash();
        enum class Modes{
            READY_SET,
            CHECK_BOMB,
            CLOSE_CLAW,
            LIFT_ARM,
            OPEN_CLAW,
        } mode;
        servos::ServoManager* servoManager;
        sensors::SensorManager* sensorManager;
    };
}

#endif