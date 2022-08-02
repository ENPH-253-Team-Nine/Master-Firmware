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
            void navigateByIR();
            static constexpr int kp_default =  3;
            static constexpr int kd_default =  1;
            static constexpr int setpoint_default = 0.0;
            void seekLine();
            static constexpr int seekTurnSpeed_default = 1;
            int turnSteerAmount = 2;
            bool inTurn;
            bool inSeek;
            static constexpr int neccesaryContactTime_ms = 500;
            long int turnStartTime;
            int turnSteerLength_ms = 20;
            int seekSegmentLength_ms = 2000;
            long int seekStartTime;
            enum class LastSeenSide{
                NEVER,
                RIGHT,
                LEFT,
            } lastSeen;
            

    };
}

#endif