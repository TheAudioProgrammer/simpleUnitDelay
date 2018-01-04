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
    NormalisableRange<float> a1Range (0.0f, 0.49f);
    
    //tree connects to slider from editor to value in processor
    tree.createAndAddParameter("a1Control", "A1Control", "a1Control", a1Range, 0.0, nullptr, nullptr);
    
    
    
    
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
    //reinitialize z delay to 0
    z1 = 0.0f;
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
    
    //iterate through channels, reading and writing to one side at a time
    for (int channel = 0; channel < buffer.getNumChannels(); ++channel)
    {
        //input data reads from buffer, then we process data and put back out
        const float* inputData = buffer.getReadPointer(channel, 0);
        float* outputData = buffer.getWritePointer (channel, 0);
    
        //place audio samples into buffer
        for (int sample = 0; sample < buffer.getNumSamples(); ++sample)
        {
            //get the values here from the slider
            a1 = *tree.getRawParameterValue("a1Control");
        
            //design equation a0 = a1 - 1.0
            a0 = a1 - 1.0;
        
            //get current value from read pointer
            float xn = inputData[sample];
            
            //delay by one sample---previous value from output is now the delayed value
            float xn1 = z1;
            
            //use difference equation y(n) = a0x(n) + a1x(n-1)
            float yn = a0 * xn + a1 * xn1;
        
            //current output is stored to become previous output in next loop
            z1 = xn;
        
            //output to speakers
            outputData[sample] = yn;
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
