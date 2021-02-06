/*
  ==============================================================================

    PatchManagerComponent.cpp
    Created: 10 Oct 2020 9:42:19pm
    Author:  Hayden Setlik

  ==============================================================================
*/

#include "PatchManagerComponent.h"

PatchLoader::PatchLoader(FmSynthesisFrameworkAudioProcessor* proc, juce::Component* patchDlg)
{
    auto appFolder = juce::File::getSpecialLocation(juce::File::userApplicationDataDirectory);
    appFolder.setAsCurrentWorkingDirectory();
    auto patchFolder = appFolder.getChildFile("HexFM_Patches");
    if(patchFolder.exists() && patchFolder.isDirectory())
    {
        patchFolder.setAsCurrentWorkingDirectory();
    }
    else
    {
        patchFolder.createDirectory();
        patchFolder.setAsCurrentWorkingDirectory();
    }
    presetFolder = &patchFolder;
    
    
    addAndMakeVisible(&patchSelector);
    addAndMakeVisible(&nextPatchButton);
    addAndMakeVisible(&lastPatchButton);
    addAndMakeVisible(&saveButton);
    
    nextPatchButton.addListener(this);
    lastPatchButton.addListener(this);
    saveButton.addListener(this);
    
    nextPatchButton.setButtonText(">");
    lastPatchButton.setButtonText("<");
    saveButton.setButtonText("Save");
    
    
}

void PatchLoader::resized()
{
    int n = getWidth() / 18;
    
    patchSelector.setBounds(n, n / 2, 16 * n, 2 * n);
    
    lastPatchButton.setBounds(4 * n, 4 * n, 3 * n,  2 * n);
    nextPatchButton.setBounds(7 * n, 4 * n, 3 * n,  2 * n);
    saveButton.setBounds(12 * n, 4 * n, 3 * n, 2 * n);
}

void PatchLoader::getPresetsFromFolder()
{
    auto files = presetFolder->findChildFiles(juce::File::findFiles, true);
    auto numFiles = files.size();
    if(numFiles < 0)
    {
        for(int i = 0; i < numFiles; ++i)
        {
            auto currentFile = files.getUnchecked(i);
            std::unique_ptr<juce::XmlElement> currentXml = juce::parseXML(currentFile);
            if(currentXml->hasAttribute("HexFmPatchName"))
            {
                auto presetName = currentXml->getStringAttribute("HexFmPatchName");
                patchNames.add(presetName);
            }
        }
    }
    
}
void PatchLoader::savePreset(juce::String name)
{
    //use the name string to check if the preset already exists or whether a new one is needed
}
void PatchLoader::loadPreset(juce::String presetName)
{
    
}

void PatchLoader::comboBoxChanged(juce::ComboBox* box)
{
    
}
