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
        layout.add(std::make_unique<juce::AudioParameterFloat>(sustainId, sustainName, 0.0f, 1.0f , 0.6f));
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
    for(int i = 0; i < 4; ++i)
    {
        auto iStr = juce::String(i);
        auto rateId = "lfoRateParam" + iStr;
        auto rateName = "LFO " + iStr + " Rate";
        auto levelId = "lfoLevelParam" + iStr;
        auto levelName = "LFO " + iStr + " Level";
        auto waveId = "lfoWaveParam" + iStr;
        auto waveName = "LFO " + iStr + " Waveform";
        auto targetId = "lfoTargetParam" + iStr;
        auto targetName = "LFO " + iStr + " Target";
        
        layout.add(std::make_unique<juce::AudioParameterFloat>(rateId, rateName, 0.0f, 20.0f , 1.0f));
        layout.add(std::make_unique<juce::AudioParameterFloat>(levelId, levelName, 0.0f, 1.0f , 1.0f));
        
        juce::StringArray targets;
        targets.add("No target");
        for(int n = 0; n < numOperators; ++n)
        {
            auto nStr = juce::String(n + 1);
            auto opLevel = "Operator " + nStr + " level";
            targets.add(opLevel);
        }
        juce::StringArray waveTypes;
        waveTypes.add("Sine");
        waveTypes.add("Triangle");
        waveTypes.add("Square");
        waveTypes.add("Saw");
        waveTypes.add("Random");
        
        layout.add(std::make_unique<juce::AudioParameterChoice>(targetId, targetName, targets, 0));
        layout.add(std::make_unique<juce::AudioParameterChoice>(waveId, waveName, waveTypes, 0));
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
                       ),  tree(*this, nullptr, "synthParams", createLayout(numOperators)), patchName("patchName")
#endif
{
    for(int i = 0; i < numVoices; ++i)
    {
        synth.addVoice(new FmVoice(numOperators));
    }
    synth.clearSounds();
    synth.addSound(new FmSound());
    
    //creating an XmlElement to represent an empty patch
    tree.state = juce::ValueTree("defaultParams");
    auto defaultValueTreeState = tree.copyState();
    auto defaultXml = *defaultValueTreeState.createXml();
    defaultXml.setAttribute(patchName, "Blank Patch");
    
    auto appFolder = juce::File::getSpecialLocation(juce::File::userApplicationDataDirectory);
    appFolder.setAsCurrentWorkingDirectory();
    auto patchFolder = appFolder.getChildFile("HexFMPatches");
    
    if(patchFolder.hasWriteAccess())
        printf("path is valid\n");
    if(patchFolder.exists() && patchFolder.isDirectory())
    {
        patchFolder.setAsCurrentWorkingDirectory();
    }
    else
    {
        patchFolder.createDirectory();
        patchFolder.setAsCurrentWorkingDirectory();
    }
    //add that blank patch Xml as a file to the patch folder
    auto defaultPatchFile = patchFolder.getChildFile("blankPatchFile");
    if(!defaultPatchFile.existsAsFile())
    {
        defaultPatchFile.create();
        defaultXml.writeTo(defaultPatchFile);
    }
    
    //loading everything from the patch folder into the patchFiles array so we can access them
    patchFiles = patchFolder.findChildFiles(juce::File::findFiles, true);
    allPatchNames.add("-");
    
    //parsing each patch into an XmlElement and adding it to the patchXmlElements array
    if(patchFiles.size() != 0)
    {
        for(int i = 0; i < patchFiles.size(); ++i)
        {
            patchXmlElements.add(new juce::XmlElement(*juce::XmlDocument::parse(patchFiles[i])));
            allPatchNames.add(patchXmlElements.getLast()->getStringAttribute("patchName"));
        }
    }
    currentFile = &defaultPatchFile;
 
    
}

//======================================================================
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
            for(int n = 0; n < 4; ++n)
            {
                auto nStr = juce::String(n);
                auto rateParam = "lfoRateParam" + nStr;
                auto levelParam = "lfoLevelParam" + nStr;
                auto waveParam = "lfoWaveParam" + nStr;
                auto targetParam = "lfoTargetParam" + nStr;
                
                thisVoice->updateLfoRate(tree.getRawParameterValue(rateParam), n);
                thisVoice->updateLfoLevel(tree.getRawParameterValue(levelParam), n);
                thisVoice->updateLfoWave(tree.getRawParameterValue(waveParam), n);
                thisVoice->updateLfoTarget(tree.getRawParameterValue(targetParam), n);
            }
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
    auto state = tree.copyState();
    std::unique_ptr<juce::XmlElement> xml (state.createXml());
    copyXmlToBinary(*xml, destData);
}

void FmSynthesisFrameworkAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    std::unique_ptr<juce::XmlElement> xmlState (getXmlFromBinary (data, sizeInBytes));
            if (xmlState.get() != nullptr)
                if (xmlState->hasTagName (tree.state.getType()))
                    tree.replaceState (juce::ValueTree::fromXml (*xmlState));
}
//==============================================================================
void FmSynthesisFrameworkAudioProcessor::loadPatch(juce::XmlElement patch)
{
    currentXml = &patch;
    auto patchSize = currentXml->toString().getNumBytesAsUTF8();
    setStateInformation(currentXml, (int)patchSize);
}

void FmSynthesisFrameworkAudioProcessor::saveNewPatch(juce::String newPatchName)
{
    auto fileName = juce::File::createLegalFileName(newPatchName);
    auto patchFolder = juce::File::getCurrentWorkingDirectory();
    auto thisFile = patchFolder.getChildFile(fileName);
    if(!thisFile.existsAsFile())
    {
        //these shits r broken!!!
        auto newTree = tree.copyState();
        auto newXml = *newTree.createXml();
        newXml.setAttribute(patchName, newPatchName);
        patchXmlElements.add(new juce::XmlElement(newXml));
    }
}
void FmSynthesisFrameworkAudioProcessor::updateExistingPatch()
{
    //std::unique_ptr<juce::XmlElement> newXml(tree.state.createXml());
}
//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new FmSynthesisFrameworkAudioProcessor();
}
