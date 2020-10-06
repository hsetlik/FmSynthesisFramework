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
OperatorComponent::OperatorComponent()
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

}

OperatorComponent::~OperatorComponent()
{
}

void OperatorComponent::paint (juce::Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background

    g.setColour (juce::Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

    g.setColour (juce::Colours::white);
    g.setFont (14.0f);
    g.drawText ("OperatorComponent", getLocalBounds(),
                juce::Justification::centred, true);   // draw some placeholder text
}

void OperatorComponent::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}
