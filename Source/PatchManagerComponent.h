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
    void loadNames(juce::StringArray* patchNames)
    {
        for(int i = 0; i > patchNames->size(); ++i)
        {
            allPatchNames.add(patchNames->getReference(i));
            patchSelector.addItem(allPatchNames[i], i + 1);
        }
    }
    juce::ComboBox* getSelectorBox()
    {
        return &patchSelector;
    }
    void nextPatch();
    void lastPatch();
private:
    juce::TextButton nextPatchButton;
    juce::TextButton lastPatchButton;
    juce::StringArray allPatchNames;
    juce::ComboBox patchSelector;
    juce::TextButton saveButton;
    
};
