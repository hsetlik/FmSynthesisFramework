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
envGraph(&delaySlider, &attackSlider, &holdSlider, &decaySlider, &sustainSlider, &releaseSlider),
levelSlider(index),
ratioSlider(index),
modIndexSlider(index),
outputButton(index),
delaySlider(index),
delayLabel(&delaySlider, "ms"),
attackSlider(index),
attackLabel(&attackSlider, "ms"),
holdSlider(index),
holdLabel(&holdSlider, "ms"),
decaySlider(index),
decayLabel(&decaySlider, "ms"),
sustainSlider(index),
sustainLabel(&sustainSlider, ""),
releaseSlider(index),
releaseLabel(&releaseSlider, "ms")
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
    
    addAndMakeVisible(&envGraph);
    
    addAndMakeVisible(&delayLabel);
    addAndMakeVisible(&attackLabel);
    addAndMakeVisible(&holdLabel);
    addAndMakeVisible(&decayLabel);
    addAndMakeVisible(&sustainLabel);
    addAndMakeVisible(&releaseLabel);
}

OperatorComponent::~OperatorComponent()
{
}

void OperatorComponent::resized()
{
    int n = getWidth() / 24;
    delaySlider.setBounds(n / 2, 23 * n, 4 * n, 4 * n);
    attackSlider.setBounds(4.5 * n, 23 * n, 4 * n, 4 * n);
    holdSlider.setBounds(8.5 * n, 23 * n, 4 * n, 4 * n);
    decaySlider.setBounds(12.5 * n, 23 * n, 4 * n, 4 * n);
    sustainSlider.setBounds(16.5 * n, 23 * n, 4 * n, 4 * n);
    releaseSlider.setBounds(20.5 * n, 23 * n, 4 * n, 4 * n);
    
    delayLabel.setBounds(n / 2, 27 * n, 4 * n, 2 * n);
    attackLabel.setBounds(4.5 * n, 27 * n, 4 * n, 2 * n);
    holdLabel.setBounds(8.5 * n, 27 * n, 4 * n, 2 * n);
    decayLabel.setBounds(12.5 * n, 27 * n, 4 * n, 2 * n);
    sustainLabel.setBounds(16.5 * n, 27 * n, 4 * n, 2 * n);
    releaseLabel.setBounds(20.5 * n, 27 * n, 4 * n, 2 * n);
    
    envGraph.setBounds(n, 13 * n, 15 * n, 10 * n);

    outputButton.setBounds(16 * n, n, 7 * n, 3 * n);
    levelSlider.setBounds(19 * n, 4.5 * n, 4 * n, 12 * n);
    modIndexSlider.setBounds(6 * n, 4 * n, 4 * n, 7 * n);
    ratioSlider.setBounds(11 * n, 4 * n, 4 * n, 7 * n);
}
