/**
    Class MyOledViewInitialisation :  Pour la gestion de l'initialisation de notre écran OLED
    @file MyOledViewInitialisation.h 
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
        #include "MyOledViewInitialisation.h"
        MyOledViewInitialisation *myOledViewInitialisation = NULL;
        myOledViewInitialisation = new MyOledViewInitialisation();
        myOledViewInitialisation->setNomDuSysteme(nomDuSysteme.c_str());
        myOledViewInitialisation->setidDuSysteme(idDuSysteme.c_str());
        myOledViewInitialisation->setSensibiliteBoutonAction(SensibiliteBoutonAction.c_str());
        myOledViewInitialisation->setSensibiliteBoutonReset(SensibiliteBoutonReset.c_str());
        myOled->display(myOledViewInitialisation);
        myOled->update(myOledViewInitialisation);


**/
#ifndef MYOLEDVIEWINITIALISATION_H
#define MYOLEDVIEWINITIALISATION_H

#include <Adafruit_SSD1306.h>
#include "MyOledView.h"
#include <string>
#include <vector>
using std::vector;

class MyOledViewInitialisation : public MyOledView {
    public:
        virtual void setNomDuSysteme(std::string val);
        virtual void setidDuSysteme(std::string val);
        virtual void setSensibiliteBoutonAction(std::string val);
        virtual void setSensibiliteBoutonReset(std::string val);

    private:
        virtual void display( Adafruit_SSD1306 *adafruit) = 0;
        virtual void update(Adafruit_SSD1306 *adafruit) = 0;

        std::string nomDuSysteme = "";
        std::string idDuSysteme = "";
        std::string SensibiliteBoutonAction = "";
        std::string SensibiliteBoutonReset = "";
   };
#endif