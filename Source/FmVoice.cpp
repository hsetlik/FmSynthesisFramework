/*
  ==============================================================================

    FmVoice.cpp
    Created: 6 Oct 2020 3:28:58pm
    Author:  Hayden Setlik

  ==============================================================================
*/

#include "FmVoice.h"

FmVoice::FmVoice(int numOperators)
{
    for(int i = 0; i < numOperators; ++i)
    {
        operators.add(new Operator(i));
    }
}

void FmVoice::renderNextBlock(juce::AudioBuffer<float> &outputBuffer, int startSample, int numSamples)
{
    for(int i = 0; i < numSamples; ++i)
    {
        float sum = 0.0f;
        for(int o = 0; o < operators.size(); ++o)
        {
            float newSample = operators[i]->sample(fundamental);
            if(operators[i]->isAudible)
                sum += newSample;
        }
        for(int channel = 0; channel < outputBuffer.getNumChannels(); ++channel)
        {
            outputBuffer.addSample(channel, startSample, sum);
        }
        ++startSample;
    }
}
