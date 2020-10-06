/*
  ==============================================================================

    ModulationGrid.h
    Created: 6 Oct 2020 1:08:49pm
    Author:  Hayden Setlik

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class ModulationGrid  : public juce::Component
{
public:
    ModulationGrid();
    ~ModulationGrid() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ModulationGrid)
};
