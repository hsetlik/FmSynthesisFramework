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
        std::vector<ModulationToggle> buttonSet;
        for(int dest = 0; dest < numOperators; ++dest)
        {
            std::unique_ptr<ModulationToggle> toggle(new ModulationToggle(source, dest));
            buttonSet.push_back(*toggle);
            //make each button visible as it is created
            addAndMakeVisible(buttonSet.back());
        }
        buttons.push_back(buttonSet);
    }
}

ModulationGrid::~ModulationGrid()
{
}

void ModulationGrid::attachButtons(juce::AudioProcessorValueTreeState *pTree)
{
    int operatorCount = (int)buttons.size();
    for(int set = 0; set < operatorCount; ++set)
    {
        std::vector<ModulationToggle> currentVector = buttons[set];
        for(int button = 0; button < operatorCount; ++button)
        {
            ModulationToggle* currentButton = &currentVector[button];
            currentButton->attach(pTree);
        }
    }
}

void ModulationGrid::resized()
{
    int n = getWidth() / 6;
    for(int source = 0; source < buttons.size(); ++source)
    {
        std::vector<ModulationToggle> buttonSet = buttons[source];
        for(int dest = 0; dest < buttons.size(); ++dest)
        {
            ModulationToggle* thisButton = &buttonSet[dest];
            thisButton->setBounds(n * source, n * source, n, n);
        }
    }
}
