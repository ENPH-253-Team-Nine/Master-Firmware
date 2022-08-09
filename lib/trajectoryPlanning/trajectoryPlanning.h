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
            void navigateByLineRamp();
            void seekLine();

            static constexpr int line_kp_default =  5.0;
            static constexpr int line_kd_default =  1.0;
            static constexpr int line_setpoint_default = 0.0;
            static constexpr int line_detectThresh = 20;
            static constexpr int line_speed_default = 70;
            static constexpr int line_corrScale_default = 1;
    };
}

#endif