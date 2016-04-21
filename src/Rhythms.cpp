//
//  Rhythms.cpp
//  InAlveo
//
//  Created by euGs on 14/04/2016.
//
//

#include "Rhythms.h"

void Rhythms::setup(std::shared_ptr<InputDevice> input, int numPads, float padSmoothing, float hitThreshold, float hitHoldSeconds){
    this->input = input;
    for (int i=0; i<numPads; ++i){
        Pad pad;
        pad.setup(padSmoothing, hitThreshold, hitHoldSeconds);
        pads.emplace_back(pad);
    }
}

void Rhythms::update(float elapsedTime){
    input->update();
    
    if (pads.size() == 0){
        return 0.f;
    }
    
    for (int i=0; i<pads.size(); i++){
        pads[i].update(input->getNormalisedRawInput(i), elapsedTime);
        averageInput += pads[i].getSmoothedValue();
    }
    
    averageInput /= pads.size();
}

float Rhythms::getRhythmLevel(){
    return averageInput;
}

bool Rhythms::wasHit(){
    bool hit = false;
    
    for (auto it : pads){
        if (it.wasHit()){
            hit = true;
        }
    }
    return hit;
}