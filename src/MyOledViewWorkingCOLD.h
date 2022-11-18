/**
    Class MyOledViewWorkingCOLD :  Pour la gestion de l'afffichage du mode COLD sur notre écran OLED
    @file MyOledViewWorkingCOLD.h 
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
        #include "MyOledViewWorkingCOLD.h"
        MyOledViewWorkingCOLD *myOledViewWorkingCOLD = NULL;
        myOledViewWorkingCOLD = new MyOledViewWorkingCOLD();
        myOled->display(myOledViewWorkingCOLD);
        myOled->update(myOledViewWorkingCOLD);


**/
#ifndef MYOLEDVIEWWORKINGCOLD_H
#define MYOLEDVIEWWORKINGCOLD_H

#include <Adafruit_SSD1306.h>
#include "MyOledViewWorking.h"
#include <string>
#include <vector>
using std::vector;

class MyOledViewWorkingCOLD : public MyOledViewWorking {
    public:

    private:
        virtual void display( Adafruit_SSD1306 *adafruit) = 0;
        virtual void update(Adafruit_SSD1306 *adafruit) = 0;
   };
#endif