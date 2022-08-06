// Boilerplate..
#ifndef STATE_MACHINE_H
#define STATE_MACHINE_H

#include <string>
#include <Arduino.h>

#include <stateData.h>

namespace StateMachine
{
    // Abstract base class for states
    class AbstractState
    {
    public:
        virtual std::string getDebugStateName();
        virtual AbstractState *evaluateTransition() = 0;
        virtual ~AbstractState() {}
    };

    // All the possible states we could be in
    namespace States
    {
        class Startup : public AbstractState
        {
        public:
            AbstractState *evaluateTransition();
            std::string getDebugStateName();
            Startup();

        private:
            long int stateEntryTime;
        };

        class SeekLine : public AbstractState
        {
            AbstractState *evaluateTransition();
            std::string getDebugStateName();
            SeekLine();

        private:
            long int stateEntryTime;
        };

        class NavByLine : public AbstractState
        {
        public:
            AbstractState *evaluateTransition();
            std::string getDebugStateName();
            NavByLine();

        private:
            long int stateEntryTime;
        };

        class RampTransition : public AbstractState
        {
            AbstractState *evaluateTransition();
            std::string getDebugStateName();
            RampTransition();

        private:
            long int stateEntryTime;
        };
        /*class TraverseArch : public State{
            virtual State* evaluateTransition();
            const std::string debugStateName = "TraverseArch";};*/

        class SeekIR : public AbstractState
        {
            AbstractState *evaluateTransition();
            std::string getDebugStateName();
            SeekIR();

        private:
            long int stateEntryTime;
        };

        class NavByIR : public AbstractState
        {
            AbstractState *evaluateTransition();
            std::string getDebugStateName();
            NavByIR();

        private:
            long int stateEntryTime;
        };

        /*class TerminalMiniTreasureGuidance : public State{
            virtual State* evaluateTransition();
            const std::string debugStateName = "TerminalMiniTreasureGuidance";};
        class MiniTreasureCapture : public State{
            virtual State* evaluateTransition();
            const std::string debugStateName = "MiniTreasureCapture";};
        class SeekBridgeAlignment : public State{
            virtual State* evaluateTransition();
            const std::string debugStateName = "SeekBridgeAlignment";};
        class DeployBridge : public State{
            virtual State* evaluateTransition();
            const std::string debugStateName = "DeployBridge";};
        class NavByFaith : public State{
            virtual State* evaluateTransition();
            const std::string debugStateName = "NavByFaith";};
        class TerminalBigTreasureGuidance : public State{
            virtual State* evaluateTransition();
            const std::string debugStateName = "TerminalBigTreasureGuidance";};
        class BigTreasureCapture : public State{
            virtual State* evaluateTransition();
            const std::string debugStateName = "BigTreasureCapture";};
        class SeekCPERM : public State{
            virtual State* evaluateTransition();
            const std::string debugStateName = "SeekCPERM";};
        class ExecuteCPERM : public State{
            virtual State* evaluateTransition();
            const std::string debugStateName = "ExecuteCPERM";};
        class Party : public State{
            virtual State* evaluateTransition();
            const std::string debugStateName = "Party";};
        */
        class Error : public AbstractState
        {
        public:
            AbstractState *evaluateTransition();
            std::string getDebugStateName();
            Error();

        private:
            long int stateEntryTime;
        };
    }
    // Enumerated list of all the above states, makes interpretation in other
    // parts of the code a lot easier.
    enum class StateEnum
    {
        Startup,
        SeekLine,
        NavByLine,
        RampTransition,
        /*TraverseArch,*/
        SeekIR,
        NavByIR,
        /*TerminalMiniTreasureGuidance,
        MiniTreasureCapture,
        SeekBridgeAlignment,
        DeployBridge,
        NavByFaith,
        TerminalBigTreasureGuidance,
        BigTreasureCapture,
        SeekCPERM,
        ExecuteCPERM,
        Party,*/
        Error
    };

    // Manages the states.
    class StateManager
    {
    public:
        StateManager();

        void poll();

        AbstractState *getCurrentState();

        std::string getCurrentStateDebugName();

    private:
        AbstractState *currentState;
    };

}

#endif