#include "ofApp.h"


/*
 Canal "beats" with the heart beat
 */

//--------------------------------------------------------------
void ofApp::setup(){
    cam.setNearClip(0.1f);
    ofEnableDepthTest();
    
    sound.setup("BabyBeats.wav");
    rhythms.setup("/dev/cu.usbmodemfd121", 57600);

    wombImage.load("womb.png");
    wombSurface.set(wombImage.getWidth(), wombImage.getHeight());
    wombSurface.setOrientation({180.f, 0.f, 0.f});
    wombSurface.mapTexCoordsFromTexture(wombImage.getTexture());
    
    birthCanalImage.load("birthCanal.png");
    birthCanal.set(250, 1000);
    birthCanal.setPosition(0, 0, -501);
    birthCanal.setOrientation({90.f, 0.f, 0.f});
    birthCanal.setResolutionRadius(50);
    birthCanal.mapTexCoordsFromTexture(birthCanalImage.getTexture());
    
    visualisationSource.setImageFilename("SoftCircle.png");
    visualisationSource.setPlaneResolution(4);
    visualisationSource.setup();
    agentSource.setup();
    agents.setup(agentSource, visualisationSource, MaxAgents);
    
    progress = 300.f;
    speed = 0.f;
    
    sound.play();
}

//--------------------------------------------------------------
void ofApp::update(){
    rhythms.update();
    birthCanalImage.load("birthCanal.png");
    
    progress -= rhythms.getRhythmLevel() * SpeedScaling;
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
