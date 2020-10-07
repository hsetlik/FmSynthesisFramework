/*
  ==============================================================================

    OperatorComponent.cpp
    Created: 6 Oct 2020 1:08:26pm
    Author:  Hayden Setlik

  ==============================================================================
*/

#include <JuceHeader.h>
#include "OperatorComponent.h"

//==============================================================================
OperatorComponent::OperatorComponent(int index, juce::AudioProcessorValueTreeState* pTree) :
levelSlider(index),
ratioSlider(index),
modIndexSlider(index),
outputButton(index),
delaySlider(index),
attackSlider(index),
holdSlider(index),
decaySlider(index),
sustainSlider(index),
releaseSlider(index)
{
    attachAll(pTree);
    addAndMakeVisible(&levelSlider);
    addAndMakeVisible(&ratioSlider);
    addAndMakeVisible(&modIndexSlider);
    addAndMakeVisible(&outputButton);
    addAndMakeVisible(&delaySlider);
    addAndMakeVisible(&attackSlider);
    addAndMakeVisible(&holdSlider);
    addAndMakeVisible(&decaySlider);
    addAndMakeVisible(&sustainSlider);
    addAndMakeVisible(&releaseSlider);
    
}

OperatorComponent::~OperatorComponent()
{
}

void OperatorComponent::resized()
{
    int n = getWidth() / 24;
    delaySlider.setBounds(0, n, 4 * n, 7 * n);
    attackSlider.setBounds(4 * n, n, 4 * n, 7 * n);
    holdSlider.setBounds(8 * n, n, 4 * n, 7 * n);
    decaySlider.setBounds(12 * n, n, 4 * n, 7 * n);
    sustainSlider.setBounds(16 * n, n, 4 * n, 7 * n);
    releaseSlider.setBounds(20 * n, n, 4 * n, 7 * n);
    
    outputButton.setBounds(16 * n, 12 * n, 2 * n, n);
    levelSlider.setBounds(n, 12 * n, 3 * n, 5 * n);
    modIndexSlider.setBounds(4 * n, 12 * n, 4 * n, 7 * n);
    ratioSlider.setBounds(8 * n, 12 * n, 4 * n, 7 * n);
}
