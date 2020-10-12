/*
  ==============================================================================

    PatchSavingDialogBox.cpp
    Created: 12 Oct 2020 11:01:32am
    Author:  Hayden Setlik

  ==============================================================================
*/

#include "PatchSavingDialogBox.h"

PatchDialogBox::PatchDialogBox()
{
    addAndMakeVisible(&nameField);
    nameField.setMultiLine(false);
    nameField.setTextToShowWhenEmpty("Patch Name", juce::Colours::lightslategrey);
    nameField.setPopupMenuEnabled(false);
    
    addAndMakeVisible(&newButton);
    newButton.setButtonText("Save as new patch");
    
    addAndMakeVisible(&overwriteButton);
    overwriteButton.setButtonText("Overwrite current patch");
}

void PatchDialogBox::paint(juce::Graphics &g)
{
    
}

void PatchDialogBox::resized()
{
    
}
