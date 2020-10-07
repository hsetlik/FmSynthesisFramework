/*
  ==============================================================================

    ModulationGrid.h
    Created: 6 Oct 2020 1:08:49pm
    Author:  Hayden Setlik

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "RGBColor.h"

//==============================================================================


class ModulationToggle : public juce::ShapeButton
{
public:
    ModulationToggle(int source, int dest) : juce::ShapeButton("modButton", color.blend(buttonOnColor, juce::Colours::black, 0.085), color.blend(buttonOnColor, juce::Colours::black, 0.085), color.RGBColor(226, 76, 86)),
    sourceOp(source),
    destOp(dest)
    {
        shouldUseOnColours(true);
        setClickingTogglesState(true);
        buttonOnColor = color.RGBColor(226, 76, 86);
        buttonOffColor = color.blend(buttonOnColor, juce::Colours::black, 0.085);
    }
    ~ModulationToggle() {}
    void attach(juce::AudioProcessorValueTreeState* pTree)
    {
        auto sString = juce::String(sourceOp);
        auto dString = juce::String(destOp);
        auto paramId = sString + "to" + dString + "Param";
        attachment.reset(new juce::AudioProcessorValueTreeState::ButtonAttachment(*pTree, paramId, *this));
    }
    int sourceOp;
    int destOp;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> attachment;
private:
    ColorCreator color;
    juce::Colour buttonOnColor;
    juce::Colour buttonOffColor;
};

class ModulationGrid  : public juce::Component
{
public:
    ModulationGrid(int numOperators);
    ~ModulationGrid() override;
    void attachButtons(juce::AudioProcessorValueTreeState* pTree);
    //void paint (juce::Graphics&) override;
    void resized() override;

private:
    juce::OwnedArray<juce::OwnedArray<ModulationToggle>> buttons;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ModulationGrid)
};
