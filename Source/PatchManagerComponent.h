/*
  ==============================================================================

    PatchManagerComponent.h
    Created: 10 Oct 2020 9:42:19pm
    Author:  Hayden Setlik

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class PatchLoader : public juce::Component
{
public:
    PatchLoader();
    ~PatchLoader() {}
    void resized() override;
    
};
