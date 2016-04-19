#pragma once

#include "ofMain.h"

class Sound {
public:
    void setup(string musicFile){
        soundPlayer.load(musicFile);
        soundPlayer.setLoop(true);
        level = 0.f;
        smoothing = .95f;
    }
    
    void play(){
        soundPlayer.play();
    }
    
    void update(){
        float newLevel = *(ofSoundGetSpectrum(1));
        level = level * smoothing + (1-smoothing) * newLevel;
    }
    
    float getLevel(){
        return level;
    }
    
private:
    ofSoundPlayer soundPlayer;
    float level, smoothing;
};