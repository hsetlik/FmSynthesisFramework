

#pragma once
#include <JuceHeader.h>
#include "RGBColor.h"

class EnvLabel : public juce::Label, public juce::Slider::Listener
{
public:
    EnvLabel(juce::Slider* sliderToAttach, juce::String suff) : attachSlider(sliderToAttach), suffix(suff)
    {
        attachSlider->addListener(this);
        setJustificationType(juce::Justification::centred);
        setMinimumHorizontalScale(0.25);
        juce::String tempText;
        auto valueToDraw = attachSlider->getValue();
        auto fullString = juce::String(valueToDraw);
        if(valueToDraw < 100.0f)
            tempText = fullString.substring(0, 3);
        else if(valueToDraw < 1000.0f)
            tempText = fullString.substring(0, 4);
        else
            tempText = fullString.substring(0, 5);
        auto labelText = tempText +  suffix;
        setText(labelText, juce::dontSendNotification);
    }
    ~EnvLabel() {}
    void sliderValueChanged(juce::Slider* slider)
    {
        juce::String tempText;
        auto valueToDraw = attachSlider->getValue();
        auto fullString = juce::String(valueToDraw);
        if(valueToDraw < 100.0f)
            tempText = fullString.substring(0, 3);
        else if(valueToDraw < 1000.0f)
            tempText = fullString.substring(0, 4);
        else
            tempText = fullString.substring(0, 5);
        auto labelText = tempText +  suffix;
        setText(labelText, juce::dontSendNotification);
    }
private:
    juce::Colour textColor = juce::Colours::white;
    juce::Slider* attachSlider;
    juce::String suffix;
};
class LevelSlider : public juce::Slider
{
public:
    LevelSlider(int index) : opIndex(index)
    {
        setSliderStyle(juce::Slider::LinearVertical);
        setTextBoxStyle(juce::Slider::TextBoxBelow, false, 45, 15);
    }
    ~LevelSlider(){}
    void attach(juce::AudioProcessorValueTreeState* pTree)
    {
        juce::String iStr = juce::String(opIndex);
        auto paramId = "levelParam" + iStr;
        attachment.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(*pTree, paramId, *this));
    }
    juce::String idStr;
    int opIndex;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> attachment;
};

class DelaySlider : public juce::Slider
{
public:
    DelaySlider(int index) : opIndex(index)
    {
        setSliderStyle(juce::Slider::Rotary);
        setTextBoxStyle(juce::Slider::NoTextBox, true,0, 0);
    }
    ~DelaySlider(){}
    void attach(juce::AudioProcessorValueTreeState* pTree)
    {
        juce::String iStr = juce::String(opIndex);
        auto paramId = "delayParam" + iStr;
        attachment.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(*pTree, paramId, *this));
    }
    juce::String idStr;
    int opIndex;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> attachment;
};

class AttackSlider : public juce::Slider
{
public:
    AttackSlider(int index) : opIndex(index)
    {
        setSliderStyle(juce::Slider::Rotary);
        setTextBoxStyle(juce::Slider::NoTextBox, true,0, 0);
        
    }
    ~AttackSlider(){}
    void attach(juce::AudioProcessorValueTreeState* pTree)
    {
        juce::String iStr = juce::String(opIndex);
        auto paramId = "attackParam" + iStr;
        attachment.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(*pTree, paramId, *this));
    }
    juce::String idStr;
    int opIndex;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> attachment;
};

class HoldSlider : public juce::Slider
{
public:
    HoldSlider(int index) : opIndex(index)
    {
        setSliderStyle(juce::Slider::Rotary);
        setTextBoxStyle(juce::Slider::NoTextBox, true,0, 0);
    }
    ~HoldSlider(){}
    void attach(juce::AudioProcessorValueTreeState* pTree)
    {
        juce::String iStr = juce::String(opIndex);
        auto paramId = "holdParam" + iStr;
        attachment.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(*pTree, paramId, *this));
    }
    juce::String idStr;
    int opIndex;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> attachment;
};

class DecaySlider : public juce::Slider
{
public:
    DecaySlider(int index) : opIndex(index)
    {
        setSliderStyle(juce::Slider::Rotary);
        setTextBoxStyle(juce::Slider::NoTextBox, true,0, 0);
    }
    ~DecaySlider(){}
    void attach(juce::AudioProcessorValueTreeState* pTree)
    {
        juce::String iStr = juce::String(opIndex);
        auto paramId = "decayParam" + iStr;
        attachment.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(*pTree, paramId, *this));
    }
    int opIndex;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> attachment;
};

class SustainSlider : public juce::Slider
{
public:
    SustainSlider(int index) : opIndex(index)
    {
        setSliderStyle(juce::Slider::Rotary);
        setTextBoxStyle(juce::Slider::NoTextBox, true,0, 0);
    }
    ~SustainSlider(){}
    void attach(juce::AudioProcessorValueTreeState* pTree)
    {
        juce::String iStr = juce::String(opIndex);
        auto paramId = "sustainParam" + iStr;
        attachment.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(*pTree, paramId, *this));
    }
    juce::String idStr;
    int opIndex;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> attachment;
};

class ReleaseSlider : public juce::Slider
{
public:
    ReleaseSlider(int index) : opIndex(index)
    {
        setSliderStyle(juce::Slider::Rotary);
        setTextBoxStyle(juce::Slider::NoTextBox, true,0, 0);
    }
    ~ReleaseSlider(){}
    void attach(juce::AudioProcessorValueTreeState* pTree)
    {
        juce::String iStr = juce::String(opIndex);
        auto paramId = "releaseParam" + iStr;
        attachment.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(*pTree, paramId, *this));
    }
    juce::String idStr;
    int opIndex;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> attachment;
};

class RatioSlider : public juce::Slider
{
public:
    RatioSlider(int index) : opIndex(index)
    {
        setSliderStyle(juce::Slider::Rotary);
        setTextBoxStyle(juce::Slider::TextBoxBelow, false, 45, 15);
        
    }
    ~RatioSlider(){}
    void attach(juce::AudioProcessorValueTreeState* pTree)
    {
        juce::String iStr = juce::String(opIndex);
        auto paramId = "ratioParam" + iStr;
        attachment.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(*pTree, paramId, *this));
    }
    juce::String idStr;
    int opIndex;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> attachment;
};

class ModIndexSlider : public juce::Slider
{
public:
    ModIndexSlider(int index) : opIndex(index)
    {
        setSliderStyle(juce::Slider::Rotary);
        setTextBoxStyle(juce::Slider::TextBoxBelow, false, 45, 15);
    }
    ~ModIndexSlider(){}
    void attach(juce::AudioProcessorValueTreeState* pTree)
    {
        juce::String iStr = juce::String(opIndex);
        auto paramId = "indexParam" + iStr;
        attachment.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(*pTree, paramId, *this));
    }
    juce::String idStr;
    int opIndex;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> attachment;
};

class OutputToggleButton : public juce::TextButton
{
public:
    OutputToggleButton(int index) : opIndex(index)
    {
        setClickingTogglesState(true);
        setButtonText("Output");
        onColor = color.RGBColor(226, 76, 86);
        offColor = color.blend(onColor, juce::Colours::black, 0.085f);
        setColour(juce::TextButton::buttonColourId, offColor);
        setColour(juce::TextButton::buttonOnColourId, onColor);
    }
    ~OutputToggleButton() {}
    void attach(juce::AudioProcessorValueTreeState* pTree)
    {
        juce::String iStr = juce::String(opIndex);
        auto paramId = "audibleParam" + iStr;
        attachment.reset(new juce::AudioProcessorValueTreeState::ButtonAttachment(*pTree, paramId, *this));
    }
    
    int opIndex;
private:
    ColorCreator color;
    juce::Colour onColor;
    juce::Colour offColor;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> attachment;
};



