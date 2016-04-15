//
//  Rhythms.cpp
//  InAlveo
//
//  Created by euGs on 14/04/2016.
//
//

#include "Rhythms.h"

void Rhythms::setup(string device, int baud){
    arduino.connect(device, baud);
    ofAddListener(arduino.EInitialized, this, &Rhythms::setupArduino);

    pad0.setup(PadSmoothing);
}

void Rhythms::update(){
    arduino.update();
    calcRhythms();
    pad0.update();
}

float Rhythms::getRhythmLevel(){
    return pad0.getSmoothedValue();
}

void Rhythms::setupArduino(const int & version){
    ofRemoveListener(arduino.EInitialized, this, &Rhythms::setupArduino);
    arduino.sendAnalogPinReporting(0, ARD_ANALOG);
}

void Rhythms::calcRhythms(){
    float a0Normalised = arduino.getAnalog(0) / MaxPadHit;
    
    cout << a0Normalised << endl;
    if (a0Normalised > 0.f){
        pad0.setRawValue(a0Normalised);
    }
}