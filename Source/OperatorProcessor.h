/*
  ==============================================================================

    OperatorProcessor.h
    Created: 6 Oct 2020 1:04:48pm
    Author:  Hayden Setlik

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "maximilian.h"
#include "DAHDSR.h"

class Operator
{
public:
    Operator(int opIndex) : index(opIndex)
    {
        isActive = false;
    }
    ~Operator() {}
    void addModSource(Operator* newSource)
    {
        modSources.push_back(newSource);
    }
    void removeModSource(Operator* sourceToRemove)
    {
        int removeIndex = sourceToRemove->getIndex();
        for(int i = 0; i < modSources.size(); ++i)
        {
            int checkIndex = modSources[i]->getIndex();
            if(removeIndex == checkIndex)
            {
                modSources.erase(modSources.begin() + i);
                break;
            }
        }
    }
    void setRatio(float newRatio)
    {
        ratio = newRatio;
    }
    void setLevel(float newLevel)
    {
        level = newLevel;
    }
    void setModIndex(float newIndex)
    {
        modIndex = newIndex;
    }
    int getIndex()
    {
        return index;
    }
    float sample(float fundamental);
    float lastOutputSample;
    bool isActive;
    DAHDSR envelope;
private:
    float ratio;
    float fundamental;
    float modIndex;
    float level;
    int index;
    std::vector<Operator*> modSources;
    maxiOsc osc;
};
