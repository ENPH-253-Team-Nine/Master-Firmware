#ifndef HMI_H
#define HMI_H

#include <stdint.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <stateData.h>
#include <stateMachine.h>

namespace HMI{
    class HMISetting;
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

        TwoWire* wire2;
        void drawFrame(uint8_t frameOffset);

        void drawTitleBar();
        void displayState();

        enum settingsEnum{
            SETTING_TESTONE,
            SETTING_TESTTWO,
            SETTING_TESTTHREE,
            SETTING_TESTFOUR,
            SETTING_TESTFIVE,
            SETTING_TESTSIX,
            _LENGTH
        };

        HMISetting* settings[settingsEnum::_LENGTH];


    };

    class HMISetting{
        friend HMIManager;
        virtual void changeSetting(int delta);
        virtual std::string getDisplayName();
        virtual void displaySetting(int ypos, bool selected);


    };

    class IntSetting : HMISetting{
        friend HMIManager;

        int* settingStore;

        int maxValue;

        int minValue;

        std::string displayName;

        Adafruit_SSD1306* displayHandler;

        IntSetting(int* settingStore, int maxValue, int minValue, std::string displayName, Adafruit_SSD1306* displayHandler);

        void changeSetting(int delta);

        std::string getDisplayName();

        void displaySetting(int ypos, bool selected);
    };
}

#endif