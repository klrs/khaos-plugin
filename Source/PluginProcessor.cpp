/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "DelayLine.h"

//==============================================================================
KhaosAudioProcessor::KhaosAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
    mFormatManager.registerBasicFormats();
    outputBuffer = juce::AudioSampleBuffer(2, 512);

    for(int i = 0; i < mNumVoices; i++)
    {
        mSampler.addVoice(new juce::SamplerVoice());
    }
}

KhaosAudioProcessor::~KhaosAudioProcessor()
{
    mFormatReader = nullptr;
}

//==============================================================================
const juce::String KhaosAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool KhaosAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool KhaosAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool KhaosAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double KhaosAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int KhaosAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int KhaosAudioProcessor::getCurrentProgram()
{
    return 0;
}

void KhaosAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String KhaosAudioProcessor::getProgramName (int index)
{
    return {};
}

void KhaosAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void KhaosAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    const int maxDelayLineInSamples = 10 * sampleRate;

    //effects.push_back(std::move(delayLine));

    delayLine.reset(new DelayLine(maxDelayLineInSamples));

    mSampler.setCurrentPlaybackSampleRate(sampleRate);
}

void KhaosAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool KhaosAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
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

void KhaosAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer(channel);
        auto* sampleChannelData = outputBuffer.getWritePointer(channel);
        const int numSamples = buffer.getNumSamples();

        for (int i = 0; i < numSamples; i++)
        {
            //iterator based range - emulated C pointer shift 
            channelData[i] = delayLine.get()->process(channelData[i]);
        }
    }
}

//==============================================================================
bool KhaosAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* KhaosAudioProcessor::createEditor()
{
    return new KhaosAudioProcessorEditor (*this);
}

//==============================================================================
void KhaosAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void KhaosAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

void KhaosAudioProcessor::loadFile(const juce::String& path)
{
    mSampler.clearSounds();

    auto file = juce::File(path);
    mFormatReader = mFormatManager.createReaderFor(file);

    juce::BigInteger range;
    range.setRange(0, 128, true);

    outputBuffer.clear();

    mFormatReader->read(&outputBuffer, 0, juce::jmin((int)mFormatReader->lengthInSamples, 512), 0, true, true);
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new KhaosAudioProcessor();
}