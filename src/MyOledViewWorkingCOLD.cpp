/**
    Gestion d'une VUE pour le OLed : Base pour les écrans de travail
    @file MyOledViewWorking.cpp
    @author Alain Dubé
    @version 1.1 20/11/20 
*/
#include <Arduino.h>
#include "MyOledViewWorkingCOLD.h"

using namespace std;

void MyOledViewWorkingCOLD::update(Adafruit_SSD1306 *adafruit){
    Serial.println("Update my view MyOledViewWorking");
    }

void MyOledViewWorkingCOLD::display( Adafruit_SSD1306 *adafruit) {

    MyOledViewWorking::display(adafruit);

    //displayGifFire(adafruit, 80, 30);

    adafruit->setCursor(10, 30);
    adafruit->setTextSize(2);
    adafruit->print(getTag("temperature").c_str());

    adafruit->setCursor(80, 20);
    adafruit->setTextSize(1);
    adafruit->print("Waiting");

    adafruit->display();
    }