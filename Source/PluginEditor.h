/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"


//==============================================================================
/**
*/
class SimpleFeedForwardFilterAudioProcessorEditor : public AudioProcessorEditor, public Slider::Listener
{
public:
    SimpleFeedForwardFilterAudioProcessorEditor (SimpleFeedForwardFilterAudioProcessor&);
    ~SimpleFeedForwardFilterAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;
    
    //inheriting from slider listener so need this pure virtual function
    void sliderValueChanged (Slider*) override;
    
    //create a scoped pointer slider attachment to connect slider value to value on processor
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> a1Value;

private:
    
    //slider to control a1 coefficient
    Slider a1Control;
    
    
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    SimpleFeedForwardFilterAudioProcessor& processor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SimpleFeedForwardFilterAudioProcessorEditor)
};
