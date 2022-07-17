#include <servoControl.h>

using namespace servos;

#define MS_TO_uS_CONSTANT 1000

ServoManager::ServoManager()
{
    servoMotors[enumServos::ARM_CLAW] = new ServoMotor(1,1,2); //think these values are correct for the SG90s
    servoMotors[enumServos::ARM_ELBOW] = new ServoMotor(2,1,2);
}

ServoManager::~ServoManager()
{
    for (ServoMotor *servoMotor : servoMotors)
    {
        delete servoMotor;
    }
}

void ServoManager::setup()
{
    for (ServoMotor *servoMotor : servoMotors)
    {
        servoMotor->setup();
    }
}

void ServoManager::poll()
{
    // what's the frequency, Kenneth?
    if (micros() >= lastRun + period_ms)
    {
        servoMotors[enumServos::ARM_CLAW]->setSpeed(StateData::servo::clawSpeed);
        servoMotors[enumServos::ARM_CLAW]->setTarget(StateData::servo::clawPos);
        servoMotors[enumServos::ARM_ELBOW]->setSpeed(StateData::servo::elbowSpeed);
        servoMotors[enumServos::ARM_ELBOW]->setTarget(StateData::servo::elbowPos);
        for (ServoMotor *servoMotor : servoMotors)
        {
            servoMotor->poll();
        }
        lastRun = micros();
    }
}

ServoMotor::ServoMotor(int controlPin, uint8_t minPulse_ms, uint8_t maxPulse_ms, uint8_t maxAngle)
{
    servo = new Servo();
    this->controlPin = controlPin;
    this->minPulse_ms = minPulse_ms;
    this->maxPulse_ms = maxPulse_ms;
    this->maxAngle = maxAngle;
}

ServoMotor::ServoMotor(int controlPin, uint8_t minPulse_ms, uint8_t maxPulse_ms)
{
    servo = new Servo();
    this->controlPin = controlPin;
    this->minPulse_ms = minPulse_ms;
    this->maxPulse_ms = maxPulse_ms;
    this->maxAngle = 180;
}

ServoMotor::~ServoMotor()
{
    servo->detach();
}

void ServoMotor::setSpeed(uint8_t speed)
{
    this->speed = speed;
}

void ServoMotor::setTarget(uint8_t targetAngle)
{
    this->targetAngle = targetAngle;
}

void ServoMotor::setup()
{
    servo->attach(controlPin);
}

void ServoMotor::poll()
{
    int curpos = servo->read();
    while (targetAngle != curpos) //I think this works??
    {
        if (speed = 0)
        {
            int pulseWidth = map(targetAngle, 0, maxAngle, minPulse_ms * MS_TO_uS_CONSTANT, maxPulse_ms * MS_TO_uS_CONSTANT);
            servo->writeMicroseconds(pulseWidth);
        }
        else
        {
            int changeWidth = map(speed, 0, maxAngle, minPulse_ms * MS_TO_uS_CONSTANT, maxPulse_ms * MS_TO_uS_CONSTANT)/1000; //magic number bad
            if(targetAngle>curpos){
                changeWidth*=-1;
            }
            currentPos_us += changeWidth;
            servo->writeMicroseconds(currentPos_us);
        }
    }
}