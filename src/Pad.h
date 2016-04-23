//
//  Pad.h
//  InAlveo
//
//  Created by euGs on 14/04/2016.
//
//

#pragma once

// We don't control timing, assume (falsely) a steady frame rate
// for simplicity. In other words, smoothing is frame rate
// dependent.
class Pad{
public:
    void setup(float smoothing, float hitThreshold, float hitHoldSeconds){
        this->smoothing = smoothing;
        this->hitThreshold = hitThreshold;
        this->hitHoldSeconds = hitHoldSeconds;
        smoothedValue = 0.f;
        rawValue = 0.f;
        lastHitTime = 0.f;
    }
    
    bool wasHit(){
        return hit;
    }
 
    float update(float rawValue, float elapsedTimeSeconds){
        this->rawValue = rawValue;
        this->elapsedTimeSeconds = elapsedTimeSeconds;
        
        smoothedValue = smoothedValue * smoothing + rawValue * (1-smoothing);
        hit = smoothedValue > hitThreshold && isHitGateOpen();
        
        if (hit){
            lastHitTime = elapsedTimeSeconds;
        }
    }
    
    float getSmoothedValue(){
        return smoothedValue;
    }

    
protected:
    float smoothing, smoothedValue, rawValue, hitThreshold, hitHoldSeconds, elapsedTimeSeconds, lastHitTime;
    bool hit;
    
    bool isHitGateOpen(){
        return elapsedTimeSeconds > lastHitTime + hitHoldSeconds;
    }
};