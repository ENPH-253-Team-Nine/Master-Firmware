#include <servoControl.h>

using namespace servos;

ServoManager::ServoManager()
{
    elbowServo = new Servo();
    clawServo = new Servo();
}

ServoManager::~ServoManager()
{
}

void ServoManager::setup()
{

    elbowServo->attach(PA9);
    clawServo->attach(PA10);
}

void ServoManager::poll()
{
    // right now this only controls servo angle and not speed.
    // we can control speed but it will be some more work and more code.

    elbowServo->write(StateData::elbowServoPos);
    clawServo->write(StateData::clawServoPos);
}