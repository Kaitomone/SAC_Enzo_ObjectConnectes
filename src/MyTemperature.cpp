/**
    Gestion de la température du Four (STUB)
    @file TemperatureStub.cpp
    @author Alain Dubé
    @version 1.0 17/03/21  
*/

#include "MyTemperature.h"

void MyTemperature::init(int _inputPinUsed, int _typeSensorUsed){
    inputPinUsed = _inputPinUsed;
    typeSensorUsed = _typeSensorUsed;

    dht = new DHT(inputPinUsed, typeSensorUsed);
    dht->begin();
    }

bool MyTemperature::setUniteUsed(int _UniteUsed){
   if((_UniteUsed>=0) && (_UniteUsed<=1)){
        UniteUsed = _UniteUsed;
        return(true);
        }
    return(false);
    }

//Return -999 if error
float MyTemperature::getTemperature(){
    float t = dht->readTemperature();
    // Check if any reads failed and exit early (to try again).
    if (isnan(t)) {
        t = lastTemperatureRead;
        }
    lastTemperatureRead = t;
    return(t);
    }