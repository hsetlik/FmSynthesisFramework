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
    auto color0 = color.RGBColor(19, 48, 101);
    opColors.push_back(color0);
    auto color1 = color.RGBColor(87, 189, 233);
    opColors.push_back(color1);
    auto color2 = color.RGBColor(43, 109, 229);
    opColors.push_back(color2);
    auto color3 = color.RGBColor(32, 84, 179);
    opColors.push_back(color3);
    auto color4 = color.RGBColor(25, 52, 102);
    opColors.push_back(color4);
    auto color5 = color.RGBColor(0, 121, 215);
    opColors.push_back(color5);
    
    addAndMakeVisible(&modGrid);
    modGrid.attachButtons(&audioProcessor.tree);
    setSize (1000, 600);
}

FmSynthesisFrameworkAudioProcessorEditor::~FmSynthesisFrameworkAudioProcessorEditor()
{
}
//==============================================================================
void FmSynthesisFrameworkAudioProcessorEditor::paint(juce::Graphics &g)
{
    auto background = color.RGBColor(37, 50, 53);
    g.fillAll(background);
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
