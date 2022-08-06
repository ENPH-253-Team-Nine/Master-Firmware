#ifndef HMI_H
#define HMI_H

#include <stdint.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <stateData.h>
#include <stateMachine.h>

#include <math.h>

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

        int16_t settingDelta;
        int8_t internalSettingIndex;
        void drawFrame(uint8_t frameOffset);

        void drawTitleBar();
        void displayState();
        void cycleDelta();

        enum settingsEnum{
            SETTING_TESTONE,
            SETTING_TESTTWO,
            SETTING_TESTTHREE,
            SETTING_TESTFOUR,
            SETTING_TESTFIVE,
            SETTING_TESTSIX,
            SETTING_PERSISTONE,
            SETTING_PERSISTTWO,
            SETTING_PERSISTTHREE,
            SETTING_STOREBUTTON,
            SETTING_LINEKP,
            SETTING_LINEKD,
            SETTING_LINECSCALE,
            SETTING_LINELTHRESH,
            SETTING_LINERTHRESH,
            _LENGTH
        };

        HMISetting* settings[settingsEnum::_LENGTH];


    };

    class HMISetting{
        friend HMIManager;
        virtual void changeSetting(int delta);
        virtual std::string getDisplayName();
        virtual void displaySetting(int ypos, bool selected, bool superSelected, int delta);


    };

    class IntSetting : HMISetting{
        friend HMIManager;

        int* settingStore;

        int maxValue;

        int minValue;

        int defaultPoint;

        std::string displayName;

        Adafruit_SSD1306* displayHandler;

        IntSetting(int* settingStore, int maxValue, int minValue, int defaultPoint, std::string displayName, Adafruit_SSD1306* displayHandler);

        void changeSetting(int delta);

        std::string getDisplayName();

        void displaySetting(int ypos, bool selected, bool superSelected, int delta);
    };

    class ButtonSetting : HMISetting{
        friend HMIManager;

        std::function<void()> handler;

        std::string displayName;

        Adafruit_SSD1306* displayHandler;

        ButtonSetting(std::function<void()> handler, std::string displayName, Adafruit_SSD1306* displayHandler);

        void changeSetting(int delta);

        std::string getDisplayName();

        void displaySetting(int ypos, bool selected, bool superSelected, int delta);
    };
}

#endif