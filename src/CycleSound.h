#pragma once

#include "ofMain.h"

class CycleSound {
public:
    void setup(vector<string> musicFiles){
        for (musicFile : musicFiles){
            ofSoundPlayer soundPlayer;
            soundPlayer.load(musicFile);
            soundPlayers.emplace_back(soundPlayer);
        }
        this->it = soundPlayers.begin();
    }
    
    void play(){
        it->play();
        it++;
        if (it == soundPlayers.end()){
            it = soundPlayers.begin();
        }
    }
    
private:
    vector<string> musicFiles;
    vector<ofSoundPlayer> soundPlayers;
    vector<ofSoundPlayer>::iterator it;
};