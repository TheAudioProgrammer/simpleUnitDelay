/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
SimpleFeedForwardFilterAudioProcessor::SimpleFeedForwardFilterAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       ), tree(*this, nullptr)
#endif
{
    //create normalisable range object for value tree param
    NormalisableRange<float> valueRange (0.0f, 0.49f);
    
    //tree connects to slider from editor to value in processor
    tree.createAndAddParameter("valueControl", "valueControl", "valueControl", valueRange, 0.0, nullptr, nullptr);
}

SimpleFeedForwardFilterAudioProcessor::~SimpleFeedForwardFilterAudioProcessor()
{
}

//==============================================================================
const String SimpleFeedForwardFilterAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool SimpleFeedForwardFilterAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool SimpleFeedForwardFilterAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool SimpleFeedForwardFilterAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double SimpleFeedForwardFilterAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int SimpleFeedForwardFilterAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int SimpleFeedForwardFilterAudioProcessor::getCurrentProgram()
{
    return 0;
}

void SimpleFeedForwardFilterAudioProcessor::setCurrentProgram (int index)
{
}

const String SimpleFeedForwardFilterAudioProcessor::getProgramName (int index)
{
    return {};
}

void SimpleFeedForwardFilterAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void SimpleFeedForwardFilterAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    
    for (int i = 0; i < kChannels; i++)
    {
        dspProcess[i].prepareToPlay();
    }
}

void SimpleFeedForwardFilterAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool SimpleFeedForwardFilterAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void SimpleFeedForwardFilterAudioProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{
    ScopedNoDenormals noDenormals;
    const int totalNumInputChannels  = getTotalNumInputChannels();
    const int totalNumOutputChannels = getTotalNumOutputChannels();
    

    for (int i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());
    
    
    for (int channel = 0; channel < buffer.getNumChannels(); ++channel)
    {
        //input data
        const float* inputData = buffer.getReadPointer(channel);
    
        //output data
        float* outputData = buffer.getWritePointer (channel);
        
        //get the values here from the slider
        coefficientValue = *tree.getRawParameterValue("valueControl");
    
        
        //place audio samples into buffer
        for (int sample = 0; sample < buffer.getNumSamples(); ++sample)
        {
            //get current value from read pointer
            float inputSample = inputData[sample];
            
            //output to speakers
            outputData[sample] = dspProcess[channel].process(inputSample, coefficientValue);
        }
    }
}

//==============================================================================
bool SimpleFeedForwardFilterAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* SimpleFeedForwardFilterAudioProcessor::createEditor()
{
    return new SimpleFeedForwardFilterAudioProcessorEditor (*this);
}

//==============================================================================
void SimpleFeedForwardFilterAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void SimpleFeedForwardFilterAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new SimpleFeedForwardFilterAudioProcessor();
}
