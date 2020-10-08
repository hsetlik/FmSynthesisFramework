/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

juce::AudioProcessorValueTreeState::ParameterLayout createLayout(int numOperators)
{
    juce::AudioProcessorValueTreeState::ParameterLayout layout;
    for(int i = 0; i < numOperators; ++i)
    {
        juce::String iStr = juce::String(i);
        //strings and parameters for the operator
        auto ratioId = "ratioParam" + iStr;
        auto ratioName = "Operator " + iStr + " ratio";
        auto levelId = "levelParam" + iStr;
        auto levelName = "Operator " + iStr + " level";
        auto indexId = "indexParam" + iStr;
        auto indexName = "Operator " + iStr + " Mod Index";
        auto outputId = "audibleParam" + iStr;
        auto outputName = "Operator " + iStr + " audible";
        juce::NormalisableRange<float> ratioRange(0.0f, 10.0f, 0.01f, 0.5f);
        ratioRange.setSkewForCentre(1.0f);
        layout.add(std::make_unique<juce::AudioParameterFloat>(ratioId, ratioName, ratioRange, 1.0f));
        layout.add(std::make_unique<juce::AudioParameterFloat>(levelId, levelName, 0.0f, 1.0f, 1.0f));
        layout.add(std::make_unique<juce::AudioParameterFloat>(indexId, indexName, 0.0f, 200.0f, 0.0f));
        layout.add(std::make_unique<juce::AudioParameterBool>(outputId, outputName, false));
        //and for the envelope
        auto delayId = "delayParam" + iStr;
        auto delayName = "Operator " + iStr + " delay";
        auto attackId = "attackParam" + iStr;
        auto attackName = "Operator " + iStr + " attack";
        auto holdId = "holdParam" + iStr;
        auto holdName = "Operator " + iStr + " hold";
        auto decayId = "decayParam" + iStr;
        auto decayName = "Operator " + iStr + " decay";
        auto sustainId = "sustainParam" + iStr;
        auto sustainName = "Operator " + iStr + " sustain";
        auto releaseId = "releaseParam" + iStr;
        auto releaseName = "Operator " + iStr + " release";
        juce::NormalisableRange<float> timeRange1(1.0f, 20000.0f, 0.1f, 0.5f);
        timeRange1.setSkewForCentre(1000.0f);
        juce::NormalisableRange<float> timeRange2(1.0f, 20000.0f, 0.1f, 0.5f);
        timeRange2.setSkewForCentre(5000.0f);
        layout.add(std::make_unique<juce::AudioParameterFloat>(delayId, delayName, timeRange2, 0.0f));
        layout.add(std::make_unique<juce::AudioParameterFloat>(attackId, attackName, timeRange1, 20.0f));
        layout.add(std::make_unique<juce::AudioParameterFloat>(holdId, holdName, timeRange1, 0.0f));
        layout.add(std::make_unique<juce::AudioParameterFloat>(decayId, decayName, timeRange2, 100.0f));
        layout.add(std::make_unique<juce::AudioParameterFloat>(sustainId, sustainName, 0.0f, 1.0f , 1.0f));
        layout.add(std::make_unique<juce::AudioParameterFloat>(releaseId, releaseName, timeRange2, 40.0f));
        //bools for modulation paths
        for(int n = 0; n < numOperators; ++n)
        {
            juce::String nStr = juce::String(n);
            auto modId = iStr + "to" + nStr + "Param";
            auto modName = "Operator " + iStr + " to " + nStr;
            layout.add(std::make_unique<juce::AudioParameterBool>(modId, modName, false));
        }
    }
    return layout;
}

//==============================================================================
FmSynthesisFrameworkAudioProcessor::FmSynthesisFrameworkAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       ), tree(*this, nullptr, "ALL PARAMETERS", createLayout(numOperators))
#endif
{
    for(int i = 0; i < numVoices; ++i)
    {
        synth.addVoice(new FmVoice(numOperators));
    }
    synth.clearSounds();
    synth.addSound(new FmSound());
}

FmSynthesisFrameworkAudioProcessor::~FmSynthesisFrameworkAudioProcessor()
{
}

//==============================================================================
const juce::String FmSynthesisFrameworkAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool FmSynthesisFrameworkAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool FmSynthesisFrameworkAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool FmSynthesisFrameworkAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double FmSynthesisFrameworkAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int FmSynthesisFrameworkAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int FmSynthesisFrameworkAudioProcessor::getCurrentProgram()
{
    return 0;
}

void FmSynthesisFrameworkAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String FmSynthesisFrameworkAudioProcessor::getProgramName (int index)
{
    return {};
}

void FmSynthesisFrameworkAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void FmSynthesisFrameworkAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    juce::ignoreUnused(samplesPerBlock);
    synth.setCurrentPlaybackSampleRate(sampleRate);
    for(int i = 0; i < synth.getNumVoices(); ++i)
    {
        FmVoice* voice = dynamic_cast<FmVoice*>(synth.getVoice(i));
        voice->setSampleRate(sampleRate);
    }
}

void FmSynthesisFrameworkAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool FmSynthesisFrameworkAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void FmSynthesisFrameworkAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    for(int voice = 0; voice < synth.getNumVoices(); ++ voice)
    {
        if((thisVoice =  dynamic_cast<FmVoice*>(synth.getVoice(voice))))
        {
            thisVoice->setRoutingFromGrid(&tree);
            for(int i = 0; i < numOperators; ++i)
            {
                auto iStr = juce::String(i);
                auto ratioId = "ratioParam" + iStr;
                auto levelId = "levelParam" + iStr;
                auto modIndexId = "indexParam" + iStr;
                auto audibleId = "audibleParam" + iStr;
                
                auto delayId = "delayParam" + iStr;
                auto attackId = "attackParam" + iStr;
                auto holdId = "holdParam" + iStr;
                auto decayId = "decayParam" + iStr;
                auto sustainId = "sustainParam" + iStr;
                auto releaseId = "releaseParam" + iStr;
                
                thisVoice->setParameters(i, tree.getRawParameterValue(ratioId),
                                         tree.getRawParameterValue(levelId),
                                         tree.getRawParameterValue(modIndexId),
                                         tree.getRawParameterValue(audibleId),
                                         tree.getRawParameterValue(delayId),
                                         tree.getRawParameterValue(attackId),
                                         tree.getRawParameterValue(holdId),
                                         tree.getRawParameterValue(decayId),
                                         tree.getRawParameterValue(sustainId),
                                         tree.getRawParameterValue(releaseId)
                                        );
            }
        }
    }
    synth.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());
}

//==============================================================================
bool FmSynthesisFrameworkAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* FmSynthesisFrameworkAudioProcessor::createEditor()
{
    return new FmSynthesisFrameworkAudioProcessorEditor (*this);
}

//==============================================================================
void FmSynthesisFrameworkAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void FmSynthesisFrameworkAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new FmSynthesisFrameworkAudioProcessor();
}
