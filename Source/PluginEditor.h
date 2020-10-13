/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "OperatorComponent.h"
#include "ModulationGrid.h"
#include "RGBColor.h"
#include "LfoGroupComponent.h"
#include "PatchManagerComponent.h"
#include "PatchSavingDialogBox.h"

//==============================================================================
/**
*/
class FmSynthesisFrameworkAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    FmSynthesisFrameworkAudioProcessorEditor (FmSynthesisFrameworkAudioProcessor&);
    ~FmSynthesisFrameworkAudioProcessorEditor() override;

    //==============================================================================
    void resized() override;
    void paint(juce::Graphics &g) override;
    void updatePresetSelection();

private:
    ColorCreator color;
    juce::OwnedArray<OperatorComponent> allOps;
    ModulationGrid modGrid;
    LfoGroupComponent lfoGroup;
    PatchLoader patchLoader;
    PatchDialogBox saveDialog;
    SaveButtonListener saveListener;
    PatchDialogCancelListener cancelListener;
    PatchDialogListener saveDialogListener;
    PatchSelectorListener patchSelectorListener;
    
    std::vector<juce::Colour> opColors;
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    FmSynthesisFrameworkAudioProcessor& audioProcessor;
    

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FmSynthesisFrameworkAudioProcessorEditor)
};
