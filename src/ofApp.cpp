#include "ofApp.h"


/*
 Canal "beats" with the heart beat
 */

//--------------------------------------------------------------
void ofApp::setup(){
    cam.setPosition(0.f, 0.f, camDistance);
    cam.setNearClip(0.1f);
    sound.setup("BabyBeats.wav");
    birthCanalModel.loadModel("BirthCanal.3ds");
    birthCanalModel.setPosition(0, 0, 0);
    rhythms.setup("/dev/cu.usbmodemfd121", 57600);
 
    progress = 0.f;
    speed = 0.f;
}

//--------------------------------------------------------------
void ofApp::update(){
    rhythms.update();
    
    progress -= rhythms.getRhythmLevel() * speedScaling;
    cam.setPosition(0.f, 0.f, progress);
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(255.f);
    
    cam.begin();
    ofSetColor(100.f, 0.f, 0.f, 100.f);
    birthCanalModel.drawFaces();
    cam.end();
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
