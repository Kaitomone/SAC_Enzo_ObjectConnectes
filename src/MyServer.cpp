/**
    Gestion d'un serveur WEB
    @file MyServer.cpp
    @author Alain Dubé
    @version 1.1 20/11/20 
*/
#include <Arduino.h>
#include "MyServer.h"
using namespace std;

typedef std::string (*CallbackType)(std::string);
CallbackType MyServer::ptrToCallBackFunction = NULL;

//Exemple pour appeler une fonction CallBack
//if (ptrToCallBackFunction) (*ptrToCallBackFunction)(stringToSend); 
void MyServer::initCallback(CallbackType callback) {
    ptrToCallBackFunction = callback;
    }

String processor(const String& var){
    float currentTemperature = 3.3f;
    if (var == "DATA_TEMP"){
    return String(currentTemperature);
    }
    return String();
}

void MyServer::initAllRoutes() { 
    //Initialisation du SPIFF.
    if (!SPIFFS.begin(true)) {
        Serial.println("An Error has occurred while mounting SPIFFS");
        return;
        }

    //Route initiale (page html)
    this->on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
        request->send(SPIFFS, "/index.html", "text/html");
        });

    this->on("/leddartech", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send(SPIFFS, "/leddartech.png", "image/png");
        });

    //Route du script JavaScript
    this->on("/script.js", HTTP_GET, [](AsyncWebServerRequest *request) {
        request->send(SPIFFS, "/script.js", "text/javascript");
        });
   
    this->onNotFound([](AsyncWebServerRequest *request){
        request->send(404, "text/plain", "Page Not Found");
        });

    this->on("/getTemp", HTTP_GET, [](AsyncWebServerRequest *request){
        AsyncResponseStream *response = request->beginResponseStream("text/html");
        AsyncWebParameter* p = request->getParam(0);
        char buffer[1024];

        sprintf(buffer, "%s %s", "changement getTemp", p->value().c_str());

        if (ptrToCallBackFunction) (*ptrToCallBackFunction) (buffer);
        
    });


    this->begin();

    
};

