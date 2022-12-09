/**
    Class MyOledViewWorkingHEAT :  Pour la gestion de l'afffichage du mode HEAT sur notre écran OLED
    @file MyOledViewWorkingHEAT.h 
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
        #include "MyOledViewWorkingHEAT.h"
        myOledViewWorkingHEAT *myOledViewWorkingHEAT = NULL;
        myOledViewWorkingHEAT = new MyOledViewWorkingHEAT();
        myOled->display(myOledViewWorkingHEAT);
        myOled->update(myOledViewWorkingHEAT);


**/
#ifndef MYOLEDVIEWWORKINGHEAT_H
#define MYOLEDVIEWWORKINGHEAT_H

#include <Adafruit_SSD1306.h>
#include "MyOledViewWorking.h"
#include <string>
#include <vector>
using std::vector;

class MyOledViewWorkingHEAT : public MyOledViewWorking {
    public:

    private:
        void display( Adafruit_SSD1306 *adafruit);
        void update(Adafruit_SSD1306 *adafruit);
   };
#endif