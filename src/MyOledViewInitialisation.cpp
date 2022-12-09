/**
    Gestion d'une VUE pour le OLed : Base pour les écrans de travail
    @file MyOledViewWorking.cpp
    @author Enzo Richard
    @version 1.1 20/11/20 
*/
#include <Arduino.h>
#include "MyOledViewInitialisation.h"

using namespace std;

void MyOledViewInitialisation::setNomDuSysteme(std::string nom){
        nomDuSysteme = nom;
    }

void MyOledViewInitialisation::setidDuSysteme(std::string id){
        idDuSysteme = id;
    }

void MyOledViewInitialisation::setSensibiliteBoutonAction(std::string sensibiliteBoutonAction){
        SensibiliteBoutonAction = sensibiliteBoutonAction;
    }

void MyOledViewInitialisation::setSensibiliteBoutonReset(std::string sensibiliteBoutonReset){
        SensibiliteBoutonReset = sensibiliteBoutonReset;
    }

void MyOledViewInitialisation::update(Adafruit_SSD1306 *adafruit){
    Serial.println("Update my view MyOledViewWorking");
    }

void MyOledViewInitialisation::display(Adafruit_SSD1306 *adafruit) {
    char strToPrint[32];
    adafruit->clearDisplay();
    
    adafruit->setCursor(0, 2);
    adafruit->setTextSize(2);
    adafruit->print(nomDuSysteme.c_str());

    adafruit->setCursor(0, 20);
    adafruit->setTextSize(1);
    adafruit->print("Id: ");
    adafruit->print(idDuSysteme.c_str());

    adafruit->setCursor(0, 30);
    adafruit->print("Initialisation");

    adafruit->setCursor(0, 40);
    adafruit->print("Bouton RESET: ");
    adafruit->print(SensibiliteBoutonReset.c_str());

    adafruit->setCursor(0, 50);
    adafruit->print("Bouton ACTION: ");
    adafruit->print(SensibiliteBoutonAction.c_str());

    adafruit->display();
    }