#include <servoControl.h>

using namespace servos;

int map(int value){
    return 5+(double)value*(double)7/((double)180);

}

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

    //elbowServo->attach(PA9);
    //clawServo->attach(PA10);
}

void ServoManager::poll()
{
    // right now this only controls servo angle and not speed.
    // we can control speed but it will be some more work and more code.
    int clawServoValue;
    pwm_start(PA_9,20,map(StateData::clawServoPos)*4.095,RESOLUTION_12B_COMPARE_FORMAT);
    pwm_start(PA_10,20,map(StateData::elbowServoPos)*4.095,RESOLUTION_12B_COMPARE_FORMAT);
    //elbowServo->write(StateData::elbowServoPos);
    //clawServo->write(StateData::clawServoPos);
}