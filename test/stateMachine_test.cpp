#include <stateMachine.h>

#include <unity.h>

void setUp(void){

}

void tearDown(void){

}


int main(int argc, char **argv){

    UNITY_BEGIN();
    StateMachine::StateManager* stateManager = new StateMachine::StateManager();

    stateManager->poll();

    stateManager->poll();

    stateManager->poll();

    stateManager->poll();

    UNITY_END();
    return 0;
}