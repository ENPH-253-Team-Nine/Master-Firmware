#include "serialComm.h"

using namespace serialComm;

SerialManager::SerialManager() {}

void SerialManager::setup() {
    Serial1.setRx(PB7);
    Serial1.setTx(PB6);
    Serial1.begin(9600);
}

void SerialManager::poll() {
    sendCommands();
    receiveData();
}

void SerialManager::sendCommands() {
    switch (SerialFlags::bridgeFlags) {
        // Only send a command to deploy bridge if Master has switched state to UNLOCKED.
        case SerialFlags::BridgeFlags::UNLOCKED:
            Serial1.write(DEPLOY_BRIDGE);
            SerialFlags::bridgeFlags = SerialFlags::BridgeFlags::DEPLOYED;
            break;
        default:
            break;
    }

    switch (SerialFlags::platformFlags) {
        case SerialFlags::PlatformFlags::ON:
            Serial1.write(SWEEP_ON);
            break;
        default:
            Serial1.write(SWEEP_OFF);
            break;
    }
}

void SerialManager::receiveData() {
    DataPacket *packet = new DataPacket();
    char recBuf[sizeof(*packet)];

    int bytesRead = Serial1.readBytes(recBuf, sizeof(*packet));

    // for (int i = 0; i < sizeof(*packet); i+=2) {
    //     int temp = recBuf[i];
    //     recBuf[i] = recBuf[i+1];
    //     recBuf[i+1] = temp;
    // }

    if (bytesRead >= 1) {
        packet = (struct DataPacket *)recBuf;
    }

    // Store variables in stateData

    StateData::reflectances::lineLeft = packet->lineL;
    StateData::reflectances::lineRight = packet->lineR;
    StateData::reflectances::edgeReflectanceFL = packet->edgeReflectanceFL;
    StateData::reflectances::edgeReflectanceFR = packet->edgeReflectanceFR;
    StateData::reflectances::edgeReflectanceBL = packet->edgeReflectanceBL;
    StateData::reflectances::edgeReflectanceBR = packet->edgeReflectanceBR;
    StateData::sonar::sonarObjectAngle = packet->sonarObjectAngle;

}