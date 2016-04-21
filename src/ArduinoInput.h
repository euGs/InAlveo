//
//  ArduinoInput.h
//  InAlveo
//
//  Created by euGs on 20/04/2016.
//
//

#pragma once

#include "InputDevice.h"
#include "ofEventUtils.h"

class ArduinoInput : public InputDevice {
public:
    void setup(float MaxInput, string device, int baud){
        InputDevice::setup(MaxInput);
        arduino.connect(device, baud);
        ofAddListener(arduino.EInitialized, this, &ArduinoInput::setupArduino);
    }
    
    virtual void update() override{
        arduino.update();
    }

    virtual float getNormalisedRawInput(float channel) override{
        if (MaxInput == 0.f){
            return 0.f;
        }
        
        return arduino.getAnalog(channel) / MaxInput;
    }

protected:
    ofArduino arduino;

    void setupArduino(const int & version){
        ofRemoveListener(arduino.EInitialized, this, &ArduinoInput::setupArduino);
        arduino.sendAnalogPinReporting(0, ARD_ANALOG);
        arduino.sendAnalogPinReporting(1, ARD_ANALOG);
    }
};