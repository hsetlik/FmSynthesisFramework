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
    }
    void listenToTextEditor(juce::TextEditor::Listener* lstnr)
    {
        nameField.addListener(lstnr);
    }
    void resized() override;
    void paint(juce::Graphics& g) override;
    juce::TextButton newButton;
    juce::TextButton overwriteButton;
private:
    juce::TextEditor nameField;
};

class PatchNameListener : public juce::TextEditor::Listener
{
    PatchNameListener();
    ~PatchNameListener() {}
    void textEditorTextChanged(juce::TextEditor &editor) override;
    void textEditorReturnKeyPressed(juce::TextEditor &editor) override;
    void textEditorEscapeKeyPressed(juce::TextEditor &editor) override;
    void textEditorFocusLost(juce::TextEditor &editor) override;
};
