/*
  ==============================================================================

    PatchSavingDialogBox.h
    Created: 12 Oct 2020 11:01:32am
    Author:  Hayden Setlik

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "PluginProcessor.h"

class PatchDialogBox : public juce::Component
{
public:
    PatchDialogBox();
    ~PatchDialogBox() {}
    void listenToButtons(juce::Button::Listener* lstnr)
    {
        newButton.addListener(lstnr);
        cancelButton.addListener(lstnr);
    }
    void resized() override;
    void paint(juce::Graphics& g) override;
    juce::String getNewPatchName()
    {
        return nameField.getText();
    }
    juce::TextButton newButton;
    juce::TextButton cancelButton;
private:
    juce::TextEditor nameField;
};

class PatchDialogListener : public juce::Button::Listener
{
public:
    PatchDialogListener(PatchDialogBox* sourceDialogBox, FmSynthesisFrameworkAudioProcessor* proc) : dialogBox(sourceDialogBox), processor(proc)
    {
        dialogBox->listenToButtons(this);
    }
    ~PatchDialogListener() {}
    void buttonClicked(juce::Button* button)
    {
        
    }
private:
    PatchDialogBox* dialogBox;
    FmSynthesisFrameworkAudioProcessor* processor;
};
