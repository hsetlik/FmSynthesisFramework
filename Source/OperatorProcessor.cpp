/*
  ==============================================================================

    OperatorProcessor.cpp
    Created: 6 Oct 2020 1:04:48pm
    Author:  Hayden Setlik

  ==============================================================================
*/

#include "OperatorProcessor.h"

float Operator::sample(float fundamental) 
{
    auto baseFreq = fundamental * ratio;
    auto finalFreq = baseFreq + (modOffset * modIndex);
    auto fullAmp = osc.sinebuf(finalFreq);
    lastOutputSample = envelope.process(fullAmp * level);
    return lastOutputSample;
}

void Operator::applyLfoMod(int targetId, float value)
{
    if(targetId == (3 * index) + 2)
    {
        ratio += value;
    }
    else if (targetId == (3 * index) + 3)
    {
        modIndex += value;
    }
    else if(targetId == (3 * index) + 4)
    {
        level += value;
    }
}

