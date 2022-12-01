/**
    Class MyOledViewWorkingOFF :  Pour la gestion de l'afffichage du mode OFF sur notre écran OLED
    @file MyOledViewWorkingOFF.h 
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
        #include "MyOledViewWorkingOFF.h"
        MyOledViewWorkingOFF *myOledViewWorkingOFF = NULL;
        myOledViewWorkingOFF = new MyOledViewWorkingOFF();
        myOled->display(myOledViewWorkingOFF);


**/
#ifndef MYOLEDVIEWWORKINGOFF_H
#define MYOLEDVIEWWORKINGOFF_H

#include <Adafruit_SSD1306.h>
#include "MyOledViewWorking.h"
#include <string>
#include <vector>
using std::vector;

class MyOledViewWorkingOFF : public MyOledViewWorking {
    public:
        void setidDuSysteme(std::string val);
    private:
        std::string idDuSysteme;

        void display( Adafruit_SSD1306 *adafruit);
   };
#endif