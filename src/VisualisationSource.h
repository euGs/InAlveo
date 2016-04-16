#pragma once

#include "Visualisation.h"

class VisualisationSource {
public:
    virtual void setup(){
    }
    
    virtual unique_ptr<Visualisation> getVisualisation() = 0;
    virtual bool hasMoreVisualisations() = 0;
};

class SpriteVisualisationSource : public VisualisationSource {
public:
    void setImageFilename(string imageFilename){
        this->imageFilename = imageFilename;
    }
    
    virtual void setup(){
        if (imageFilename.empty()){
            ofLogWarning() << "SpriteVisualisationSource::setup()"
            << "Can't set up because imageFilename hasn't been set by client code"
            << endl;
            return;
        }
        
        image.load(imageFilename);
        
        planeResolution = 4;
    }
    
    virtual unique_ptr<Visualisation> getVisualisation() override{
        ofPlanePrimitive plane;
        setUpPlane(plane);
        unique_ptr<SpriteVisualisation> visualisation = make_unique<SpriteVisualisation>();
        visualisation->setup(plane, make_shared<ofTexture>(image.getTexture()));
        
        return move(visualisation);
    }
    
    virtual bool hasMoreVisualisations() override{
        return true;
    }
    
protected:
    string imageFilename;
    int planeResolution;
    ofImage image;
    
    void setUpPlane(ofPlanePrimitive & plane){
        plane.set(image.getWidth(), image.getHeight(), planeResolution, planeResolution);
        plane.mapTexCoords(0, 0, image.getWidth(), image.getHeight());
    }
};

class CrumpledPaperVisualisationSource : public SpriteVisualisationSource {
protected:
    virtual unique_ptr<Visualisation> getVisualisation() override{
        ofPlanePrimitive plane;
        setUpPlane(plane);
        unique_ptr<CrumpledPaperVisualisation> visualisation = make_unique<CrumpledPaperVisualisation>();
        visualisation->setup(plane, make_shared<ofTexture>(image.getTexture()));
        
        return move(visualisation);
    }

};
