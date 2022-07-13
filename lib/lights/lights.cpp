#include "lights.h"

/*Light manager class - one instance ever */

Lights::LightManager::LightManager()
{
    lights[EnumLights::BUILTIN_LED] = new Lights::Light(LED_BUILTIN, true);
}

Lights::LightManager::~LightManager() // pretty boilerplate
{
    for (Light *light : lights)
    {
        delete light;
    }
}

void Lights::LightManager::poll()
{
    for (Light *light : lights)
    {
        switch (*StateData::state)
        {
        case StateMachine::StateEnum::Startup:
            // If we read from the data store that the state is 'startup',
            // use the 'blink' subroutine to run the lights.
            blink(100, light);
            break;
        case StateMachine::StateEnum::Error:
            // If we read from the data store that the state is 'error',
            // use the 'be on' routine to run the lights.
            beOn(light);
            break;
        }
    }
}

void Lights::LightManager::setup()
{
    for (Light *light : lights)
    {
        light->setup();
    }
}

/* State-dependant functionalities*/

void Lights::LightManager::blink(uint16_t period, Light *light)
{
    long int curTime = millis();
    // if more time has elapsed since you changed than the length of the period, toggle the light.
    if (curTime >= light->lastChanged + period)
    {
        // this breaks if you have more than just on/off states and is probably bad practice, but...
        // it's kinda cool and onelining it is the lazy, eric approved approach
        light->setLightState(static_cast<Lights::Light::LightState>(!static_cast<bool>(light->getLightState())));
    }
}

void Lights::LightManager::beOn(Light *light)
{
    if (!(light->getLightState() == Lights::Light::LightState::ON))
    {
        light->setLightState(Lights::Light::LightState::ON);
    }
}

void Lights::LightManager::beOff(Light *light)
{
    if (!(light->getLightState() == Lights::Light::LightState::OFF))
    {
        light->setLightState(Lights::Light::LightState::OFF);
    }
}

/** Light class**/
/* One instance of this class per physical LED*/

Lights::Light::Light(int pin, bool inverted)
{
    this->pin = pin;
    this->inverted = inverted;
    this->state = Lights::Light::LightState::OFF;
}

Lights::Light::Light(int pin)
{
    this->pin = pin;
    this->inverted = false;
}

void Lights::Light::setLightState(Lights::Light::LightState newState)
{
    state = newState;
    switch (state)
    {
    case Lights::Light::LightState::ON:
        digitalWrite(pin, !inverted);
        break;

    case Lights::Light::LightState::OFF:
        digitalWrite(pin, inverted);
        break;
    }
    lastChanged = millis();
}

// I am aware that reading something like this makes the word 'light' look not real
// It's called 'semantic satiation' (https://en.wikipedia.org/wiki/Semantic_satiation)
// but I promise being organized like this will actually be less confusing in the
// long run.
Lights::Light::LightState Lights::Light::getLightState()
// Decoded:
//  Lights - the 'Lights' namespace that contains this entire file
//        ::Light - the Light class
//               ::LightState - this class will return something from the 'LightState' enum
//                            Lights - the namespace again
//                                  ::Light - the Light class again
//                                         ::getLightState() - the actual name of this function
{
    return state;
}

void Lights::Light::setup()
{
    pinMode(pin, OUTPUT);
}
