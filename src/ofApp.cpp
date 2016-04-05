#include "ofApp.h"


/*
 Canal "beats" with the heart beat
 */

//--------------------------------------------------------------
void ofApp::setup(){
    float desiredDistance = 400.f;
    
    cam.setPosition(0.f, 0.f, desiredDistance);
    sound.setup("BabyBeats.wav");
    birthCanalModel.loadModel("BirthCanal.3ds");
    
    progress = 0.f;
}

//--------------------------------------------------------------
void ofApp::update(){
    cam.setPosition(0.f, 0.f, ofGetMouseX());
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(255.f, 255.f, 255.f);
    
    float xFactor, yFactor;
    
    xFactor = 1.f;
    xFactor += (progress <  .25f) ? ofMap(progress, 0.f, 0.25f, 1.f, 0.f) : 0.f ;
    yFactor = 1.f;
    yFactor += (progress > .75f) ? ofMap(progress, .75f, 1.f, 0.f, 1.f) : 0.f;
    
    cam.begin();
    ofSetColor(100.f, 0.f, 0.f);
    //    ofDrawEllipse(0.f, 0.f, 300.f * xFactor, 300.f * yFactor);
    //    ofDrawCylinder(0.f, 0.f, 0.f, 100, 100);
    birthCanalModel.setPosition(0, 0, 0);
    birthCanalModel.drawFaces();
    cam.end();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    progress += .05f;
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
