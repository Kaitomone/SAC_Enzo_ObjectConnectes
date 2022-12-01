/* Copyright (C) 2022 Enzo Richard
 * All rights reserved.
 *
 * Projet SAC Connectés
 * Ecole du Web
 * Cours Objets Connectés (c)2022
 *
    @file     main.cpp
    @author   Enzo Richard
    @version  1.5 25/11/2022
    @description
      Faire une application qui permet d'allumer un four pour faire sécher le bois,
      avec l'aide d'un écran OLED, d'un capteur de température DHT22 et des LEDs.
    platform = ESP32
    OS : Arduino
    Langage : C++
    Historique des versions
        Version    Date       Auteur            Description
        1.1        09/09/22   Enzo              Première version du logiciel
        1.2        15/09/22   Enzo              Intégration serveur WEB et affichage de notre page
        1.3        10/11/22   Enzo              Allumage des LED et Fonctionnent écran OLED
        1.4        18/11/22   Enzo              Ajout des fonctions pour les différents affichage de notre écran OLED et ajout 
                                                de la classe BOUTON
        1.5        25/11/22   Enzo              Les vues OLED fonctionne et s'affiche correctement                                       

    Fonctionnalités implantées
        Fonctionnement des LEDs
        Gestion du senseur de température
        Gestion écran OLED
        Gestion boutons

    Configuration du système
        GPIO12 : pin 12   Rouge 
        GPIO14 : pin 27   Vert                              
        GPIO27 : pin 14   Jaune  

    Senseur de température et d'humidité DHT22
      MyTemperature                 V1.0
        GPIO : 15 
    
    Écran OLED
        GPIO SDA : 21
        GPIO SCL : 22

    MyButton                        V1.0  Pour gérer un (ou des) bouton(s) Touch de l'ESP32 
        GPIO33 : T9                       Pour le bouton RESET    : Reset le ESP 
        GPIO32 : T8                       Pour le bouton ACTION   : Fait une action  
 */

#include <Arduino.h>
#include <Wire.h>
#include <String>
#include <sstream>

#include "myFunctions.cpp" //fonctions utilitaires

using namespace std;

// Gestion des LEDs
#define GPIO_PIN_LED_LOCK_RED 12 // Led Rouge GPIO12
#define GPIO_PIN_LED_OK_GREEN 27 // Led Verte GPIO27
#define GPIO_PIN_LED_HEAT_YELLOW 14 // Led Jaune GPIO14

// Gestion senseur température
#include "MyTemperature.h"

#define DHTPIN  4   // Pin utilisée par le senseur DHT22
#define DHTTYPE DHT22  //Le type de senseur utilisé (mais ce serait mieux d'avoir des DHT22 pour plus de précision)
MyTemperature *myTemperature = NULL;

// Récupérer la température
float tempFour = 23;
char strTemperature[64];

// Gestion écran OLED
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#include <Adafruit_SSD1306.h>
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

#include <MyOled.h>
// Gestion écran OLED
MyOled *myOled = NULL;

#include <MyOledView.h>
MyOledView *myOledView = NULL;

#include "MyOledViewInitialisation.h"
MyOledViewInitialisation *myOledViewInitialisation = NULL;
string nomDuSysteme = "Sac System";
string idDuSysteme = "696969";

#include "MyOledViewWifiAp.h"
MyOledViewWifiAp *myOledViewWifiAp = NULL;

#include "MyOledViewErrorWifiConnexion.h"
MyOledViewErrorWifiConnexion *myOledViewErrorWifiConnexion = NULL;

#include "MyOledViewWorking.h"
MyOledViewWorking *myOledViewWorking = NULL;

#include "MyOledViewWorkingCOLD.h"
MyOledViewWorkingCOLD *myOledViewWorkingCOLD = NULL;

#include "MyOledViewWorkingHEAT.h"
MyOledViewWorkingHEAT *myOledViewWorkingHEAT = NULL;

#include "MyOledViewWorkingOFF.h"
MyOledViewWorkingOFF *myOledViewWorkingOFF = NULL;

#include <WiFiManager.h>
#include <HTTPClient.h>
WiFiManager wm;
#define WEBSERVER_H

//Pour la gestion du serveur ESP32
#include "MyServer.h"
MyServer *myServer = NULL; 

//Variable pour la connection Wifi
const char *SSID = "SAC_";
const char *PASSWORD = "sac_";
String ssIDRandom;

// Gestion des boutons
#include "MyButton.h"
MyButton *myButtonAction = NULL;
MyButton *myButtonReset = NULL;

int currentTempFour = 0;
string etat = "OFF";


// On créer notre CallBack qui va recevoir les messages envoyés depuis la page WEB
std::string CallBackMessageListener(string message) {
  while(replaceAll(message, std::string("  "), std::string(" ")));

  /* Envoyer la température du four*/
  string actionToDo1 = getValue(message, ' ', 0);
  std::string tempDuFour = strTemperature; //Lire le senseur de température
  if (string(actionToDo1.c_str()).compare(string("askTempFour")) == 0) {
      return(tempDuFour); 
  }
  std::string result = "";
  return result;
  }

void setup() {
  
  Serial.begin(115200);

  // Initialisation des LEDs
  pinMode(GPIO_PIN_LED_LOCK_RED, OUTPUT);
  pinMode(GPIO_PIN_LED_OK_GREEN, OUTPUT);
  pinMode(GPIO_PIN_LED_HEAT_YELLOW, OUTPUT);

  //Initialisation senseur de température
  myTemperature = new MyTemperature;
  myTemperature->init(DHTPIN, DHTTYPE); //Pin 4 et Type DHT22

  myOled = new MyOled(&Wire, -1, 64, 128);
  myOled->init();

  myOledViewInitialisation = new MyOledViewInitialisation();
  myOledViewInitialisation->setNomDuSysteme(nomDuSysteme.c_str());
  myOledViewInitialisation->setidDuSysteme(idDuSysteme.c_str());
  myOledViewInitialisation->setSensibiliteBoutonAction("??????");
  myOledViewInitialisation->setSensibiliteBoutonReset("??????");
  myOled->displayView(myOledViewInitialisation);

  char strButtonAction[64];
  //Initialisation des boutons
  myButtonAction = new MyButton();        //Pour lire le bouton actions
  myButtonAction->init(T8);
  int sensibilisationButtonAction = myButtonAction->autoSensibilisation();
  sprintf(strButtonAction, "%d", sensibilisationButtonAction);

  char strButtonReset[64];
  myButtonReset = new MyButton();         //Pour lire le bouton hard reset
  myButtonReset->init(T9);
  int sensibilisationButtonReset = myButtonReset->autoSensibilisation();
  sprintf(strButtonReset, "%d", sensibilisationButtonReset);

  myOledViewInitialisation->setSensibiliteBoutonAction(strButtonAction);
  myOledViewInitialisation->setSensibiliteBoutonReset(strButtonReset);
  myOled->displayView(myOledViewInitialisation);

  //Connection au WifiManager
  String ssIDRandom, PASSRandom;
  String stringRandom;
  stringRandom = get_random_string(4).c_str();
  ssIDRandom = SSID;
  ssIDRandom = ssIDRandom + stringRandom;
  stringRandom = get_random_string(4).c_str();
  PASSRandom = PASSWORD;
  PASSRandom = PASSRandom + stringRandom;

  char strToPrint[128];
  sprintf(strToPrint, "Identification : %s   MotDePasse: %s", ssIDRandom, PASSRandom);
  Serial.println(strToPrint);

  myOledViewWifiAp = new MyOledViewWifiAp();
  myOledViewWifiAp->setNomDuSysteme(nomDuSysteme.c_str());
  myOledViewWifiAp->setssIDDuSysteme(ssIDRandom.c_str());
  myOledViewWifiAp->setPassDuSysteme(PASSRandom.c_str());

  myOledViewErrorWifiConnexion = new MyOledViewErrorWifiConnexion();

  if (!wm.autoConnect(ssIDRandom.c_str(), PASSRandom.c_str())){
          Serial.println("Erreur de connexion.");
          myOled->displayView(myOledViewErrorWifiConnexion);
          }
  else {
      Serial.println("Connexion Établie.");
      myOled->displayView(myOledViewWifiAp);
      for (int i=0;i<2;i++){
        digitalWrite(GPIO_PIN_LED_LOCK_RED, HIGH);
        digitalWrite(GPIO_PIN_LED_HEAT_YELLOW, HIGH);
        digitalWrite(GPIO_PIN_LED_OK_GREEN, HIGH);
        delay(1000);
        digitalWrite(GPIO_PIN_LED_LOCK_RED, LOW);
        digitalWrite(GPIO_PIN_LED_HEAT_YELLOW, LOW);
        digitalWrite(GPIO_PIN_LED_OK_GREEN, LOW);
        delay(1000);
      }
      
      }

  // ----------- Routes du serveur ----------------
  myServer = new MyServer(80);
  myServer->initAllRoutes();
  myServer->initCallback(&CallBackMessageListener);
}

void displayGoodScreen(){
  delay(10);

  sprintf(strTemperature, "%g", tempFour);

  if(isEqualString(etat.c_str(), string("HEAT"))) myOled->updateCurrentView(myOledViewWorkingHEAT);

  if(isEqualString(etat.c_str(), string("OFF"))) {
    digitalWrite(GPIO_PIN_LED_LOCK_RED, LOW);
    digitalWrite(GPIO_PIN_LED_OK_GREEN, HIGH);
    digitalWrite(GPIO_PIN_LED_HEAT_YELLOW, LOW);
    myOledViewWorkingOFF = new MyOledViewWorkingOFF();
    myOledViewWorkingOFF->setParams("nomDuSysteme", nomDuSysteme);
    myOledViewWorkingOFF->setParams("idDuSysteme", idDuSysteme);
    myOledViewWorkingOFF->setParams("ipDuSysteme", WiFi.localIP().toString().c_str());
    myOledViewWorkingOFF->setParams("temperature", strTemperature);
    myOled->displayView(myOledViewWorkingOFF);
    currentTempFour = tempFour;
  }

  if(isEqualString(etat.c_str(), string("COLD"))) {
    digitalWrite(GPIO_PIN_LED_LOCK_RED, LOW);
    digitalWrite(GPIO_PIN_LED_OK_GREEN, LOW);
    digitalWrite(GPIO_PIN_LED_HEAT_YELLOW, HIGH);
    myOledViewWorkingCOLD = new MyOledViewWorkingCOLD();
    myOledViewWorkingCOLD->setParams("nomDuSysteme", nomDuSysteme);
    myOledViewWorkingCOLD->setParams("idDuSysteme", idDuSysteme);
    myOledViewWorkingCOLD->setParams("ipDuSysteme", WiFi.localIP().toString().c_str());
    myOledViewWorkingCOLD->setParams("temperature", strTemperature);
    myOled->displayView(myOledViewWorkingCOLD);
    currentTempFour = tempFour;

  }

  if(isEqualString(etat.c_str(), string("HEAT"))) {
    digitalWrite(GPIO_PIN_LED_LOCK_RED, HIGH);
    digitalWrite(GPIO_PIN_LED_OK_GREEN, LOW);
    digitalWrite(GPIO_PIN_LED_HEAT_YELLOW, LOW);

    myOledViewWorkingHEAT = new MyOledViewWorkingHEAT();
    myOledViewWorkingHEAT->setParams("nomDuSysteme", nomDuSysteme);
    myOledViewWorkingHEAT->setParams("idDuSysteme", idDuSysteme);
    myOledViewWorkingHEAT->setParams("ipDuSysteme", WiFi.localIP().toString().c_str());
    myOledViewWorkingHEAT->setParams("temperature", strTemperature);
    myOled->displayView(myOledViewWorkingHEAT);
    currentTempFour = tempFour;
  }
}

void loop() {
  
  // Fonctionnement senseur de température
  tempFour = myTemperature->getTemperature();

  // On regarde si la température du senseur est supérieur ou égale à notre températureCible
  Serial.print("Température : ");
  Serial.println(tempFour);

  sprintf(strTemperature, "%g", tempFour);

  if (tempFour <= 25)
  {
    etat = "OFF";
  }
  else if (tempFour > 25 && tempFour <= 28)
  {
    etat = "COLD";
  }
  else
  {
    etat = "HEAT";
  }
  
  displayGoodScreen();

  delay(1000);
}
