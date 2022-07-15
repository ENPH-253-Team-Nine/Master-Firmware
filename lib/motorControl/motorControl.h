#ifndef MOTOR_CONTROL_H
#define MOTOR_CONTROL_H

#include <Arduino.h>
#include <limits.h>

namespace motors
{
    class MotorManager; // forward declared

    class DriveMotor
    {
        friend MotorManager;

    public:
        enum class Direction
        {
            FORWARD,
            BACKWARD
        };

    protected:
        DriveMotor(PinName forwardPin, PinName reversePin);
        void setup();
        void setSpeed(uint8_t speed);
        uint8_t getSpeed();
        void setDirection(Direction direction);
        Direction getDirection();
        void updatePWMs();

    private:
        PinName forwardPin;
        PinName reversePin;
        uint8_t speed;
        Direction direction;
        int toPWM(uint8_t speed);
        static constexpr uint32_t PWMFreq = 1000; //units?
        uint16_t forwardPinValue;
        uint16_t reversePinValue;
    };

    class MotorManager
    {
    public:
        MotorManager();
        ~MotorManager();
        void poll();
        void setup();

        void setSteer(int8_t steer); //positive is right
        void setSpeed(int8_t speed);

    private:
        enum EnumMotors
        {
            DRIVE_LEFT,
            DRIVE_RIGHT,
            _LENGTH
        };

        int8_t steer;

        int8_t speed;

        DriveMotor *motors[EnumMotors::_LENGTH];

    };
}

#endif