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
OperatorComponent::OperatorComponent(int index) :
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
    

}
