#pragma once

#include "ofMain.h"

class Visualisation {
public:
    virtual void draw(ofVec3f position, ofVec3f orientationEuler) = 0;
    virtual void drawWithoutColor(ofVec3f position, ofVec3f orientationEuler) {
    };
    virtual void bringItHome(float durationSeconds) {
    };
};

class SpriteVisualisation : public Visualisation {
public:
    virtual void setup(ofPlanePrimitive plane, shared_ptr<ofTexture> texture){
        this->plane = plane;
        this->texture = texture;
    }

    virtual void draw(ofVec3f position, ofVec3f orientationEuler){
        plane.setPosition(position);
        plane.setOrientation(orientationEuler);
        texture->bind();
        plane.draw();
        texture->unbind();
    }
    
    virtual void drawWithoutColor(ofVec3f position, ofVec3f orientationEuler){
        plane.setPosition(position);
        plane.setOrientation(orientationEuler);
        plane.draw();
    }

protected:
    shared_ptr<ofTexture> texture;
    ofPlanePrimitive plane;
};

class TornPaperVisualisation : public SpriteVisualisation {
public:
    virtual void setup(ofPlanePrimitive plane, shared_ptr<ofTexture> texture){
        SpriteVisualisation::setup(plane, texture);
        
        ofMesh & mesh = this->plane.getMesh();
        float maxDisplacement = plane.getWidth();

        for (size_t i=0; i<mesh.getNumVertices(); i++){
            ofVec3f displacement(ofRandom(maxDisplacement), ofRandom(maxDisplacement), ofRandom(maxDisplacement));
            ofVec3f vertex = mesh.getVertex(i);
            vertex += displacement;

            mesh.setVertex(i, vertex);
        }
    }
};

// A visualisation that is like crumpled paper in its normal state but
// can uncrumple back to flat paper on command.
class CrumpledPaperVisualisation : public TornPaperVisualisation {
public:
    virtual void setup(ofPlanePrimitive plane, shared_ptr<ofTexture> texture) override{
        // Cache the original flat mesh.
        ofMesh & mesh = plane.getMesh();
        flatMesh = mesh;
        
        for (size_t i=0; i<mesh.getNumVertices(); i++){
            flatMesh.setVertex(i, mesh.getVertex(i));
        }
        
        // Let TornPaperVisualisation do the crumpling.
        TornPaperVisualisation::setup(plane, texture);
        
        // Cache the crumpled mesh.
        mesh = this->plane.getMesh();
        crumpledMesh = mesh;

        for (size_t i=0; i<mesh.getNumVertices(); i++){
            crumpledMesh.setVertex(i, mesh.getVertex(i));
        }
    }
    
    virtual void bringItHome(float normalisedHomeness) override{
        ofMesh & mesh = plane.getMesh();
        
        for (int i=0; i<mesh.getNumVertices(); i++){
            ofVec3f vertex = flatMesh.getVertex(i) - crumpledMesh.getVertex(i);

            mesh.setVertex(i, crumpledMesh.getVertex(i) + vertex*normalisedHomeness);
        }
    }
    
protected:
    ofMesh flatMesh, crumpledMesh;
};