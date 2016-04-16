#pragma once

#include "ofMain.h"
#include "ofxAssimpModelLoader.h"
#include "Sound.h"
#include "Rhythms.h"
#include "Agents.h"
#include "AgentSource.h"
#include "VisualisationSource.h"

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
    const float SpeedScaling = 5.f;
    const float VisualFeedbackScaling = 255.f;   // For flashing the screen when pad is hit.
    const int MaxAgents = 100;
    const float BirthCanalZ = 645;
    const float AgentsRadiusScaling = .8f;  // The radius of the area occupied by agents.

    ofEasyCam cam;
    Sound sound;
    Rhythms rhythms;
    float progress, speed;
    ofxAssimpModelLoader birthCanalModel;
    Agents agents;
    SphereRovingAgentSource agentSource;
    CrumpledPaperVisualisationSource visualisationSource;
};
