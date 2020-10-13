/*
  ==============================================================================

    PatchManagerComponent.h
    Created: 10 Oct 2020 9:42:19pm
    Author:  Hayden Setlik

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "PluginProcessor.h"

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
    void listenToSaveButton(juce::Button::Listener* lstnr)
    {
        saveButton.addListener(lstnr);
    }
    juce::ComboBox patchSelector;
    
private:
    juce::TextButton saveButton;
    juce::TextButton nextPatchButton;
    juce::TextButton lastPatchButton;
    juce::StringArray displayPatchNames;
};

class SaveButtonListener : public juce::Button::Listener
{
public:
    SaveButtonListener(juce::Component* compToActivate)
    {
        component = compToActivate;
    }
    ~SaveButtonListener() {}
    void buttonClicked(juce::Button* button)
    {
        component->setEnabled(true);
        component->setVisible(true);
        component->toFront(true);
    }
private:
    juce::Component* component;
};

class PatchSelectorListener : public juce::ComboBox::Listener
{
public:
    PatchSelectorListener(FmSynthesisFrameworkAudioProcessor& proc) : processor(&proc)
    {
        
    }
    ~PatchSelectorListener() {}
    void comboBoxChanged(juce::ComboBox* box) override
    {
        auto nameInComboBox = box->getText();
        for(int i = 0; i < processor->patchXmlElements.size(); ++i)
        {
            juce::XmlElement* element = processor->patchXmlElements[i];
            if(element->getStringAttribute("patchName") == nameInComboBox)
            {
                processor->loadPatch(*element);
                printf("Patch Is: %s\n", nameInComboBox.toRawUTF8());
            }
        }
    }
private:
    FmSynthesisFrameworkAudioProcessor* processor;
};
