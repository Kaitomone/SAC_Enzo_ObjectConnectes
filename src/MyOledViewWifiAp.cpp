/**
    Gestion d'une VUE pour le OLed : Base pour les écrans de travail
    @file MyOledViewWorking.cpp
    @author Alain Dubé
    @version 1.1 20/11/20 
*/
#include <Arduino.h>
#include "MyOledViewWifiAp.h"

using namespace std;

void MyOledViewWifiAp::setNomDuSysteme(std::string nom){
        nomDuSysteme = nom;
    }

void MyOledViewWifiAp::setssIDDuSysteme(std::string id){
        ssIDDuSysteme = id;
    }

void MyOledViewWifiAp::setPassDuSysteme(std::string id){
        passDuSysteme = id;
    }
    

void MyOledViewWifiAp::update(Adafruit_SSD1306 *adafruit){
    Serial.println("Update my view MyOledViewWorking");
    }

void MyOledViewWifiAp::display( Adafruit_SSD1306 *adafruit) {
    adafruit->clearDisplay();

    adafruit->setCursor(0, 2);
    adafruit->setTextSize(2);
    adafruit->print(nomDuSysteme.c_str());

    adafruit->setCursor(0, 20);
    adafruit->setTextSize(1);
    adafruit->print("Id: ");
    adafruit->print(nomDuSysteme.c_str());

    adafruit->setCursor(0, 30);
    adafruit->print("AP Configuration");

    adafruit->setCursor(15, 40);
    adafruit->print("SSID: ");
    adafruit->print(ssIDDuSysteme.c_str());
    
    adafruit->setCursor(15, 50);
    adafruit->print("PASS: ");
    adafruit->print(passDuSysteme.c_str());

    adafruit->display();
    }