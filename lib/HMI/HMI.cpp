#include "HMI.h"

using namespace HMI;

void displayOff();

HMIManager::HMIManager()
{
    this->displayHandler = new Adafruit_SSD1306(screenWidth, screenHeight, &Wire, oledReset);
    StateData::HMI::settingSelectIndex = 0;
    internalSettingIndex = 2;
    settingDelta = 1;
    settings[settingsEnum::SETTING_DISPLAY_ENABLED] = new ButtonSetting([=]{displayOff();}, "Display Off", displayHandler);
    settings[settingsEnum::SETTING_TESTONE] = new IntSetting(&StateData::testSettingOne, 1024, -1024, 0, "Test 1", displayHandler);
    settings[settingsEnum::SETTING_TESTTWO] = new IntSetting(&StateData::testSettingTwo, 1024, -1024, 0, "Test 2", displayHandler);
    settings[settingsEnum::SETTING_TESTTHREE] = new IntSetting(&StateData::testSettingThree, 1024, -1024, -1024, "Test 3", displayHandler);
    settings[settingsEnum::SETTING_TESTFOUR] = new IntSetting(&StateData::testSettingFour, 1024, -1024, 0, "Test 4", displayHandler);
    settings[settingsEnum::SETTING_TESTFIVE] = new IntSetting(&StateData::testSettingFive, 1024, -1024, -1024, "Test 5", displayHandler);
    settings[settingsEnum::SETTING_TESTSIX] = new IntSetting(&StateData::testSettingSix, 1024, -1024, 0, "Test 6", displayHandler);
    settings[settingsEnum::SETTING_PERSISTONE] = new IntSetting(&StateData::persistent::storedSettings.storedSetting1, 1024, -1024, 0, "Persist 1", displayHandler);
    settings[settingsEnum::SETTING_PERSISTTWO] = new IntSetting(&StateData::persistent::storedSettings.storedSetting2, 1024, -1024, 0, "Persist 2", displayHandler);
    settings[settingsEnum::SETTING_PERSISTTHREE] = new IntSetting(&StateData::persistent::storedSettings.storedSetting3, 1024, -1024, 0, "Persist 3", displayHandler);
    settings[settingsEnum::IDOL_WIDTH] = new IntSetting(&StateData::persistent::storedSettings.idolWidth_mm, 100, 0, 0, "Idl sz (mm)", displayHandler);
    settings[settingsEnum::SETTING_STOREBUTTON] = new ButtonSetting(StateData::persistent::storeInMemory, "Write EEPROM", displayHandler);
    settings[settingsEnum::SETTING_LINEKP] = new IntSetting(&StateData::persistent::storedSettings.lineKP, 100, 0, 10, "line KP", displayHandler);
    settings[settingsEnum::SETTING_LINEKD] = new IntSetting(&StateData::persistent::storedSettings.lineKD, 100, 0, 10, "line KD", displayHandler);
    settings[settingsEnum::SETTING_LINECSCALE] = new IntSetting(&StateData::persistent::storedSettings.lineCScale, 1000000, 1, 1000, "line C Scale", displayHandler);
    settings[settingsEnum::SETTING_LINELTHRESH] = new IntSetting(&StateData::persistent::storedSettings.lineLThresh, 1024, 1, 420, "line L thresh", displayHandler);
    settings[settingsEnum::SETTING_LINERTHRESH] = new IntSetting(&StateData::persistent::storedSettings.lineRThresh, 1024, 1, 85, "line R thresh", displayHandler);
}

void HMIManager::setup()
{
    // this should really be in some sort of storage manager but it doesn't exist
    // so I'm putting it here;

    displayHandler->begin(SSD1306_SWITCHCAPVCC, 0x3C);
    displayHandler->clearDisplay();
    for (uint8_t i = screenHeight / 2 - 2; i > 0; i--)
    {
        displayHandler->clearDisplay();
        drawFrame(i);
        displayHandler->display();
        delay(1);
    }
}

void HMIManager::poll()
{
    if (StateData::HMI::HMIDisplayEnabled)
    {
        displayHandler->clearDisplay();
        drawFrame(0);
        drawTitleBar();

        if (StateData::HMI::settingLevel > 1)
        {
            cycleDelta();
            StateData::HMI::settingLevel = 1;
        }
        else if (StateData::HMI::settingLevel < 0)
        {
            StateData::HMI::settingLevel = 0;
        }
        switch (StateData::HMI::settingLevel)
        {
        case 0:
            if (StateData::HMI::settingSelectIndex > 0)
            {
                internalSettingIndex += 1;
                StateData::HMI::settingSelectIndex = 0;
            }
            else if (StateData::HMI::settingSelectIndex < 0)
            {
                internalSettingIndex -= 1;
                StateData::HMI::settingSelectIndex = 0;
            }
            if (internalSettingIndex >= settingsEnum::_LENGTH)
            {
                internalSettingIndex = settingsEnum::_LENGTH - 1;
            }
            else if (internalSettingIndex < 0)
            {
                internalSettingIndex = 0;
            }
            break;
        case 1:
            if (StateData::HMI::settingSelectIndex > 0)
            {
                settings[internalSettingIndex]->changeSetting(-1 * settingDelta);
                StateData::HMI::settingSelectIndex = 0;
            }
            else if (StateData::HMI::settingSelectIndex < 0)
            {
                settings[internalSettingIndex]->changeSetting(settingDelta);
                StateData::HMI::settingSelectIndex = 0;
            }
            break;
        }

        if (internalSettingIndex >= 2)
            settings[internalSettingIndex - 2]->displaySetting(15, false, false, settingDelta);
        if (internalSettingIndex >= 1)
            settings[internalSettingIndex - 1]->displaySetting(25, false, false, settingDelta);
        settings[internalSettingIndex]->displaySetting(35, true, StateData::HMI::settingLevel >= 1, settingDelta);
        if (internalSettingIndex + 1 < settingsEnum::_LENGTH)
            settings[internalSettingIndex + 1]->displaySetting(45, false, false, settingDelta);
        if (internalSettingIndex + 2 < settingsEnum::_LENGTH)
            settings[internalSettingIndex + 2]->displaySetting(55, false, false, settingDelta);

        displayHandler->display();
    }
}

void HMIManager::drawFrame(uint8_t frameOffset)
{
    displayHandler->drawRect(frameOffset, frameOffset, screenWidth - frameOffset * 2, screenHeight - frameOffset * 2, SSD1306_WHITE);
}

void HMIManager::drawTitleBar()
{
    displayState();
    displayHandler->drawFastHLine(1, 10, screenWidth - 2, SSD1306_WHITE);
    int ledColor = StateData::mockLED == true ? SSD1306_WHITE : SSD1306_BLACK;
    displayHandler->fillCircle(screenWidth - 6, 5, 3, ledColor);
}

void HMIManager::displayState()
{
    displayHandler->setTextSize(1);
    displayHandler->setCursor(2, 2);
    displayHandler->setTextColor(SSD1306_WHITE);
    switch (*StateData::state)
    {
    case StateMachine::StateEnum::Error:
        displayHandler->invertDisplay(true);
        break;
    default:
        displayHandler->invertDisplay(false);
        break;
    }
    displayHandler->print("State:");
    displayHandler->println(StateData::debugStateName.c_str());
}

void HMIManager::cycleDelta()
{
    if (settingDelta < 1000)
    {
        settingDelta *= 10;
    }
    else
    {
        settingDelta = 1;
    }
}

// settings

IntSetting::IntSetting(int *settingStore, int maxValue, int minValue, int defaultPoint, std::string displayName, Adafruit_SSD1306 *displayHandler)
{
    this->defaultPoint = defaultPoint;
    this->settingStore = settingStore;
    this->maxValue = maxValue;
    this->minValue = minValue;
    this->displayName = displayName;
    this->displayHandler = displayHandler;
}

void IntSetting::changeSetting(int delta)
{
    *settingStore += delta;

    if (*settingStore > maxValue)
    {
        *settingStore = maxValue;
    }
    else if (*settingStore < minValue)
    {
        *settingStore = minValue;
    }
}

std::string IntSetting::getDisplayName()
{
    return displayName;
}

void IntSetting::displaySetting(int ypos, bool selected, bool superSelected, int delta)
{
    if (superSelected)
    {
        // int height = 46;
        displayHandler->setTextColor(SSD1306_BLACK, SSD1306_WHITE);
        // displayHandler->drawRect(128-12, 15, 10, height, SSD1306_WHITE);

        // int dataHeight;
        // if(*settingStore >= defaultPoint){
        //     dataHeight = static_cast<double>((*settingStore-minValue)) / (maxValue-minValue) * height;
        // }

        // displayHandler->fillRect(128-12, 15+dataHeight, 10, height - dataHeight, SSD1306_WHITE);
    }
    else
    {
        displayHandler->setTextColor(SSD1306_WHITE);
    }
    displayHandler->setTextSize(1);
    displayHandler->setCursor(2, ypos);
    displayHandler->print(selected ? ">" : " ");
    displayHandler->print(displayName.c_str());
    displayHandler->print(":");
    displayHandler->print(*settingStore);
    if (superSelected)
    {
        displayHandler->print(" (E");
        displayHandler->print(static_cast<uint8_t>(log10(delta)));
        displayHandler->print(")");
    }
    displayHandler->println();
}

ButtonSetting::ButtonSetting(std::function<void()> handler, std::string displayName, Adafruit_SSD1306 *displayHandler)
{
    this->handler = handler;
    this->displayName = displayName;
    this->displayHandler = displayHandler;
}

void ButtonSetting::changeSetting(int delta)
{
    handler();
}

std::string ButtonSetting::getDisplayName()
{
    return displayName;
}

void ButtonSetting::displaySetting(int ypos, bool selected, bool superSelected, int delta)
{
    if (superSelected)
    {
        // int height = 46;
        displayHandler->setTextColor(SSD1306_BLACK, SSD1306_WHITE);
        // displayHandler->drawRect(128-12, 15, 10, height, SSD1306_WHITE);

        // int dataHeight;
        // if(*settingStore >= defaultPoint){
        //     dataHeight = static_cast<double>((*settingStore-minValue)) / (maxValue-minValue) * height;
        // }

        // displayHandler->fillRect(128-12, 15+dataHeight, 10, height - dataHeight, SSD1306_WHITE);
    }
    else
    {
        displayHandler->setTextColor(SSD1306_WHITE);
    }
    displayHandler->setTextSize(1);
    displayHandler->setCursor(2, ypos);
    displayHandler->print(selected ? ">" : " ");
    displayHandler->print(displayName.c_str());
    displayHandler->println();
}

void HMIManager::displayOff()
{
    displayHandler->clearDisplay();
    displayHandler->display();
    StateData::HMI::HMIDisplayEnabled = false;
    delay(500);
}