//
//  AudioInput.h
//  InAlveo
//
//  Created by euGs on 20/04/2016.
//
//

#pragma once

#include "InputDevice.h"
#include "ofSoundStream.h"

class AudioInput : public InputDevice {
public:
    virtual void setup(float MaxInput) override{
        InputDevice::setup(MaxInput);
    }
    
    virtual float getNormalisedRawInput(float channel){
        if (MaxInput == 0.f){
            return 0.f;
        }
        
        return rawInput / MaxInput;
    }
    
    virtual bool isReady() override{
        return true;
    }
    
    void audioIn(float * input, int bufferSize, int nChannels){
        if (bufferSize == 0){
            rawInput = 0.f;
            return;
        }
        
        // Take an average input.
        float rawInputSum = 0.f;
        
        for (int i = 0; i < bufferSize; i++){
            rawInputSum += abs(input[i]);
        }
        
        rawInput = rawInputSum / bufferSize;
    }
    
protected:
    float rawInput;
};