/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

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
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
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
            thisVoice->setAlgorithm(&tree);
            for(int i = 0; i < numOperators; ++i)
            {
                auto iStr = juce::String(i);
                auto ratioId = "ratioParam" + iStr;
                auto levelId = "levelParam" + iStr;
                auto modIndexId = "modIndexParam" + iStr;
                auto audibleId = "audibleParam" + iStr;
                
                auto delayId = "delayParam" + iStr;
                auto attackId = "attackParam" + iStr;
                auto holdId = "holdParam" + iStr;
                auto decayId = "decayParam" + iStr;
                auto sustainId = "sustainParam" + iStr;
                auto releaseId = "releaseId" + iStr;
                
                thisVoice->setParameters(i, tree.getRawParameterValue(ratioId),
                                         tree.getRawParameterValue(delayId),
                                         tree.getRawParameterValue(attackId),
                                         tree.getRawParameterValue(holdId),
                                         tree.getRawParameterValue(decayId),
                                         tree.getRawParameterValue(sustainId),
                                         tree.getRawParameterValue(releaseId),
                                         tree.getRawParameterValue(levelId),
                                         tree.getRawParameterValue(modIndexId),
                                         tree.getRawParameterValue(audibleId));
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
