/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
SimpleFeedForwardFilterAudioProcessorEditor::SimpleFeedForwardFilterAudioProcessorEditor (SimpleFeedForwardFilterAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    
    //initialization for a1 Control Slider
    a1Control.setSliderStyle(Slider::SliderStyle::LinearVertical);
    a1Control.setRange(0.0f, 0.49f);
    a1Control.setValue(0.0f);
    a1Control.setTextBoxStyle(Slider::TextBoxBelow, true, 50, 30);
    a1Control.addListener(this);
    addAndMakeVisible(&a1Control);
    
    //use slider attachment pointer to link a1Control to processor values
    a1Value = new AudioProcessorValueTreeState::SliderAttachment (processor.tree, "a1Control", a1Control);
    
    setSize (200, 200);
}

SimpleFeedForwardFilterAudioProcessorEditor::~SimpleFeedForwardFilterAudioProcessorEditor()
{
}

//==============================================================================
void SimpleFeedForwardFilterAudioProcessorEditor::paint (Graphics& g)
{
    //reserve area for title
    Rectangle<int> titleArea (0, 10, getWidth(), 20);
    
    //basic graphic stuff for ui
    g.fillAll (Colours::black);
    g.setColour(Colours::white);
    g.drawText("Unit Delay Z-1", titleArea, Justification::centredTop);
    Rectangle <float> area (25, 25, 150, 150);
    g.setColour(Colours::yellow);
    g.drawRoundedRectangle(area, 20.0f, 2.0f);
}

void SimpleFeedForwardFilterAudioProcessorEditor::resized()
{
    //draw the slider
    a1Control.setBounds(75, 30, 50, 140);
}

//don't really need this since processor variable is controlled by the tree, but it's a pure virtual function 
void SimpleFeedForwardFilterAudioProcessorEditor::sliderValueChanged(Slider* slider)
{
    if (slider == &a1Control)
    {
        processor.a1L = a1Control.getValue();
        processor.a1R = a1Control.getValue();
    }
}



