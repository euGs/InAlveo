//
//  Trigger.h
//  InAlveo
//
//  Created by euGs on 14/04/2016.
//
//

#pragma once

// We don't control timing, assume (falsely) a steady frame rate
// for simplicity. In other words, smoothing is frame rate
// dependent.
class Trigger{
public:
    void setup(float smoothing){
        this->smoothing = smoothing;
        smoothedValue = 0.f;
        rawValue = 0.f;
    }
    
    void setRawValue(float rawValue){
        this->rawValue = rawValue;
    }
    
    float getSmoothedValue(){
        return smoothedValue;
    }
    
    void update(){
        smoothedValue = smoothedValue * smoothing + rawValue * (1-smoothing);
    }
    
protected:
    float smoothing, smoothedValue, rawValue;
};