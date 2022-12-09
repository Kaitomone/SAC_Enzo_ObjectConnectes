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
    float currentTemperature = 2.2f;
    if (var == "DATA_TEMP"){
    return String(currentTemperature);
    }
    return String();
}

String processor2(const String& var){
    int currentCompteurFour;
    if (var == "DATA_COMPTEUR"){
    return String(currentCompteurFour);
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

    this->on("/sac.png", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send(SPIFFS, "/sac.png", "image/png");
        });

    //Route du script JavaScript
    this->on("/script.js", HTTP_GET, [](AsyncWebServerRequest *request) {
        request->send(SPIFFS, "/script.js", "text/javascript");
        });
   
    this->onNotFound([](AsyncWebServerRequest *request){
        request->send(404, "text/plain", "Page Not Found");
        });

    // Envoi la température au service WEB
    this->on("/lireTemp", HTTP_GET, [](AsyncWebServerRequest *request) {
        std::string repString = "";
        if (ptrToCallBackFunction) repString = (*ptrToCallBackFunction)("askTempFour");
        String lireTempDuFour =String(repString.c_str());
        request->send(200, "text/plain", lireTempDuFour );
    });

    // Appel l'api pour récupérer les bois
    this->on("/getNomBois", HTTP_GET, [](AsyncWebServerRequest *request) {
        Serial.println("getNomBois... ");

        HTTPClient http;
        String woodApiRestAdress = "http://51.79.84.135:2223/api/woodlist";
        String response = "Error";
        bool beginResult = http.begin(woodApiRestAdress);
        if(!beginResult){
            Serial.println("Erreur lors de la connection au serveur");
        }
        else{
            Serial.println("Connection au serveur réussie");
            http.addHeader("authorization", "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJ1c2VybmFtZSI6ImFsYSIsImlhdCI6MTY2MTUxNjAzNX0.4eGrq5XuJM1AcFnrxsRLHZp7e7E6v_u8lh6gEVAoU0Q");
            http.GET();
            response = http.getString();
            Serial.println(response);
            http.end();
        }

        request->send(200, "text/plain", response);
    });

    // Appel l'api pour envoyer les détails du bois
    this->on("/getDetailsBois", HTTP_GET, [](AsyncWebServerRequest *request) {
        if(request->hasParam("id")){
            AsyncWebParameter* p = request->getParam("id");
            HTTPClient http;
            String woodApiRestAdress = "http://51.79.84.135:2223/api/drying?id=" + p->value();
            String response = "Error";
            bool beginResult = http.begin(woodApiRestAdress);
            if(!beginResult){
                Serial.println("Erreur lors de la connection au serveur");
            }
            else{
                Serial.println("Connection au serveur réussie");
                http.addHeader("authorization", "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJ1c2VybmFtZSI6ImFsYSIsImlhdCI6MTY2MTUxNjAzNX0.4eGrq5XuJM1AcFnrxsRLHZp7e7E6v_u8lh6gEVAoU0Q");
                http.GET();
                response = http.getString();
                Serial.println(response);
                http.end();
            }

            request->send(200, "text/plain", response);
        }
        else{
            request->send(400, "text/plain", "Erreur : Paramètres manquant");
        };
    });

    // Récupère la température cible et le temps de séchage
    this->on("/setTempSechEtCible", HTTP_GET, [](AsyncWebServerRequest *request){
        AsyncResponseStream *response = request->beginResponseStream("text/html");
        AsyncWebParameter* p1 = request->getParam(0);
        AsyncWebParameter* p2 = request->getParam(1);
        char buffer[1024];

        sprintf(buffer, "%s %s %s", "changement setTempSechEtCible", p1->value().c_str(), p2->value().c_str());

        if (ptrToCallBackFunction) (*ptrToCallBackFunction) (buffer);
        
    });

    // Permet de savoir si on appuyer sur le bouton de démarrage
    this->on("/demarrerFour", HTTP_GET, [](AsyncWebServerRequest *request){
        AsyncResponseStream *response = request->beginResponseStream("text/html");
        char buffer[1024];

        sprintf(buffer, "%s", "changement demarrerFour");

        if (ptrToCallBackFunction) (*ptrToCallBackFunction) (buffer);
        
    });

    // Envoie le compteur au service WEB
    this->on("/lireCompteur", HTTP_GET, [](AsyncWebServerRequest *request) {
        std::string repString = "";
        if (ptrToCallBackFunction) repString = (*ptrToCallBackFunction)("askCompteurFour");
        String lireCompteurFour =String(repString.c_str());
        request->send(200, "text/plain", lireCompteurFour );
    });

    this->begin();

    
};

