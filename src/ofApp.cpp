#include "ofApp.h"

/*
 Canal "beats" with the heart beat
 */

//--------------------------------------------------------------
void ofApp::setup(){
    cam.setNearClip(0.1f);
    ofEnableDepthTest();
    
    babyBeats.load("BabyBeats.wav");
    babyBeats.setLoop(true);
    mamaBeats.load("MamaBeats.wav");
    underwater.load("Underwater.wav");
    underwater.setLoop(true);
    
    inputType = InputType::Arduino;
    shared_ptr<InputDevice> input = setupInput();

    rhythms.setup(input, NumPads, PadSmoothing, HitThreshold, HitHoldSeconds);

    wombImage.load("womb.png");
    wombSurface.set(wombImage.getWidth(), wombImage.getHeight());
    wombSurface.setOrientation({180.f, 0.f, 0.f});
    wombSurface.mapTexCoordsFromTexture(wombImage.getTexture());
    
    birthCanalImage.load("birthCanal.png");
    birthCanal.set(250, 1000);
    birthCanal.setPosition(0, 0, BirthCanalZ);
    birthCanal.setOrientation({90.f, 0.f, 2.5f});
    birthCanal.setResolutionRadius(50);
    birthCanal.mapTexCoordsFromTexture(birthCanalImage.getTexture());
    
    visualisationSource.setImageFilename("SoftCircle.png");
    visualisationSource.setPlaneResolution(4);
    visualisationSource.setup();
    agentSource.setup();
    agents.setup(agentSource, visualisationSource, MaxAgents);
    
    progress = 600.f;
    speed = 0.f;
    
    babyBeats.play();
    underwater.play();
}

//--------------------------------------------------------------
shared_ptr<InputDevice> ofApp::setupInput(){
    if (inputType == InputType::Arduino){
        arduinoInput = make_shared<ArduinoInput>();
        arduinoInput->setup(1023.f, "/dev/tty.usbmodemfa131", 57600);
        return arduinoInput;
    } else if (inputType == InputType::Audio){
        soundStream.setup(this, 0, 2, 44100, 256, 4);
        audioInput = make_shared<AudioInput>();
        audioInput->setup(AudioMaxInput);
        return audioInput;
    }
}

//--------------------------------------------------------------
void ofApp::update(){
    rhythms.update(ofGetElapsedTimef());
    birthCanalImage.load("birthCanal.png");
    
    progress -= rhythms.getRhythmLevel() * SpeedScaling;
    if (rhythms.wasHit()){
        mamaBeats.play();
    }
    agents.update(AgentsRadiusScaling);
    
    cam.setPosition(0.f, 0.f, progress);
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(255.f);
    
    cam.begin();
    birthCanalImage.getTexture().bind();
    birthCanal.draw();
    birthCanalImage.getTexture().unbind();
    wombImage.getTexture().bind();
    wombSurface.drawFaces();
    wombImage.getTexture().unbind();
    ofPushStyle();
    ofSetColor(255.f, 255.f, 200.f, 150.f);
    agents.draw();
    ofPopStyle();
    cam.end();
    
    ofPushStyle();
    ofSetColor(255.f, rhythms.getRhythmLevel() * VisualFeedbackScaling);
    ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());
    ofPopStyle();
    
    if (rhythms.wasHit()){
        mamaBeats.play();
    }
    
    ofPushStyle();
    ofSetColor(0, 0, 0);
    ofDrawBitmapString(ofGetFrameRate(), 20, 20);
    ofDrawBitmapString(rhythms.getRhythmLevel(), 20, 40);
    ofPopStyle();
}

//--------------------------------------------------------------
void ofApp::audioIn(float * input, int bufferSize, int nChannels){
    if (inputType == InputType::Audio){
        audioInput->audioIn(input, bufferSize, nChannels);
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    mamaBeats.play();
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){
    
}
