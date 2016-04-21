#pragma once

#include "ofMain.h"
#include "ofxAssimpModelLoader.h"
#include "Sound.h"
#include "Rhythms.h"
#include "Agents.h"
#include "AgentSource.h"
#include "VisualisationSource.h"
#include "AudioInput.h"
#include "ArduinoInput.h"

class ofApp : public ofBaseApp{
    
public:
    void setup();
    shared_ptr<InputDevice> setupInput();
    void update();
    void draw();
    void audioIn(float * input, int bufferSize, int nChannels);
    
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
    const float SpeedScaling = 5.f;
    const float VisualFeedbackScaling = 255.f;   // For flashing the screen when pad is hit.
    const int MaxAgents = 200;
    const float BirthCanalZ = -501;
    const float AgentsRadiusScaling = 1.7f;  // The radius of the sphere occupied by agents.
    const int NumPads = 2;
    const float PadSmoothing = .9f;
    const float HitThreshold = .08f;
    const float HitHoldSeconds = .2f;
    const float AudioMaxInput = 1.f;

    enum class InputType { Arduino, Audio };
    
    ofCamera cam;
    ofSoundPlayer babyBeats, mamaBeats, underwater;
    ofSoundStream soundStream;
    shared_ptr<AudioInput> audioInput;
    shared_ptr<ArduinoInput> arduinoInput;
    InputType inputType;
    
    Sound sound;
    Rhythms rhythms;
    float progress, speed;

    ofImage wombImage;
    ofImage birthCanalImage;
    ofPlanePrimitive wombSurface;
    ofCylinderPrimitive birthCanal;
    
    Agents agents;
    SphereRovingAgentSource agentSource;
    CrumpledPaperVisualisationSource visualisationSource;
};
