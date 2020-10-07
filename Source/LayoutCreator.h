/*
  ==============================================================================

    LayoutCreator.h
    Created: 6 Oct 2020 4:00:02pm
    Author:  Hayden Setlik

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

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
