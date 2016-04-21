//
//  Rhythms.h
//  InAlveo
//
//  Created by euGs on 14/04/2016.
//
//

#pragma once

#include <memory>
#include <vector>

#include "InputDevice.h"
#include "Pad.h"

class Rhythms {
public:
    void setup(std::shared_ptr<InputDevice> input, int numPads, float padSmoothing, float hitThreshold, float hitHoldSeconds);
    void update(float elapsedTime);
    float getRhythmLevel();
    bool wasHit();
    
protected:
    std::shared_ptr<InputDevice> input;
    std::vector<Pad> pads;
    float averageInput;
};