#include "sensors.h"

using namespace sensors;

AbstractPolledSensor::AbstractPolledSensor(void *storeLocation, int pin){
    this->storeLocation = storeLocation;
    this->pin = pin;
}

void AbstractPolledSensor::setup(){
    pinMode(pin, INPUT_PULLUP);
}

AbstractInterruptSensor::AbstractInterruptSensor(void *storeLocation, int pin){
    this->storeLocation = storeLocation;
    this->pin = pin;
}

void AbstractInterruptSensor::setup(){
    pinMode(pin, INPUT_PULLUP);
}

/* IR Frequency*/

IRFrequency::IRFrequency(void *storeLocation, int pin) : AbstractPolledSensor(storeLocation, pin) {}

void IRFrequency::setup() {
    AbstractPolledSensor::setup();
}

void IRFrequency::read(){
    *((double *) storeLocation) = analogRead(pin); //pointer fuckery
}

/* Switch */

Switch::Switch(void *storeLocation, int pin) : AbstractPolledSensor(storeLocation, pin) {}

void Switch::setup(){
    AbstractPolledSensor::setup();
}

void Switch::read(){
    switch(digitalRead(pin)){
        case HIGH:
            *((SwitchState *) storeLocation) = SwitchState::CLOSED;
            break;
        case LOW:
            *((SwitchState *) storeLocation) = SwitchState::OPEN;
            break;
    }    
}

/* Reflectance */

ReflectanceSensor::ReflectanceSensor(void *storeLocation, int pin) : AbstractPolledSensor(storeLocation, pin) {}

void ReflectanceSensor::setup(){
    AbstractPolledSensor::setup();
}

void ReflectanceSensor::read(){
    *((double *) storeLocation) = analogRead(pin);
}

/* Hall Effect */

HallSensor::HallSensor(void *storeLocation, int pin) : AbstractPolledSensor(storeLocation, pin) {}

void HallSensor::setup(){
    AbstractPolledSensor::setup();
}

void HallSensor::read(){
    *((double *) storeLocation) = analogRead(pin);
}

/* Button */

Button::Button(void *storeLocation, int pin, bool incrementor) : AbstractInterruptSensor(storeLocation, pin) {
    this->incrementor = incrementor;
    this->lastPress = 0;
}

void Button::setup(){
    AbstractInterruptSensor::setup();
    std::function<void()> passableHandle = [=]{this->handler();};  //oh god more terrible pointer fuckery, now with lambdas
                                                                    //https://stackoverflow.com/questions/7582546/using-generic-stdfunction-objects-with-member-functions-in-one-class
    attachInterrupt(digitalPinToInterrupt(pin), passableHandle, FALLING);
}

void Button::handler(){
    if(millis()>=lastPress+debouceTime_ms){
        incrementor ? *((int *) storeLocation)+=1 : *((int *) storeLocation) -=1;
        lastPress = millis();
    }
    
}


/* Encoder */

//I am not confident in this

Encoder::Encoder(void *storeLocation, int pinA, int pinB){
    encoderA = new EncoderInterrupt(pinA, [=]{this->handler();});
    encoderB = new EncoderPoll(&encoderBValue, pinB);

    this->storeLocation = storeLocation;
}

void Encoder::setup(){
    encoderA->setup();
    encoderB->setup();
}

void Encoder::handler(){
    encoderB->read();
    switch(encoderBValue){
        case EncoderValue::ENCODER_HIGH:
            *((int *) storeLocation)-=1;
            break;
        case EncoderValue::ENCODER_LOW:
            *((int *) storeLocation)+=1;
            break;
    }
}


Encoder::EncoderInterrupt::EncoderInterrupt(int pin, std::function<void()> upperHandle) : AbstractInterruptSensor(nullptr, pin){
    this->upperHandle = upperHandle;
}

void Encoder::EncoderInterrupt::setup(){
    AbstractInterruptSensor::setup();
    attachInterrupt(digitalPinToInterrupt(pin), upperHandle, RISING);
}

Encoder::EncoderPoll::EncoderPoll(Encoder::EncoderValue* storeData, int pin) : AbstractPolledSensor(storeData, pin) {}

void Encoder::EncoderPoll::setup(){
    AbstractPolledSensor::setup();
}

void Encoder::EncoderPoll::read(){
        switch(digitalRead(pin)){
        case HIGH:
            *((Encoder::EncoderValue *) storeLocation) = Encoder::EncoderValue::ENCODER_HIGH;
            break;
        case LOW:
            *((Encoder::EncoderValue *) storeLocation) = Encoder::EncoderValue::ENCODER_LOW;
            break;
    } 
}


/* Sensor Manager */

SensorManager::SensorManager(){
    polledSensors[polledSensorEnum::IR_STRENGTH_LEFT] = new IRFrequency(&StateData::IR::leftIRStrength,PB1);
    polledSensors[polledSensorEnum::IR_STRENGTH_RIGHT] = new IRFrequency(&StateData::IR::rightIRStrength,PB0);
    polledSensors[polledSensorEnum::CLAW_LIMIT_SWITCH] = new Switch(&StateData::switches::clawLimitSwitch, PB13);
    polledSensors[polledSensorEnum::CLAW_REFLECT] = new ReflectanceSensor(&StateData::reflectances::clawReflectance,PA5);
    polledSensors[polledSensorEnum::CLAW_HALL_EFFECT] = new HallSensor(&StateData::magnets::clawHall,PA7);

    //not dealing with interrupts at the moment, don't know what to do with the HMI

    encoders[encoderEnum::ENCODER_LEFT] = new Encoder(&StateData::encoders::leftEncoderCount,PA3,PA6);
    encoders[encoderEnum::ENCODER_RIGHT] = new Encoder(&StateData::encoders::rightEncoderCount,PA2,PA4);

    interruptedSensors[interruptSensorEnum::HMI_1] = new Button(&StateData::HMI::settingSelectIndex, PB11, false);
    interruptedSensors[interruptSensorEnum::HMI_2] = new Button(&StateData::HMI::settingLevel, PA11, true);
    interruptedSensors[interruptSensorEnum::HMI_3] = new Button(&StateData::HMI::settingLevel, PA13, false);
    interruptedSensors[interruptSensorEnum::HMI_2] = new Button(&StateData::HMI::settingSelectIndex, PA15, true);


}

void SensorManager::poll(){
    for(AbstractPolledSensor* sensor : polledSensors){
        sensor->read();
    }
}

void SensorManager::setup(){
    for(AbstractPolledSensor* sensor : polledSensors){
        sensor->setup();
    }
    interruptedSensors[interruptSensorEnum::HMI_1]->setup();
    interruptedSensors[interruptSensorEnum::HMI_2]->setup();

    /*for(AbstractInterruptSensor* sensor : interruptedSensors){
        sensor->setup();
    }*/ //temp ignoring
    for(Encoder* sensor : encoders){
        sensor->setup();
    }
}
