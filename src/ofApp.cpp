#include "ofApp.h"


/*
 Canal "beats" with the heart beat
 */

//--------------------------------------------------------------
void ofApp::setup(){
    cam.setNearClip(0.1f);
    sound.setup("BabyBeats.wav");
    birthCanalModel.loadModel("BirthCanal.3ds");
    birthCanalModel.setPosition(0.f, 0.f, 0.f);
    birthCanalModel.setScale(100.f, 100.f, 100.f);
    rhythms.setup("/dev/cu.usbmodemfd121", 57600);
    
    visualisationSource.setImageFilename("SoftCircle.png");
    visualisationSource.setup();
    agentSource.setup();
    agents.setup(agentSource, visualisationSource, MaxAgents);
 
    progress = 300.f;
    speed = 0.f;
}

//--------------------------------------------------------------
void ofApp::update(){
    rhythms.update();
    
    progress -= rhythms.getRhythmLevel() * SpeedScaling;
    agents.update(static_cast<float>(ofGetMouseX())/800);

    cam.setPosition(0.f, 0.f, progress);
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(255.f);
    
    cam.begin();
    ofPushStyle();
    ofSetColor(100.f, 0.f, 0.f, 100.f);
    birthCanalModel.drawFaces();
    ofPopStyle();
    agents.draw();
    cam.end();
    
    ofPushStyle();
    ofSetColor(0, 0, 0);
    ofDrawBitmapString(ofGetFrameRate(), 20, 20);
    ofDrawBitmapString(ofGetMouseX(), 20, 40);
    ofPopStyle();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

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
