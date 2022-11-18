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
    char strToPrint[128];

    adafruit->clearDisplay();

    adafruit->setCursor(0, 2);
    adafruit->setTextSize(2);
    adafruit->println(nomDuSysteme.c_str());

    adafruit->setCursor(0, 20);
    adafruit->setTextSize(1);
    sprintf(strToPrint, "Id: %s", idDuSysteme);
    adafruit->print(strToPrint);

    adafruit->setCursor(0, 30);
    adafruit->print("Initialisation");

    adafruit->setCursor(0, 40);
    sprintf(strToPrint, "Bouton RESET: %s", SensibiliteBoutonReset);
    adafruit->print(strToPrint);

    adafruit->setCursor(0, 50);
    sprintf(strToPrint, "Bouton ACTION: %s", SensibiliteBoutonAction);
    adafruit->print(strToPrint);

    adafruit->display();
    }