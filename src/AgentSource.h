#pragma once

#include "Agent.h"

class AgentSource {
public:
    virtual void setup() = 0;
    virtual void reset() {};
    virtual unique_ptr<Agent> getAgent() = 0;
};

class MeshRovingAgentSource : public AgentSource {
public:
    void setup() override{
    }
    
    void setMesh(shared_ptr<ofMesh> mesh){
        this->mesh = mesh;
    }
    
    void moveMesh(ofVec3f displacement){
        for (ofIndexType i=0; i<mesh->getNumVertices(); ++i){
            mesh->setVertex(i, mesh->getVertex(i)+displacement);
        }
    }
    
    virtual unique_ptr<Agent> getAgent() override{
        unique_ptr<MeshRovingAgent> agent = make_unique<MeshRovingAgent>();
        agent->setMesh(mesh);
        agent->setMinimumDistance(10.f);
        
        return move(agent);
    }
    
protected:
    shared_ptr<ofMesh> mesh;
};

class SphereRovingAgentSource : public AgentSource {
public:
    void setup() override{
    }
    
    unique_ptr<Agent> getAgent() override{
        return move(make_unique<SphereRovingAgent>());
    }
};

class PivotingSphereRovingAgentSource : public AgentSource {
public:
    void setup() override{
    }
    
    unique_ptr<Agent> getAgent() override{
        return move(make_unique<PivotingSphereRovingAgent>());
    }
};