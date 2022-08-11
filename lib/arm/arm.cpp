#include "arm.h"

#include <Servo.h>

void arm::ArmManager::setup(servos::ServoManager* servoManager, sensors::SensorManager* sensorManager){
    this->servoManager = servoManager;
    this->sensorManager = sensorManager;
}

void arm::ArmManager::poll(){
    switch(*StateData::state){
        //this is just an incredibly basic outline... obviously the actual how it should move
        // what needs to be added to the stateData for it to control and read from
        // will all have to come later
       

        case StateMachine::StateEnum::Startup:
            armIdle();
            break;

        //grabStash needs ot be added to state machine
        case StateMachine::StateEnum::GrabStash:
            grabStash();
            break;
         
    }
}



void arm::ArmManager::armIdle() {
     StateData::clawServoPos = 170;
     StateData::elbowServoPos = 160;

}

void arm::ArmManager::grabStash(){

   //puts arm down and claw open
    StateData::elbowServoPos = 30;
    servoManager->poll();
    // while(true){
    //     delay(2000);
    //     StateData::clawServoPos = 170;
    //     servoManager->poll();
    //     delay(2000);
    //     StateData::clawServoPos = 30;
    //     servoManager->poll();
    //     yield();
    // }
    delay(500);
    StateData::clawServoPos = 170;
    servoManager->poll();
    delay (2500);

    


            

        
//while lim switch
    sensorManager->poll();
    if (StateData::magnets::clawHall >= 500) {
        
        //closes claw        
        StateData::clawServoPos = 20;
        servoManager->poll();
        delay(1000);


        //checks limit switch
        sensorManager->poll();
        if (StateData::switches::clawLimitSwitch == sensors::SwitchState::CLOSED){

            //closes claw 
            StateData::clawServoPos = 20;
            servoManager->poll();
            delay(2000);
            //lifts arm
            StateData::elbowServoPos = 170;
            servoManager->poll();
            delay(2000);
            //opens claw
            StateData::clawServoPos = 170;
            servoManager->poll();
            delay(2000);
        }
    }
    else {
        StateData::elbowServoPos = 160;
        servoManager->poll();
        StateData::clawServoPos = 170;
        servoManager->poll();
        delay (2500);
    }
}   
 

   
    
   