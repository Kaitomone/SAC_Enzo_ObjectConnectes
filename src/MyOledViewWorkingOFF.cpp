/**
    Gestion d'une VUE pour le OLed : Base pour les écrans de travail
    @file MyOledViewWorking.cpp
    @author Alain Dubé
    @version 1.1 20/11/20 
*/
#include <Arduino.h>
#include "MyOledViewWorkingOFF.h"
using namespace std;

void MyOledViewWorkingOFF::display( Adafruit_SSD1306 *adafruit) {

    MyOledViewWorking::display(adafruit);

    adafruit->setCursor(10, 30);
    adafruit->setTextSize(2);
    adafruit->print(getTag("temperature").c_str());

    adafruit->setCursor(80, 20);
    adafruit->setTextSize(1);
    adafruit->print("Ready");

    adafruit->display();
    }