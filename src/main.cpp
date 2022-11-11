/* Copyright (C) 2022 Enzo Richard
 * All rights reserved.
 *
 * Projet SAC Connectés
 * Ecole du Web
 * Cours Objets Connectés (c)2022
 *
    @file     main.cpp
    @author   Enzo Richard
    @version  1.1 09/09/2022
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

    Fonctionnalités implantées
        Clignotement des LEDs
        Gestion du senseur de température
      
      Configuration du système
            GPIO12 : pin 12   Rouge 
            GPIO14 : pin 14  Vert                              
            GPIO27 : pin 27  Jaune  

      Senseur de température et d'humidité DHT22
        MyTemperature                 V1.0
            GPIO : 15 
      
      Écran OLED
            GPIO SDA : 21
            GPIO SCL : 22
 */

#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <String>
#include <sstream>

#include <WiFiManager.h>
#include "myFunctions.cpp" //fonctions utilitaires
#include <MyOled.h>

using namespace std;

#include <HTTPClient.h>
#include <WiFiManager.h>
WiFiManager wm;
#define WEBSERVER_H

//Pour la gestion du serveur ESP32
#include "MyServer.h"
MyServer *myServer = NULL; 

// Gestion des LEDs
#define GPIO_PIN_LED_LOCK_RED 12 // Led Rouge GPIO12
#define GPIO_PIN_LED_OK_GREEN 14 // Led Verte GPIO14
#define GPIO_PIN_LED_HEAT_YELLOW 27 // Led Jaune 27

// Gestion senseur température
#include "MyTemperature.h"
#define DHTPIN  4   // Pin utilisée par le senseur DHT22
#define DHTTYPE DHT22  //Le type de senseur utilisé (mais ce serait mieux d'avoir des DHT22 pour plus de précision)
MyTemperature *myTemperature = NULL;

// Récupérer la température
float tempFour = 23;
char strTemperature[64];

// Gestion écran OLED
MyOled *myOled = NULL;

//Variable pour la connection Wifi
const char *SSID = "SAC_";
const char *PASSWORD = "sac_";
String ssIDRandom;


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
  myTemperature->init(DHTPIN, DHTTYPE); //Pin 15 et Type DHT11

  //Initialisation écran OLED
  myOled = new MyOled(&Wire, -1, 64, 128);
  myOled->init();

  myOled->clearDisplay();

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


  if (!wm.autoConnect(ssIDRandom.c_str(), PASSRandom.c_str())){
          Serial.println("Erreur de connexion.");
      
          }
  else {
      Serial.println("Connexion Établie.");
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

void loop() {
  
  // Fonctionnement senseur de température
  tempFour = myTemperature->getTemperature();

  // On regarde si la température du senseur est supérieur ou égale à notre températureCible
  Serial.print("Température : ");
  Serial.println(tempFour);

  sprintf(strTemperature, "%g", tempFour);

  // Affichage de la température en mode HEATING
  myOled->clearDisplay();
  myOled->setCursor(0, 2);
  myOled->setTextSize(2);
  myOled->println("SAC System");
  myOled->setCursor(0, 20);
  myOled->setTextSize(1);
  myOled->print("Id: 568657");
  myOled->setCursor(85, 20);
  myOled->print("Heating");
  myOled->setCursor(10, 35);
  myOled->setTextSize(2);
  myOled->print(strTemperature);
  myOled->setCursor(60, 35);
  myOled->printSpecialChar("o", 1);
  myOled->setCursor(72, 35);
  myOled->println("C");
  myOled->setCursor(20, 55);
  myOled->setTextSize(1);
  myOled->print("192.168.16.1");
  myOled->display();
      
  delay(1000);
}
