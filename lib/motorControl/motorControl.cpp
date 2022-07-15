#include "motorControl.h"

using namespace motors;

DriveMotor::DriveMotor(PinName forwardPin, PinName reversePin){
    this->forwardPin = forwardPin;
    this->reversePin = reversePin;
    speed = 0;
    
}

void DriveMotor::setup(){
    pinMode(PA0,OUTPUT);
    pinMode(PA1,OUTPUT);
}

void DriveMotor::setDirection(DriveMotor::Direction direction){
    this->direction = direction;
}

DriveMotor::Direction DriveMotor::getDirection(){
    return direction;
}

void DriveMotor::setSpeed(uint8_t speed){
    this->speed = speed;
}

uint8_t DriveMotor::getSpeed(){
    return speed;
}

int DriveMotor::toPWM(uint8_t speed){
    //I think this needs some work
    return static_cast<int>(static_cast<double>(speed)/INT8_MAX*4096);
}

void DriveMotor::updatePWMs(){
    uint16_t newForwardPinValue;
    uint16_t newReversePinValue;

    switch(direction){
        case DriveMotor::Direction::FORWARD:
            newForwardPinValue = toPWM(static_cast<uint8_t>(speed));
            newReversePinValue = 0;
            break;
        case DriveMotor::Direction::BACKWARD:
            newForwardPinValue = 0;
            newReversePinValue = toPWM(static_cast<uint8_t>(speed));
            break;
    }
    if(forwardPinValue != newForwardPinValue || reversePinValue != newReversePinValue){
        forwardPinValue = newForwardPinValue;
        reversePinValue = newReversePinValue;
        pwm_start(forwardPin, PWMFreq, forwardPinValue, RESOLUTION_12B_COMPARE_FORMAT); //what does this resolution_ thing mean?
        pwm_start(reversePin, PWMFreq, reversePinValue, RESOLUTION_12B_COMPARE_FORMAT);
    }
}



MotorManager::MotorManager(){
    motors[DRIVE_LEFT] = new DriveMotor(PA_0, PA_1);
    motors[DRIVE_RIGHT] = new DriveMotor(PA_2, PA_3);
    steer = 0;
    speed = 0;
}

MotorManager::~MotorManager(){
    for(DriveMotor* motor : motors){
        delete motor;
    }
}

void MotorManager::setup(){
    for(DriveMotor* motor : motors){
        motor->setup();
    }
}

void MotorManager::setSteer(int8_t steer){
    this->steer = steer;
}

void MotorManager::setSpeed(int8_t speed){
    this->speed = speed;
}

void MotorManager::poll(){

    int8_t rightSpeed, leftSpeed;
    
    if(speed+steer > INT8_MAX){
        leftSpeed = INT8_MAX;
        rightSpeed = INT8_MAX-2*steer;
    } else if(speed+steer < INT8_MIN){
        rightSpeed = INT8_MAX;
        leftSpeed = INT8_MAX-2*steer;
    } else {
        leftSpeed = speed+steer;
        rightSpeed = speed - steer;
    }

    if(rightSpeed >= 0){
        motors[DRIVE_RIGHT]->setSpeed(rightSpeed);
        motors[DRIVE_RIGHT]->setDirection(DriveMotor::Direction::FORWARD);
    } else {
        motors[DRIVE_RIGHT]->setSpeed(-1*rightSpeed);
        motors[DRIVE_RIGHT]->setDirection(DriveMotor::Direction::BACKWARD);
    }

    if(leftSpeed >= 0){
        motors[DRIVE_LEFT]->setSpeed(leftSpeed);
        motors[DRIVE_LEFT]->setDirection(DriveMotor::Direction::FORWARD);
    } else {
        motors[DRIVE_LEFT]->setSpeed(-1*leftSpeed);
        motors[DRIVE_LEFT]->setDirection(DriveMotor::Direction::BACKWARD);
    }

    for(DriveMotor* motor : motors){
        motor->updatePWMs();
    }
}