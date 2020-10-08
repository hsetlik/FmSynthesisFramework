/*
  ==============================================================================

    ModulationGrid.cpp
    Created: 6 Oct 2020 1:08:49pm
    Author:  Hayden Setlik

  ==============================================================================
*/

#include <JuceHeader.h>
#include "ModulationGrid.h"

//==============================================================================
ModulationGrid::ModulationGrid(int numOperators)
{
    //create the button objects
    for(int source = 0; source < numOperators; ++source)
    {
        buttons.add(new juce::OwnedArray<ModulationToggle>);
        for(int dest = 0; dest < numOperators; ++dest)
        {
            juce::OwnedArray<ModulationToggle>* buttonSet = buttons.getLast();
            //make each button visible as it is created
            buttonSet->add(new ModulationToggle(source, dest));
            addAndMakeVisible(buttonSet->getLast());
        }
    }
}

ModulationGrid::~ModulationGrid()
{
}

void ModulationGrid::attachButtons(juce::AudioProcessorValueTreeState *pTree)
{
    int operatorCount = (int)buttons.size();
    for(int source = 0; source < operatorCount; ++source)
    {
        juce::OwnedArray<ModulationToggle>* array = buttons[source];
        for(int dest = 0; dest < operatorCount; ++dest)
        {
            ModulationToggle* thisButton = array->getUnchecked(dest);
            thisButton->attach(pTree);
        }
    }
}

void ModulationGrid::resized()
{
    auto bounds = getLocalBounds().reduced(18);
    int n = bounds.getWidth() / 6;
    for(int source = 0; source < buttons.size(); ++source)
    {
        juce::OwnedArray<ModulationToggle>* array = buttons[source];
        for(int dest = 0; dest < buttons.size(); ++dest)
        {
            ModulationToggle* thisButton = array->getUnchecked(dest);
            thisButton->setBounds((source * n) + 18, (dest * n) + 18, n, n);
        }
    }
}

void ModulationGrid::paint(juce::Graphics &g)
{
    auto background = gridColors.RGBColor(87, 110, 117);
    g.fillAll(background);
    auto textColor = juce::Colours::white; //gridColors.RGBColor(37, 50, 53);
    g.setColour(textColor);
    auto labelFont = juce::Font("VCR OSD Mono", 12.0f, 0);
    g.setFont(labelFont);
    auto buttonsBox = getLocalBounds().reduced(18);
    auto area = getLocalBounds();
    int n = area.getWidth() / 8;
    auto labelBox = juce::Rectangle<int> {n, 0, 6 * n, 18};
    g.drawText("Algorithm", labelBox, juce::Justification::centred);
    auto k = buttonsBox.getWidth() / 6;
    //destinaiton numbers
    int bottomLineTop = getHeight() - 15;
    auto destLabel1 = juce::Rectangle<int> {k, bottomLineTop, 7, 15};
    auto destLabel2 = juce::Rectangle<int> {(int)(2 * k), bottomLineTop, 7, 15};
    auto destLabel3 = juce::Rectangle<int> {(int)(3 * k), bottomLineTop, 7, 15};
    auto destLabel4 = juce::Rectangle<int> {(int)(4 * k), bottomLineTop, 7, 15};
    auto destLabel5 = juce::Rectangle<int> {(int)(5 * k), bottomLineTop, 7, 15};
    auto destLabel6 = juce::Rectangle<int> {(int)(6 * k), bottomLineTop, 7, 15};
    
    g.drawText("1", destLabel1, juce::Justification::centred);
    g.drawText("2", destLabel2, juce::Justification::centred);
    g.drawText("3", destLabel3, juce::Justification::centred);
    g.drawText("4", destLabel4, juce::Justification::centred);
    g.drawText("5", destLabel5, juce::Justification::centred);
    g.drawText("6", destLabel6, juce::Justification::centred);
    //source numbers
    int xOffset = 4;
    auto sourceLabel1 = juce::Rectangle<int> {xOffset, (int)(k * 0.75), 7, 15};
    auto sourceLabel2 = juce::Rectangle<int> {xOffset, (int)(k * 1.75), 7, 15};
    auto sourceLabel3 = juce::Rectangle<int> {xOffset, (int)(k * 2.75), 7, 15};
    auto sourceLabel4 = juce::Rectangle<int> {xOffset, (int)(k * 3.75), 7, 15};
    auto sourceLabel5 = juce::Rectangle<int> {xOffset, (int)(k * 4.75), 7, 15};
    auto sourceLabel6 = juce::Rectangle<int> {xOffset, (int)(k * 5.75), 7, 15};
    
    g.drawText("1", sourceLabel1, juce::Justification::centred);
    g.drawText("2", sourceLabel2, juce::Justification::centred);
    g.drawText("3", sourceLabel3, juce::Justification::centred);
    g.drawText("4", sourceLabel4, juce::Justification::centred);
    g.drawText("5", sourceLabel5, juce::Justification::centred);
    g.drawText("6", sourceLabel6, juce::Justification::centred);
}
