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
        1.1        09/09/22   Enzo & Alexis     Première version du logiciel
        1.2        15/09/22   Enzo & Alexis     Intégration serveur WEB et affichage de notre page

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
#include "MyTemperature.h"
#include <WiFiManager.h>
#include "myFunctions.cpp" //fonctions utilitaires

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
#define DHTPIN  4   // Pin utilisée par le senseur DHT22
#define DHTTYPE DHT22  //Le type de senseur utilisé (mais ce serait mieux d'avoir des DHT22 pour plus de précision)
TemperatureStub *temperatureStub = NULL;

// Notre tempéatureCible
int tempFour = 23;

// Gestion écran OLED
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

//Variable pour la connection Wifi
const char *SSID = "SAC_";
const char *PASSWORD = "sac_";
String ssIDRandom;

// On créer notre CallBack qui va recevoir les messages envoyés depuis la page WEB
std::string CallBackMessageListener(string message) {
  while(replaceAll(message, std::string("  "), std::string(" ")));

  //Décortiquer le message
  string actionToDo = getValue(message, ' ', 0);
  Serial.print(message.c_str());
  std::string tempDuFour = "22"; //Lire le senseur de température
  if (string(actionToDo.c_str()).compare(string("askTempFour ")) == 0) { 
    Serial.print(tempDuFour.c_str());
    return(tempDuFour.c_str()); }
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
  temperatureStub = new TemperatureStub;
  temperatureStub->init(DHTPIN, DHTTYPE); //Pin 15 et Type DHT11

  //Initialisation écran OLED
  display.begin();
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }

  display.clearDisplay();

  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 10);
  // Display static text
  display.println("Initialisation");
  display.display(); 
  display.clearDisplay();

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
      }

  // ----------- Routes du serveur ----------------
  myServer = new MyServer(80);
  myServer->initAllRoutes();
  myServer->initCallback(&CallBackMessageListener);
}

void loop() {
  
  // Fonctionnement senseur de température
  float t = temperatureStub->getTemperature();
  // On regarde si la température du senseur est supérieur ou égale à notre températureCible
  Serial.print("Température : ");
  Serial.println(t);

  tempFour = t;

  // display.clearDisplay();
  // display.setCursor(0, 10);
  // display.setTextSize(3);

  Serial.println("Oui");
  digitalWrite(GPIO_PIN_LED_LOCK_RED, HIGH);
  digitalWrite(GPIO_PIN_LED_HEAT_YELLOW, HIGH);
  digitalWrite(GPIO_PIN_LED_OK_GREEN, HIGH);

  // char strTemp [64];

  // sprintf(strTemp, "%g C", t);

  // display.println(strTemp);
  // display.display();
      
  delay(1000);
}
