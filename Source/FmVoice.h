/*
  ==============================================================================

    FmVoice.h
    Created: 6 Oct 2020 3:28:58pm
    Author:  Hayden Setlik

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "AlgorithmProcessor.h"

class FmSound : public juce::SynthesiserSound
{
public:
    bool appliesToNote(int /*midiNoteNumber*/) //just plays this sound for any midi note
    {
        return true;
    }
    bool appliesToChannel(int /*midiChannel*/) //plays the sound on both channels
    {
        return true;
    }
};
class FmVoice : public juce::SynthesiserVoice
{
public:
    FmVoice(int numOperators);
    
    bool canPlaySound(juce::SynthesiserSound* sound)
    {
        return dynamic_cast<FmSound*>(sound) != nullptr;
    }
    
    void startNote (int midiNoteNumber,
                    float velocity,
                    juce::SynthesiserSound *sound,
                    int currentPitchWheelPosition)
    {
        fundamental = juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber);
        for(int i = 0; i < operators.size(); ++i)
        {
            operators[i]->envelope.triggerOn();
        }
    }
    void stopNote (float velocity, bool allowTailOff)
    {
        for(int i = 0; i < operators.size(); ++i)
        {
            operators[i]->envelope.triggerOff();
        }
        allowTailOff = true;
        if(velocity == 0)
            clearCurrentNote();
    }
    void setEnvelope(
                     int operatorIndex,
                     std::atomic<float>* ratio,
                     std::atomic<float>* envDelay,
                     std::atomic<float>* envAttack,
                     std::atomic<float>* envHold,
                     std::atomic<float>* envDecay,
                     std::atomic<float>* envSustain,
                     std::atomic<float>* envRelease,
                     std::atomic<float>* level,
                     std::atomic<float>* modIndex,
                     std::atomic<float>* audible
                     )
    {
        operators[operatorIndex]->setRatio(*ratio);
        operators[operatorIndex]->setLevel(*level);
        operators[operatorIndex]->setModIndex(*modIndex);
        operators[operatorIndex]->setAudible(*audible);
        operators[operatorIndex]->envelope.setDelay(*envDelay);
        operators[operatorIndex]->envelope.setAttack(*envAttack);
        operators[operatorIndex]->envelope.setHold(*envHold);
        operators[operatorIndex]->envelope.setDecay(*envDecay);
        operators[operatorIndex]->envelope.setSustain(*envSustain);
        operators[operatorIndex]->envelope.setRelease(*envRelease);
    }
    void setSampleRate(double newRate)
    {
        for(int i = 0; i < operators.size(); ++i)
        {
            operators[i]->envelope.setSampleRate(newRate);
        }
    }
    void pitchWheelMoved(int newPitchWheelVal) {}
    //=============================================
    void controllerMoved(int controllerNumber, int controllerValue) {}
    //===============================================
    void aftertouchChanged (int newAftertouchValue) {}
    //==============================================
    void channelPressureChanged (int newChannelPressureValue) {}
    //===============================================
    void renderNextBlock (juce::AudioBuffer<float> &outputBuffer, int startSample, int numSamples);
    //==============================================
    void setCurrentPlaybackSampleRate (double newRate)
    {
        
    }
    float fundamental;
    juce::OwnedArray<Operator> operators;
};
