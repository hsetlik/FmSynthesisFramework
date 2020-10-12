/*
  ==============================================================================

    PatchSavingDialogBox.h
    Created: 12 Oct 2020 11:01:32am
    Author:  Hayden Setlik

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class PatchDialogBox : public juce::Component
{
public:
    PatchDialogBox();
    ~PatchDialogBox() {}
    void listenToButtons(juce::Button::Listener* lstnr)
    {
        newButton.addListener(lstnr);
        overwriteButton.addListener(lstnr);
        cancelButton.addListener(lstnr);
    }
    void resized() override;
    void paint(juce::Graphics& g) override;
    juce::String getNewPatchName()
    {
        return nameField.getText();
    }
    juce::TextButton newButton;
    juce::TextButton overwriteButton;
    juce::TextButton cancelButton;
private:
    juce::TextEditor nameField;
};

class PatchDialogCancelListener : public juce::Button::Listener
{
public:
    PatchDialogCancelListener(juce::Component* comp)
    {
        component = comp;
    }
    ~PatchDialogCancelListener()
    {
        
    }
    void buttonClicked(juce::Button* button) override
    {
        component->setEnabled(false);
        component->setVisible(false);
        component->toBack();
    }
private:
    juce::Component* component;
};
