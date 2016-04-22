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
    firstSounds.load("FirstSounds.wav");
    
    inputType = InputType::Arduino;
    input = setupInput();

    rhythms.setup(input, NumPads, PadSmoothing, HitThreshold, HitHoldSeconds);

    wombImage.load("womb.png");
    wombSurface.set(wombImage.getWidth(), wombImage.getHeight());
    wombSurface.setOrientation({180.f, 0.f, 0.f});
    wombSurface.mapTexCoordsFromTexture(wombImage.getTexture());
    
    birthCanalImage.load("birthCanalHiRes.png");
    birthCanal.set(250, 1000);
    birthCanal.setPosition(0, 0, BirthCanalZ);
    birthCanal.setOrientation({90.f, 0.f, 2.5f});
    birthCanal.setResolutionRadius(50);
    birthCanal.mapTexCoordsFromTexture(birthCanalImage.getTexture());
    birthCanal.disableNormals();
    
    visualisationSource.setImageFilename("SoftCircle.png");
    visualisationSource.setPlaneResolution(4);
    visualisationSource.setup();
    agentSource.setup();
    agents.setup(agentSource, visualisationSource, MaxAgents);

    vaginaAgentsPlane.set(300, 600, 10, 10);
    vaginaAgentsSource.setup();
    vaginaAgentsSource.setMesh(make_shared<ofMesh>(vaginaAgentsPlane.getMesh()));
    vaginaAgentsSource.moveMesh({0.f, 0.f, -950.f});
    vaginaAgents.setup(vaginaAgentsSource, visualisationSource, MaxAgents);
    
    progress = ProgressInUtero;
    babyBeats.play();
    underwater.play();
    
    state = State::InLimbo;
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
    if (state == State::InLimbo){
        if (input->isReady()){
            fadeFinished = ofGetElapsedTimef() + FadeDurationSeconds;
            state = State::LimboToUtero;
        }
    } else if (state == State::LimboToUtero){
        if (ofGetElapsedTimef() > fadeFinished){
            state = State::InUtero;
        }
    } else if (state == State::InUtero) {
        if (progress < ProgressInAlveo){
            state = State::InAlveo;
        }
        updateNavigation();
    } else if (state == State::InAlveo){
        if (progress < ProgressInAere){
            state = State::InAere;
            fadeFinished = ofGetElapsedTimef() + FirstSoundsDurationSeconds;
            firstSounds.play();
            babyBeats.stop();
            underwater.stop();
        } else {
            updateNavigation();
        }
    } else if (state == State::InAere){
        if (ofGetElapsedTimef() < fadeFinished){
            progress -= 3.f;
        } else if (ofGetElapsedTimef() >= fadeFinished){
            state = State::LimboToUtero;
            fadeFinished = ofGetElapsedTimef() + FadeDurationSeconds;
            progress = ProgressInUtero;
            babyBeats.play();
            underwater.play();
        }
    }

    rhythms.update(ofGetElapsedTimef());
    agents.update(AgentsRadiusScaling);
    vaginaAgents.update(AgentsRadiusScaling);
    
    cam.setPosition(0.f, 0.f, progress);
}

//--------------------------------------------------------------
void ofApp::updateNavigation(){
    progress -= rhythms.getRhythmLevel() * SpeedScaling;
    if (rhythms.wasHit()){
        mamaBeats.play();
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(255.f);
    ofPushStyle();

    cam.begin();
    
    ofSetColor(255.f, ofMap(progress, -600.f, ProgressInAere, 255.f, 0.f, true));
    birthCanalImage.getTexture().bind();
    birthCanal.draw();
    birthCanalImage.getTexture().unbind();
    wombImage.getTexture().bind();
    wombSurface.drawFaces();
    wombImage.getTexture().unbind();
    
    if (state == State::InLimbo || state == State::LimboToUtero || state == State::InUtero){
        ofSetColor(255.f, 255.f, 200.f, 150.f);
        agents.draw();
    }

    float alpha = ofMap(progress, 0.f, ProgressInAere, 0.f, 255.f, true);
    alpha += sin(ofGetElapsedTimef()*10)*10.f;
    ofSetColor(222.f, 94.f, 107.f, alpha);
    vaginaAgents.draw();
    cam.end();
    
    if (state == State::InLimbo){
        ofSetColor(255.f);
    } else if (state == State::LimboToUtero){
        ofSetColor(255.f, ofMap(fadeFinished-ofGetElapsedTimef(), FadeDurationSeconds, 0.f, 255.f, 0.f, true));
    } else if (state == State::InUtero || state == State::InAlveo){
        ofSetColor(255.f, rhythms.getRhythmLevel() * VisualFeedbackScaling);
    } else if (state == State::InAere){
        ofSetColor(255.f, ofMap(fadeFinished-ofGetElapsedTimef(), FadeDurationSeconds, 0.f, 0.f, 255.f, true));
    }
    
    ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());
    
    ofSetColor(0, 0, 0);
    ofDrawBitmapString(ofGetFrameRate(), 20, 20);
    ofDrawBitmapString(rhythms.getRhythmLevel(), 20, 40);
    ofDrawBitmapString(progress, 20, 60);
    string text;
    if (state == State::InLimbo){
        text = "In Limbo";
    } else if (state == State::InUtero){
        text = "In Utero";
    } else if (state == State::InAlveo){
        text = "In Alveo";
    } else if (state == State::InAere){
        if (ofGetElapsedTimef() > fadeFinished){
            text = "Born";
        } else {
            text = "In Aere";
        }
    }
    ofDrawBitmapString(text, 20, 80);
    ofDrawBitmapString(ofGetElapsedTimef(), 160, 20);
    ofDrawBitmapString(fadeFinished, 160, 40);
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
    progress -= 20;
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
