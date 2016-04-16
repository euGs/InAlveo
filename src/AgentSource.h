#pragma once

#include "Agent.h"

class AgentSource {
public:
    virtual void setup() = 0;
    virtual void reset() {};
    virtual unique_ptr<Agent> getAgent() = 0;
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