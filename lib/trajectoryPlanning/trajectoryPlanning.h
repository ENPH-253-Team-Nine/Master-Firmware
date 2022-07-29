#ifndef TRAJECTORY_PLANNING_H
#define TRAJECTORY_PLANNING_H

//includes
#include <Arduino.h>
#include <stateData.h>
#include <stateMachine.h>

namespace trajectory{
    class TrajectoryManager{
        public:
            TrajectoryManager();

            ~TrajectoryManager();

            void poll();
            void setup();

        private:
            int8_t speed;
            int8_t steer;

            void allStop();
            void navigateByLine();
            static constexpr int kp_default =  3;
            static constexpr int kd_default =  1;
            static constexpr int setpoint_default = 0.0;
            static constexpr int lineDetectThresh = 20;
            

    };
}

#endif