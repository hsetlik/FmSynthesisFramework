/*
  ==============================================================================

    OperatorComponent.h
    Created: 6 Oct 2020 1:08:26pm
    Author:  Hayden Setlik

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "SliderSubclasses.h"
#include "RGBColor.h"

//==============================================================================
/*
*/
class OperatorComponent  : public juce::Component
{
public:
    OperatorComponent(int index, juce::AudioProcessorValueTreeState* pTree);
    ~OperatorComponent() override;
    void attachAll(juce::AudioProcessorValueTreeState* pTree)
    {
        outputButton.attach(pTree);
        levelSlider.attach(pTree);
        ratioSlider.attach(pTree);
        modIndexSlider.attach(pTree);
        
        
        delaySlider.attach(pTree);
        attackSlider.attach(pTree);
        holdSlider.attach(pTree);
        decaySlider.attach(pTree);
        sustainSlider.attach(pTree);
        releaseSlider.attach(pTree);
    }
    void resized() override;
    int opIndex;
private:
    ColorCreator color;
    juce::Colour background;
    LevelSlider levelSlider;
    RatioSlider ratioSlider;
    ModIndexSlider modIndexSlider;
    OutputToggleButton outputButton;
    
    DelaySlider delaySlider;
    AttackSlider attackSlider;
    HoldSlider holdSlider;
    DecaySlider decaySlider;
    SustainSlider sustainSlider;
    ReleaseSlider releaseSlider;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (OperatorComponent)
};
