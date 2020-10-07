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
    auto color0 = color.RGBColor(131, 189, 161);
    opColors.push_back(color0);
    auto color1 = color.RGBColor(131, 169, 181);
    opColors.push_back(color1);
    auto color2 = color.RGBColor(87, 110, 117);
    opColors.push_back(color2);
    auto color3 = color.RGBColor(88, 89, 84);
    opColors.push_back(color3);
    auto color4 = color.RGBColor(37, 50, 53);
    opColors.push_back(color4);
    auto color5 = color.RGBColor(107, 200, 185);
    opColors.push_back(color5);
    
    addAndMakeVisible(&modGrid);
    modGrid.attachButtons(&audioProcessor.tree);
    setSize (800, 600);
}

FmSynthesisFrameworkAudioProcessorEditor::~FmSynthesisFrameworkAudioProcessorEditor()
{
}
//==============================================================================
void FmSynthesisFrameworkAudioProcessorEditor::paint(juce::Graphics &g)
{
    for(int i = 0; i < 6; ++i)
    {
        auto rect = allOps[i]->getBounds();
        g.setColour(opColors[i]);
        g.fillRect(rect);
    }
}

void FmSynthesisFrameworkAudioProcessorEditor::resized()
{
    int w = getWidth() / 4;
    int h = getHeight() / 2;
    allOps[0]->setBounds(0, 0, w, h);
    allOps[1]->setBounds(w, 0, w, h);
    allOps[2]->setBounds(2 * w, 0, w, h);
    allOps[3]->setBounds(0, h, w, h);
    allOps[4]->setBounds(w, h, w, h);
    allOps[5]->setBounds(2 * w, h, w, h);
    modGrid.setBounds(3 * w, 0, w, w);
}
