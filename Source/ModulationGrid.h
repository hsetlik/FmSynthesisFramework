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
    ModulationToggle(int source, int dest) : juce::ShapeButton("modButton", toggleColors.blend(buttonOnColor, juce::Colours::black, 0.085), toggleColors.blend(buttonOnColor, juce::Colours::black, 0.085), toggleColors.RGBColor(226, 76, 86)),
    sourceOp(source),
    destOp(dest)
    {
        shouldUseOnColours(true);
        setClickingTogglesState(true);
        buttonOnColor = toggleColors.RGBColor(226, 76, 86);
        buttonOffColor = toggleColors.blend(buttonOnColor, juce::Colours::black, 0.085);
    }
    ~ModulationToggle() {}
    void paintButton(juce::Graphics& g, bool mouseOver, bool isMouseDown) override
    {
        g.setColour(buttonOffColor);
        if(getToggleState())
            g.setColour(buttonOnColor);
        auto rect = getLocalBounds().reduced(3);
        g.fillRect(rect);
    }
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
    ColorCreator toggleColors;
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
