#ifndef STATE_DATA_H
#define STATE_DATA_H

#include <stdint.h>
#include <string>

#include <EEPROM.h>

// kinda gross but neccesary, AFAIK, forward declaration.
namespace StateMachine{
    enum class StateEnum;
}

namespace sensors{
    enum class SwitchState;
}

namespace SerialFlags{
    extern bool deployBridge; 
    extern bool rotateSonarPlatform;

    enum class BridgeFlags {
        LOCKED = 0,
        UNLOCKED = 1,
        DEPLOYED = 2,
        _LENGTH = 3
    };

    enum class PlatformFlags {
        ON = 0,
        OFF = 1,
        _LENGTH = 2
    };

    extern BridgeFlags bridgeFlags;
    extern PlatformFlags platformFlags;
}

// Data about the current state of the robot
// I'm using state very generally to mean 'current situation' not just the state
// from the state machine. Open to better name suggestions.
namespace StateData{

    // This has to be a pointer (in conjuntion with the forward declaration above)
    // so that it can 'exist' without including stateMachine.h, which is not 
    // possible to include for fun circular dependancy reasons.
    extern StateMachine::StateEnum* state;
    extern std::string debugStateName;

    extern bool mockLED;

    extern int8_t driveSpeed;
    extern int8_t driveSteer;

    namespace IR{
        extern double leftIRStrength;
        extern double rightIRStrength;
    }

    namespace switches{
        extern sensors::SwitchState clawLimitSwitch;
    }

    namespace reflectances{
        extern int clawReflectance;
        extern int lineLeft;
        extern int lineRight;

        extern int kp;
        extern int kd;
        extern int corrScale;
        extern int setpoint; 
        extern int lasterror;
        extern int correction;

        extern int edgeReflectanceFL;
        extern int edgeReflectanceFR;
        extern int edgeReflectanceBL;
        extern int edgeReflectanceBR;
    }

    namespace magnets{
        extern double clawHall;
    }

    namespace HMI{
        extern int8_t settingSelectIndex;
        extern int8_t settingLevel;
        extern bool HMIDisplayEnabled;
    }

    namespace encoders{
        extern int leftEncoderCount;
        extern int rightEncoderCount;
    }

    namespace sonar{
        extern int sonarObjectAngle;

        extern int sonarSweepSize; //length of array
        extern double sonarSweepAngularResolution; //degrees per entry
        extern int sonarSweep[160];
    }

    extern uint8_t elbowServoPos;
    extern uint8_t clawServoPos;

    extern int8_t leftMotorSpeed;
    extern int8_t rightMotorSpeed;

    extern int testSettingOne;
    extern int testSettingTwo;
    extern int testSettingThree;
    extern int testSettingFour;
    extern int testSettingFive;
    extern int testSettingSix;

    namespace persistent{
            typedef struct{
                //remember your usual struct packing rules
                int storedSetting1;
                int storedSetting2;
                int storedSetting3;
                int lineKP;
                int lineKD;
                int lineCScale;
                int lineLThresh;
                int lineRThresh;
                int lineCorCoeff;
                int manualMotorSpeed;

                int idolWidth_mm;
            } StoredSettings;

            extern StoredSettings storedSettings;

            extern uint8_t* storedSettings_bytes;

        void getFromMemory();
        void storeInMemory();   
    } 
}


#endif