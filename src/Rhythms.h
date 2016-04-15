//
//  Rhythms.h
//  InAlveo
//
//  Created by euGs on 14/04/2016.
//
//

#pragma once

#include "ofArduino.h"
#include "Trigger.h"

class Rhythms {
public:
    void setup(string device, int baud);
    void update();
    float getRhythmLevel();
    
protected:
    const float MaxPadHit = 1023.f;
    const float PadSmoothing = .9f;
    
    ofArduino arduino;
    Trigger pad0, pad1;
    
    void setupArduino(const int & version);
    void calcRhythms();
};