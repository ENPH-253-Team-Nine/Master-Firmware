#ifndef SERVO_CONTROL_H
#define SERVO_CONTROL_H

#include <Arduino.h>
#include <Servo.h>

#include <stateData.h>

namespace servos{
    class ServoManager;

    class ServoMotor{
        friend ServoManager;

    protected:
        ServoMotor(int controlPin, uint8_t minPulse_ms, uint8_t maxPulse_ms, uint8_t maxAngle);
        ServoMotor(int controlPin, uint8_t minPulse_ms, uint8_t maxPulse_ms);
        ~ServoMotor();
        void setup();
        void poll();
        // speed is in degrees per 1000 servo control ticks
        void setSpeed(uint8_t speed);
        void setTarget(uint8_t targetAngle);
        

    private:
        int controlPin;
        Servo *servo;
        int16_t speed;
        uint8_t targetAngle;
        uint8_t minPulse_ms;
        uint8_t maxPulse_ms;
        int currentPos_us;
        uint8_t maxAngle;
    };

    class ServoManager{
        public:
        ServoManager();
        ~ServoManager();
        void poll();
        void setup();
    private:
        enum enumServos{
            ARM_ELBOW,
            ARM_CLAW,
            _LENGTH
        };
        long int lastRun;
        static constexpr long int period_ms = 1000; //1khz

        ServoMotor *servoMotors[enumServos::_LENGTH]; 
    };
}

#endif