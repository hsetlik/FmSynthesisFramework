

#pragma once
#include <JuceHeader.h>

class LevelSlider : public juce::Slider
{
public:
    LevelSlider(int index) : opIndex(index)
    {
        setSliderStyle(juce::Slider::Rotary);
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
        setTextBoxStyle(juce::Slider::TextBoxBelow, false, 45, 15);
        
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
        setTextBoxStyle(juce::Slider::TextBoxBelow, false, 45, 15);
        
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
        setTextBoxStyle(juce::Slider::TextBoxBelow, false, 45, 15);
        
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
        setTextBoxStyle(juce::Slider::TextBoxBelow, false, 45, 15);
        
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
        setTextBoxStyle(juce::Slider::TextBoxBelow, false, 45, 15);
        
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
        setTextBoxStyle(juce::Slider::TextBoxBelow, false, 45, 15);
        
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
        auto paramId = "modIndexParam" + iStr;
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
        setButtonText("Output");
    }
    ~OutputToggleButton() {}
    void attach(juce::AudioProcessorValueTreeState* pTree)
    {
        juce::String iStr = juce::String(opIndex);
        auto paramId = "audibleParam" + iStr;
        attachment.reset(new juce::AudioProcessorValueTreeState::ButtonAttachment(*pTree, paramId, *this));
    }
    int opIndex;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> attachment;
};



