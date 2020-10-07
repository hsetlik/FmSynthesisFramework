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

//==============================================================================
/*
*/
class OperatorComponent  : public juce::Component
{
public:
    OperatorComponent(int index);
    ~OperatorComponent() override;
    void attachAll(juce::AudioProcessorValueTreeState* pTree)
    {
        levelSlider.attach(pTree);
        ratioSlider.attach(pTree);
        modIndexSlider.attach(pTree);
        outputButton.attach(pTree);
        
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
