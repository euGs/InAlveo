#pragma once

#include "ofMain.h"
#include "Sound.h"
#include "Rhythms.h"
#include "ofxAssimpModelLoader.h"

class ofApp : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();
    
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseEntered(int x, int y);
    void mouseExited(int x, int y);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
protected:
    const float camDistance = 400.f;
    const float speedScaling = .01f;

    ofEasyCam cam;
    Sound sound;
    Rhythms rhythms;
    float progress, speed;
    ofxAssimpModelLoader birthCanalModel;
};
