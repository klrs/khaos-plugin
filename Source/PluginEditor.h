/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

const int HELL_MODE = 0;
const int OCEAN_MODE = 1;
const int SKY_MODE = 2;
const int CURRENT_MODE = HELL_MODE;

//==============================================================================
/**
*/
class KhaosAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    KhaosAudioProcessorEditor (KhaosAudioProcessor&);
    ~KhaosAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    KhaosAudioProcessor& audioProcessor;
    juce::Slider khaosSlider;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (KhaosAudioProcessorEditor)
};
