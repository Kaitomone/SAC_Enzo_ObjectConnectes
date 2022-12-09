/**
    Gestion d'une VUE pour le OLed : Base pour les écrans de travail
    @file MyOledViewWorking.cpp
    @author Alain Dubé
    @version 1.1 20/11/20 
*/
#include <Arduino.h>
#include "MyOledViewErrorWifiConnexion.h"

using namespace std;

void MyOledViewErrorWifiConnexion::update(Adafruit_SSD1306 *adafruit){
    Serial.println("Update my view MyOledViewWorking");
    }

void MyOledViewErrorWifiConnexion::display( Adafruit_SSD1306 *adafruit) {
    adafruit->clearDisplay();

    adafruit->setCursor(0, 2);
    adafruit->setTextSize(2);
    adafruit->print(nomDuSysteme.c_str());

    adafruit->setCursor(0, 20);
    adafruit->setTextSize(1);
    adafruit->print("Id: ");
    adafruit->print(nomDuSysteme.c_str());

    adafruit->setCursor(0, 30);
    adafruit->print("Erreur lors de la connexion");

    adafruit->display();
    }