/*
  ==============================================================================

    DspProcess.cpp
    Created: 18 Jan 2018 12:09:46pm
    Author:  Joshua Hodge

  ==============================================================================
*/

#include "DspProcess.h"

float DspProcess::process (float currentSample, float delayedSample, float sliderValue)
{
    //design equation a0 = a1 - 1.0
    float a0 = sliderValue - 1.0;
    
    //delay by one sample---previous value from output is now the delayed value
    float previousSample = delayedSample;
    
    //use difference equation y(n) = a0x(n) + a1x(n-1)
    float processedSample = a0 * currentSample + sliderValue * previousSample;
    
    //current output is stored to become previous output in next loop
    delayedSample = currentSample;
    
    return processedSample;
}
