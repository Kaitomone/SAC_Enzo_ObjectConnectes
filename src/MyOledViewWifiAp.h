/**
    Class MyOledViewWifiAp :  Pour la gestion de la connexion Wifi de notre ESP32
    @file MyOledViewWifiAp.h 
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
        #include "MyOledViewWifiAp.h"
        MyOledViewWifiAp *myOledViewWifiAp = NULL;
        myOledViewWifiAp = new MyOledViewWifiAp();
        myOledViewWifiAp->setNomDuSysteme(nomDuSysteme.c_str());
        myOledViewWifiAp->setssIDDuSysteme(ssIDDuSysteme.c_str());
        myOledViewWifiAp->setPassDuSysteme(passDuSysteme.c_str());
        myOled->display(myOledViewWifiAp);
        myOled->update(myOledViewWifiAp);


**/
#ifndef MYOLEDVIEWWIFIAP_H
#define MYOLEDVIEWWIFIAP_H

#include <Adafruit_SSD1306.h>
#include "MyOledView.h"
#include <string>
#include <vector>
using std::vector;

class MyOledViewWifiAp : public MyOledView {
    public:
        void setNomDuSysteme(std::string val);
        void setssIDDuSysteme(std::string val);
        void setPassDuSysteme(std::string val);

    private:
        void display( Adafruit_SSD1306 *adafruit);
        void update(Adafruit_SSD1306 *adafruit);

        std::string nomDuSysteme;
        std::string ssIDDuSysteme;
        std::string passDuSysteme;
   };
#endif