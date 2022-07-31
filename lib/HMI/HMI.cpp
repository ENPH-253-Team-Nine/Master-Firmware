#include "HMI.h"

using namespace HMI;

HMIManager::HMIManager(){
    //wire2 = new TwoWire(PB10, PB11);
    this->displayHandler = new Adafruit_SSD1306(screenWidth,screenHeight,&Wire,oledReset);
    StateData::HMI::settingSelectIndex = 2;
    settings[settingsEnum::SETTING_TESTONE] = new IntSetting(&StateData::testSettingOne,1024,-1024,"Test 1", displayHandler);
    settings[settingsEnum::SETTING_TESTTWO] = new IntSetting(&StateData::testSettingTwo,1024,-1024,"Test 2", displayHandler);
    settings[settingsEnum::SETTING_TESTTHREE] = new IntSetting(&StateData::testSettingThree, 1024, -1024,"Test 3", displayHandler);
    settings[settingsEnum::SETTING_TESTFOUR] = new IntSetting(&StateData::testSettingFour,1024,-1024,"Test 4", displayHandler);
    settings[settingsEnum::SETTING_TESTFIVE] = new IntSetting(&StateData::testSettingFive,1024,-1024,"Test 5", displayHandler);
    settings[settingsEnum::SETTING_TESTSIX] = new IntSetting(&StateData::testSettingSix,1024,-1024,"Test 6", displayHandler);



}

void HMIManager::setup(){
    //wire2->begin();
    displayHandler->begin(SSD1306_SWITCHCAPVCC, 0x3C);
    displayHandler->clearDisplay();
    for(uint8_t i=screenHeight/2-2; i>0; i--){
        displayHandler->clearDisplay();
        drawFrame(i);
        displayHandler->display();
        delay(1);
    }
}

void HMIManager::poll(){
    displayHandler->clearDisplay();
    drawFrame(0);
    drawTitleBar();
    if(StateData::HMI::settingSelectIndex>=settingsEnum::_LENGTH){
        StateData::HMI::settingSelectIndex = settingsEnum::_LENGTH-1;
    }
    else if(StateData::HMI::settingSelectIndex<0){
        StateData::HMI::settingSelectIndex = 0;
    }
    StateData::testSettingThree = StateData::HMI::settingSelectIndex;

    if(StateData::HMI::settingSelectIndex>=2) settings[StateData::HMI::settingSelectIndex-2]->displaySetting(15,false);
    if(StateData::HMI::settingSelectIndex>=1) settings[StateData::HMI::settingSelectIndex-1]->displaySetting(25,false);
    settings[StateData::HMI::settingSelectIndex]->displaySetting(35,true);
    if(StateData::HMI::settingSelectIndex+1<settingsEnum::_LENGTH) settings[StateData::HMI::settingSelectIndex+1]->displaySetting(45,false);
    if(StateData::HMI::settingSelectIndex+2<settingsEnum::_LENGTH) settings[StateData::HMI::settingSelectIndex+2]->displaySetting(55,false);



    displayHandler->display();
}

void HMIManager::drawFrame(uint8_t frameOffset){ 
    displayHandler->drawRect(frameOffset,frameOffset,screenWidth-frameOffset*2, screenHeight-frameOffset*2,SSD1306_WHITE);
}

void HMIManager::drawTitleBar(){
    displayState();
    displayHandler->drawFastHLine(1,10,screenWidth-2,SSD1306_WHITE);
    int ledColor = StateData::mockLED == true ? SSD1306_WHITE : SSD1306_BLACK;
    displayHandler->fillCircle(screenWidth-6, 5, 3, ledColor);
}

void HMIManager::displayState(){
    displayHandler->setTextSize(1);
    displayHandler->setCursor(2,2);
    displayHandler->setTextColor(SSD1306_WHITE);
    switch(*StateData::state){
        case StateMachine::StateEnum::Error:
            displayHandler->invertDisplay(false);
            break;
        default:
            displayHandler->invertDisplay(true);          
            break;
    }
    displayHandler->print("(");
    displayHandler->print(StateData::HMI::settingSelectIndex);
    displayHandler->print(") ");
    displayHandler->print("State:");
    displayHandler->println(StateData::debugStateName.c_str());


}







//settings

IntSetting::IntSetting(int* settingStore, int maxValue, int minValue, std::string displayName, Adafruit_SSD1306* displayHandler)
{
    this->settingStore = settingStore;
    this->maxValue = maxValue;
    this->minValue = minValue;
    this->displayName = displayName;
    this->displayHandler = displayHandler;
}

void IntSetting::changeSetting(int delta)
{
    *settingStore+=delta;
}

std::string IntSetting::getDisplayName(){
    return displayName;
}

void IntSetting::displaySetting(int ypos, bool selected){
    displayHandler->setTextSize(1);
    displayHandler->setCursor(2,ypos);
    displayHandler->print(selected ? ">" :" ");
    displayHandler->print(displayName.c_str());
    displayHandler->print(":");
    displayHandler->println(*settingStore);

    /*if(selected){
        displayHandler->setTextColor(SSD1306_BLACK,SSD1306_WHITE); 
    }
    else{
        displayHandler->setTextColor(SSD1306_WHITE); 
    }*/
}

