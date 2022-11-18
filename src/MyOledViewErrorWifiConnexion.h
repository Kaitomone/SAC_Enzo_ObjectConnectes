/**
    Class MyOledViewErrorWifiConnexion :  Pour la gestion des erreurs lors de la connexion au Wifi
    @file MyOledViewErrorWifiConnexion.h 
    @author Enzo Richard
    @version 1.0 18/11/22 
    
    Historique des versions   
                            Versions  Date      Auteur      Description
                            1.0      21/09/20   Enzo        Première version de la classe
                            
                            
    platform = espressif32
    board = esp32doit-devkit-v1
    framework = arduino
    lib_deps = 
        Aucune
    Autres librairies (à copier dans le répertoire lib)
        Aucune
    
    Exemple d'utilisation 
        #include "MyOledViewErrorWifiConnexion.h"
        MyOledViewErrorWifiConnexion *myOledViewErrorWifiConnexion = NULL;
        myOledViewErrorWifiConnexion = new MyOledViewErrorWifiConnexion();
        myOledViewErrorWifiConnexion->setNomDuSysteme(nomDuSysteme.c_str());
        myOled->display(myOledViewErrorWifiConnexion);
        myOled->update(myOledViewErrorWifiConnexion);


**/
#ifndef MYOLEDVIEWERRORWIFICONNEXION_H
#define MYOLEDVIEWERRORWIFICONNEXION_H

#include <Adafruit_SSD1306.h>
#include "MyOledView.h"
#include <string>
#include <vector>
using std::vector;

class MyOledViewErrorWifiConnexion : public MyOledView {
    public:
        virtual void setNomDuSysteme(std::string val);

    private:
        virtual void display( Adafruit_SSD1306 *adafruit) = 0;
        virtual void update(Adafruit_SSD1306 *adafruit) = 0;

        std::string nomDuSysteme;
   };
#endif