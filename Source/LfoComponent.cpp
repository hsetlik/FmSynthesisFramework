/*
  ==============================================================================

    LfoComponent.cpp
    Created: 9 Oct 2020 9:25:18am
    Author:  Hayden Setlik

  ==============================================================================
*/

#include "LfoComponent.h"

LfoComponent::LfoComponent(int index) : lfoIndex(index)
{
    addAndMakeVisible(&rateSlider);
    rateSlider.setRange(0.0f, 20.0f);
    rateSlider.setSliderStyle(juce::Slider::Rotary);
    rateSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 45, 15);
    
    addAndMakeVisible(&levelSlider);
    levelSlider.setRange(0.0f, 1.0f);
    levelSlider.setSliderStyle(juce::Slider::Rotary);
    levelSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 45, 15);
    
    addAndMakeVisible(&waveSelector);
    addAndMakeVisible(&targetSelector);
    
    targetSelector.addItem("No target", 1);
    for(int i = 0; i < 6; ++i)
    {
        auto iStr = juce::String(i + 1);
        auto opLevel = "Operator " + iStr + " level";
        targetSelector.addItem(opLevel, i + 2);
    }
    
    waveSelector.addItem("Sine", 1);
    waveSelector.addItem("Triangle", 2);
    waveSelector.addItem("Saw", 3);
    waveSelector.addItem("Square", 4);
    waveSelector.addItem("Random", 5);
}

void LfoComponent::attachAll(juce::AudioProcessorValueTreeState *pTree)
{
    auto iStr = juce::String(lfoIndex);
    auto rateId = "lfoRateParam" + iStr;
    rateAttach.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(*pTree, rateId, rateSlider));
    
    auto levelId = "lfoLevelParam" + iStr;
    levelAttach.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(*pTree, levelId, levelSlider));
    
    auto waveId = "lfoWaveParam" + iStr;
    waveTypeAttach.reset(new juce::AudioProcessorValueTreeState::ComboBoxAttachment(*pTree, waveId, waveSelector));
    
    auto targetId = "lfoTargetParam" + iStr;
    targetAttach.reset(new juce::AudioProcessorValueTreeState::ComboBoxAttachment(*pTree, targetId, targetSelector));
}

void LfoComponent::resized()
{
    int n = getWidth() / 24;
    levelSlider.setBounds(n, n / 2, 5 * n, 7 * n);
    rateSlider.setBounds(n, 10 * n, 5 * n, 7 * n);
    
    waveSelector.setBounds(7 * n, n, 10 * n, 2 * n);
    targetSelector.setBounds(7 * n, 12 * n, 14 * n, 2 * n);
}

