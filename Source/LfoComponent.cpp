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
    waveSelector.addItem("None", 1);
    for(int i = 0; i < 6; ++i)
    {
        auto iStr = juce::String(i + 1);
        auto opRatio = "Operator " + iStr + " ratio";
        auto opModIndex = "Operator " + iStr + "mod index";
        auto opLevel = "Operator " + iStr + " level";
        waveSelector.addItem(opRatio, i + 2);
        waveSelector.addItem(opModIndex, i + 3);
        waveSelector.addItem(opLevel, i + 4);
    }
    
    addAndMakeVisible(&targetSelector);
    
    
}
