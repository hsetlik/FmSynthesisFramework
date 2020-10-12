/*
  ==============================================================================

    PatchManagerComponent.cpp
    Created: 10 Oct 2020 9:42:19pm
    Author:  Hayden Setlik

  ==============================================================================
*/

#include "PatchManagerComponent.h"

PatchLoader::PatchLoader()
{
    addAndMakeVisible(&patchSelector);
    addAndMakeVisible(&nextPatchButton);
    addAndMakeVisible(&lastPatchButton);
    addAndMakeVisible(&saveButton);
    
    nextPatchButton.setButtonText(">");
    lastPatchButton.setButtonText("<");
    saveButton.setButtonText("Save");
}

void PatchLoader::resized()
{
    int n = getWidth() / 18;
    
    patchSelector.setBounds(n, n / 2, 16 * n, 2 * n);
    
    lastPatchButton.setBounds(4 * n, 4 * n, 3 * n,  2 * n);
    nextPatchButton.setBounds(7 * n, 4 * n, 3 * n,  2 * n);
    saveButton.setBounds(12 * n, 4 * n, 3 * n, 2 * n);
}
