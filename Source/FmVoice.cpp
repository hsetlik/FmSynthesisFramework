/*
  ==============================================================================

    FmVoice.cpp
    Created: 6 Oct 2020 3:28:58pm
    Author:  Hayden Setlik

  ==============================================================================
*/

#include "FmVoice.h"

FmVoice::FmVoice(int numOperators) :  operatorCount(numOperators), fundamental(0.0f)
{
    for(int i = 0; i < numOperators; ++i)
    {
        operators.add(new Operator(i));
    }
    for(int n = 0; n < totalLfos; ++n)
    {
        lfoBank.add(new LfoProcessor(n));
    }
}

void FmVoice::renderNextBlock(juce::AudioBuffer<float> &outputBuffer, int startSample, int numSamples)
{
    for(int i = 0; i < numSamples; ++i)
    {
        applyModulations();
        for(int lfo = 0; lfo < 4; ++ lfo)
        {
            applyLfo(lfo);
        }
        float sum = 0.0f;
        for(int o = 0; o < operatorCount; ++o)
        {
            float newSample = operators[o]->sample(fundamental);
            if(operators[o]->isAudible)
                sum += newSample;
        }
        for(int channel = 0; channel < outputBuffer.getNumChannels(); ++channel)
        {
            outputBuffer.addSample(channel, startSample, sum);
        }
        ++startSample;
    }
}

void FmVoice::setRoutingFromGrid(juce::AudioProcessorValueTreeState *pTree)
{
    for(int source = 0; source < operatorCount; ++source)
    {
        auto sString = juce::String(source);
        for(int dest = 0; dest < operatorCount; ++dest)
        {
            auto dString = juce::String(dest);
            auto str = sString + "to" + dString + "Param";
            std::atomic<float>* value = pTree->getRawParameterValue(str);
            if(*value)
                routingParams[source][dest] = true;
            else
                routingParams[source][dest] = false;
        }
    }
}

void FmVoice::applyModulations()
{
    for(int i = 0; i < operatorCount; ++i)
    {
        operators[i]->cleanOffset();
    }
    for(int source = 0; source < operatorCount; ++source)
    {
        Operator* sourceOp = operators[source];
        for(int dest = 0; dest < operatorCount; ++dest)
        {
            Operator* destOp = operators[dest];
            if(routingParams[source][dest])
            {
                destOp->modOffset += sourceOp->lastOutputSample;
            }
        }
    }
}

void FmVoice::applyLfo(int index)
{
    LfoProcessor* thisLfo = lfoBank[index];
    float rawVal = thisLfo->getSampleValue();
    int thisTarget = thisLfo->currentTarget;
    thisTarget += 1;
    juce::String targetType;
    int targetOp;
    if(thisTarget > 2)
    {
        //determining the operator index
        if(thisTarget < 5)
            targetOp = 0;
        else if(thisTarget < 8)
            targetOp = 1;
        else if(thisTarget < 11)
            targetOp = 2;
        else if(thisTarget < 14)
            targetOp = 3;
        else if(thisTarget < 17)
            targetOp = 4;
        else if(thisTarget < 20)
            targetOp = 5;
        
        //determining the destination type
        if(thisTarget % 3 ==0)
        {
            targetType = "modIndex";
            auto preMod = operators[targetOp]->getModIndex();
            auto maxDelta = 200.0f - preMod;
            auto modDelta = maxDelta * rawVal;
            auto postMod = preMod + modDelta;
            operators[targetOp]->setModIndex(postMod);
        }
        else if(thisTarget % 3 == 1)
        {
            targetType = "level";
            auto preMod = operators[targetOp]->getLevel();
            auto maxDelta = 1.0f - preMod;
            auto modDelta = maxDelta * rawVal;
            auto postMod = preMod + modDelta;
            operators[targetOp]->setLevel(postMod);
        }
        else if(thisTarget % 3 == 2)
        {
            targetType = "ratio";
            auto preMod = operators[targetOp]->getRatio();
            auto maxDelta = 10.0f - preMod;
            auto modDelta = maxDelta * rawVal;
            auto postMod = preMod +  modDelta;
            operators[targetOp]->setRatio(postMod);
        }
    }
}
