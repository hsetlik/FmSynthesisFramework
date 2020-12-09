/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "FmVoice.h"
#include "LayoutCreator.h"


const int numOperators = 6;
const int numVoices = 6;

//==============================================================================
class FmSynthesisFrameworkAudioProcessor  : public juce::AudioProcessor
{
public:
    //==============================================================================
    FmSynthesisFrameworkAudioProcessor();
    ~FmSynthesisFrameworkAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;
    
    juce::StringArray getPatchNames()
    {
        return allPatchNames;
    }
    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
    //==============================================================================
    void loadPatch(juce::XmlElement patch);
    //the 'save' button will bring up a dialog box to ask the user to overwrite the current patch or save with a new name
    //the callback of that save button will determine which of these two is called
    void updateExistingPatch();
    void saveNewPatch(juce::String newPatchName);
    //====================================================
    juce::AudioProcessorValueTreeState tree;
    FmVoice* thisVoice;
    juce::OwnedArray<juce::XmlElement> patchXmlElements;
private:
    juce::StringArray allPatchNames;
    juce::Identifier patchName;
    juce::XmlElement* currentXml;
    juce::Array<juce::File> patchFiles;
    juce::File* currentFile;
    juce::Synthesiser synth;
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FmSynthesisFrameworkAudioProcessor)
};
