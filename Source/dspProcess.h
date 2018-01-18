/*
  ==============================================================================

    DspProcess.h
    Created: 18 Jan 2018 12:09:46pm
    Author:  Joshua Hodge

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

class DspProcess
{
public:
    float process (float currentSample, float delayedSample, float sliderValue);
    
private:
    
};
