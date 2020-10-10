/*
  ==============================================================================

    LfoProcessor.cpp
    Created: 9 Oct 2020 9:51:25am
    Author:  Hayden Setlik

  ==============================================================================
*/

#include "LfoProcessor.h"
LfoProcessor::LfoProcessor(int index) : lfoIndex(index)
{
    srand((unsigned) time(NULL));
}

float LfoProcessor::getSampleValue()
{
    float rawValue;
    switch(currentWaveType)
    {
        case 0:
        {
            rawValue = (lfo_osc.sinebuf(currentRate) / 2) + 0.5;
        }
        case 1:
        {
            rawValue = (lfo_osc.triangle(currentRate) / 2) + 0.5;
        }
        case 2:
        {
            rawValue = (lfo_osc.square(currentRate) / 2) + 0.5;
        }
        case 3:
        {
            rawValue = (lfo_osc.saw(currentRate) / 2) + 0.5;
        }
        case 4:
        {
            rawValue = (float) rand() / RAND_MAX;
        }
    }
    return rawValue * currentLevel;
};
