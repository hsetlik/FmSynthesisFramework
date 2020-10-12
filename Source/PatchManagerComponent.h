/*
  ==============================================================================

    PatchManagerComponent.h
    Created: 10 Oct 2020 9:42:19pm
    Author:  Hayden Setlik

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class PatchLoader : public juce::Component, juce::Button::Listener
{
public:
    PatchLoader();
    ~PatchLoader() {}
    void resized() override;
    void loadNames(juce::StringArray patchNames)
    {
        patchSelector.addItemList(patchNames, 1);
    }
    juce::ComboBox* getSelectorBox()
    {
        return &patchSelector;
    }
    void buttonClicked(juce::Button* button) override
    {
        auto totalItems = patchSelector.getNumItems();
        auto currentIndex = patchSelector.getSelectedItemIndex();
        auto maxIncrease = totalItems - currentIndex;
        if(button == &nextPatchButton && maxIncrease > 0)
        {
            patchSelector.setSelectedItemIndex(currentIndex + 1);
        }
        else if(button == &lastPatchButton && (currentIndex - 1) >= 0)
        {
            patchSelector.setSelectedItemIndex(currentIndex - 1);
        }
    }
    void nextPatch();
    void lastPatch();
    juce::ComboBox patchSelector;
private:
    juce::TextButton nextPatchButton;
    juce::TextButton lastPatchButton;
    juce::StringArray displayPatchNames;
    juce::TextButton saveButton;
};
