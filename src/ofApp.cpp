#include "ofApp.h"


/*
 Canal "beats" with the heart beat
 */

//--------------------------------------------------------------
void ofApp::setup(){
    float desiredDistance = 400.f;
    
    cam.setPosition(0.f, 0.f, desiredDistance);
    cam.setNearClip(0.1f);
    sound.setup("BabyBeats.wav");
    birthCanalModel.loadModel("BirthCanal.3ds");
    birthCanalModel.setPosition(0, 0, 0);
 
    progress = 25.f;
}

//--------------------------------------------------------------
void ofApp::update(){
    cam.setPosition(0.f, 0.f, progress);
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(255.f, 200.f, 200.f);
    
    cam.begin();
    ofSetColor(100.f, 0.f, 0.f, 100.f);
    birthCanalModel.drawFaces();
    cam.end();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    progress -= 1.f;
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
