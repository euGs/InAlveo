#pragma once

#include "ofMain.h"
#include "Rhythms.h"
#include "Agents.h"
#include "AgentSource.h"
#include "VisualisationSource.h"
#include "AudioInput.h"
#include "ArduinoInput.h"
#include "CycleSound.h"

class ofApp : public ofBaseApp{
    
public:
    void setup();
    shared_ptr<InputDevice> setupInput();
    void update();
    void updateNavigation();
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
    const int MaxAgents = 100;
    const float BirthCanalZ = -501;
    const float AgentsRadiusScaling = 1.7f;  // The radius of the sphere occupied by agents.
    const int NumPads = 2;
    const float PadSmoothing = .9f;
    const float HitThreshold = .08f;
    const float HitHoldSeconds = .2f;
    const float AudioMaxInput = 1.f;
    const float ProgressInUtero = 555.f;
    const float ProgressInAlveo = 0.f;
    const float ProgressInAere = -800.f;
    const float ProgressFadeBirthCanal = -400.f;
    const float FadeDurationSeconds = 2.f;
    const float FirstSoundsDurationSeconds = 8.f;

    enum class InputType { Arduino, Audio };
    enum class State { InLimbo, LimboToUtero, InUtero, InAlveo, InAere };
    
    State state;
    ofEasyCam cam;
    ofSoundPlayer babyBeats, mamaBeats, underwater, firstSounds;
    CycleSound cycleMamaBeats;
    ofSoundStream soundStream;
    shared_ptr<AudioInput> audioInput;
    shared_ptr<ArduinoInput> arduinoInput;
    shared_ptr<InputDevice> input;
    InputType inputType;
    
    Rhythms rhythms;
    float progress;
    float fadeFinished;

    ofImage wombImage;
    ofImage birthCanalImage;
    ofPlanePrimitive wombSurface;
    ofCylinderPrimitive birthCanal;
    
    ofPlanePrimitive vaginaAgentsPlane;
    Agents agents, vaginaAgents;
    MeshRovingAgentSource vaginaAgentsSource;
    SphereRovingAgentSource agentSource;
    CrumpledPaperVisualisationSource visualisationSource;
};
