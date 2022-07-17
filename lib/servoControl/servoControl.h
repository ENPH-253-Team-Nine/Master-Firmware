#ifndef SERVO_CONTROL_H
#define SERVO_CONTROL_H

#include <Arduino.h>
#include <Servo.h>

#include <stateData.h>

namespace servos{
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

        Servo *servos[enumServos::_LENGTH];
    };
}

#endif