/*
  ==============================================================================

    DAHDSRGraph.cpp
    Created: 8 Oct 2020 10:33:41am
    Author:  Hayden Setlik

  ==============================================================================
*/

#include "DAHDSRGraph.h"

DAHDSRGraph::DAHDSRGraph(juce::Slider* Delay,
                         juce::Slider* Attack,
                         juce::Slider* Hold,
                         juce::Slider* Decay,
                         juce::Slider* Sustain,
                         juce::Slider* Release):
sDelay(Delay),
sAttack(Attack),
sHold(Hold),
sDecay(Decay),
sSustain(Sustain),
sRelease(Release)
{
    fDelay = 0.0f;
    fAttack = 20.0f;
    fHold = 0.0f;
    fDecay = 100.0f;
    fSustain = 0.6f;
    fRelease = 40.0f;
    bgColor = graphColor.RGBColor(37, 50, 53);
    traceColor = graphColor.RGBColor(250, 172, 63);
    startTimerHz(24);
}

void DAHDSRGraph::grabValues()
{
    if(sAttack->getValue() > 0.0f)
    {
        fDelay = sDelay->getValue();
        fAttack = sAttack->getValue();
        fHold = sHold->getValue();
        fDecay = sDecay->getValue();
        fSustain = sSustain->getValue();
        fRelease = sRelease->getValue();
    }
}

void DAHDSRGraph::paint(juce::Graphics &g)
{
    
    g.fillAll(bgColor);
    
    auto area = getLocalBounds().toFloat();
    auto eDelay = exp(fDelay) * area.getWidth();
    printf("eDelay: %f\n", eDelay);
    printf("fDelay: %f\n", fDelay);
    auto eAttack = exp(fAttack) * area.getWidth();
    auto eHold = exp(fHold) * area.getWidth();
    auto eDecay = exp(fDecay) * area.getWidth();
    auto eRelease = exp(fRelease) * area.getWidth();
    juce::Path trace;
    trace.startNewSubPath(0.0f, area.getHeight());
    trace.lineTo(eDelay, area.getHeight());
    trace.lineTo(eDelay + eAttack, 0.0f);
    trace.lineTo(eDelay + eAttack + eHold, 0.0f);
    auto sustainY = (1.0f - fSustain) * area.getHeight();
    auto timeTotal = eDelay + eAttack + eHold + eDecay + eRelease;
    auto sustainLength = timeTotal * 0.25;
    trace.lineTo(eDelay + eAttack + eHold + eDecay, sustainY);
    trace.lineTo(eDelay + eAttack + eHold + eDecay + sustainLength, sustainY);
    trace.lineTo(timeTotal + sustainLength, area.getHeight());
    trace.closeSubPath();
    trace.scaleToFit(0.0f, 0.0f, area.getWidth(), area.getHeight(), false);
    
    auto stroke = juce::PathStrokeType(1.0f);
    g.setColour(traceColor);
    g.strokePath(trace, stroke);
}
