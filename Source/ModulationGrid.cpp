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
    int n = getWidth() / 6;
    for(int source = 0; source < buttons.size(); ++source)
    {
        juce::OwnedArray<ModulationToggle>* array = buttons[source];
        for(int dest = 0; dest < buttons.size(); ++dest)
        {
            ModulationToggle* thisButton = array->getUnchecked(dest);
            thisButton->setBounds(source * n, dest * n, n, n);
        }
    }
}
