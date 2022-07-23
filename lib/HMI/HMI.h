#ifndef HMI_H
#define HMI_H

#include <stdint.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <stateData.h>

namespace HMI{
    class HMIManager{
    public:
        HMIManager();
        ~HMIManager();
        void setup();
        void poll();

    private:
        static constexpr uint8_t screenWidth = 128;
        static constexpr uint8_t screenHeight = 64;
        static constexpr int8_t oledReset = -1;

        Adafruit_SSD1306* displayHandler;

        void drawFrame(uint8_t frameOffset);

        void drawLogo();


    };
}

#endif