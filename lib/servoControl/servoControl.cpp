#include <servoControl.h>

using namespace servos;

ServoManager::ServoManager(){
    for(Servo* servo : servos){
        servo = new Servo();
    }
}

ServoManager::~ServoManager(){
    for(Servo* servo : servos){
        servo->detach();
        delete servo;
    }
}

void ServoManager::setup(){
    servos[enumServos::ARM_CLAW]->attach(0 /* need to look up what the actual values are*/);
    servos[enumServos::ARM_ELBOW]->attach(1);
}

void ServoManager::poll(){
    //right now this only controls servo angle and not speed. 
    //we can control speed but it will be some more work and more code.
    servos[enumServos::ARM_CLAW]->write(StateData::clawServoPos);
    servos[enumServos::ARM_ELBOW]->write(StateData::elbowServoPos);
}