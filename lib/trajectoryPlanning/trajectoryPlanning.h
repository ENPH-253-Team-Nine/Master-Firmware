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

        private:
            int8_t speed;
            int8_t steer;

            void allStop();
    };
}

#endif