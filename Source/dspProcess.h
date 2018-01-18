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
    void prepareToPlay();
    
    float process (float currentSample, float sliderValue);
    
private:
    float delayedSample;
    
};
