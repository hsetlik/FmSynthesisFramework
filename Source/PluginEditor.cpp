/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
FmSynthesisFrameworkAudioProcessorEditor::FmSynthesisFrameworkAudioProcessorEditor (FmSynthesisFrameworkAudioProcessor& p)
    : AudioProcessorEditor (&p), modGrid(numOperators), audioProcessor (p)
{
    for(int i = 0; i < numOperators; ++i)
    {
        allOps.add(new OperatorComponent(i, &audioProcessor.tree));
        addAndMakeVisible(*allOps.getLast());
    }
    addAndMakeVisible(&modGrid);
    modGrid.attachButtons(&audioProcessor.tree);
    setSize (800, 600);
}

FmSynthesisFrameworkAudioProcessorEditor::~FmSynthesisFrameworkAudioProcessorEditor()
{
}
//==============================================================================
void FmSynthesisFrameworkAudioProcessorEditor::resized()
{
    int w = getWidth() / 4;
    int h = getHeight() / 2;
    for(int i = 0; i < numOperators; ++i)
    {
        int y;
        if(i > 2)
            y = h;
        else
            y = 0;
        int xFactor;
        if(i > 2)
            xFactor = xFactor = i - 3;
        else
            xFactor = i;
        allOps[i]->setBounds(w * xFactor, y, w, h);
    }
    modGrid.setBounds(3 * w, 0, w, w);
}
