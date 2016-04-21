//
//  Input.h
//  InAlveo
//
//  Created by euGs on 20/04/2016.
//
//

#pragma once

class InputDevice {
public:
    virtual void setup(float MaxInput){
        this->MaxInput = MaxInput;
    }
    
    virtual void update(){
    }
    
    virtual float getNormalisedRawInput(float channel) = 0;
    
protected:
    float MaxInput;
};