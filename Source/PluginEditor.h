/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

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
    juce::Slider freqSlider;
    juce::Slider amplSlider;

    //compressor
    juce::Slider compTreshSlider;
    juce::Slider compRatioSlider;
    juce::Slider compAttackSlider;
    juce::Slider compReleaseSlider;
    juce::Slider compKneeSlider;

    //noisegate
    juce::Slider gateAttackSlider;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (KhaosAudioProcessorEditor)

public:
    std::unique_ptr <juce::AudioProcessorValueTreeState::SliderAttachment> khaosSliderValue;
    std::unique_ptr <juce::AudioProcessorValueTreeState::SliderAttachment> freqSliderValue;
    std::unique_ptr <juce::AudioProcessorValueTreeState::SliderAttachment> amplSliderValue;

    std::unique_ptr <juce::AudioProcessorValueTreeState::SliderAttachment> compTreshSliderValue;
    std::unique_ptr <juce::AudioProcessorValueTreeState::SliderAttachment> compRatioSliderValue;
    std::unique_ptr <juce::AudioProcessorValueTreeState::SliderAttachment> compAttackSliderValue;
    std::unique_ptr <juce::AudioProcessorValueTreeState::SliderAttachment> compReleaseSliderValue;
    std::unique_ptr <juce::AudioProcessorValueTreeState::SliderAttachment> compKneeSliderValue;

    std::unique_ptr <juce::AudioProcessorValueTreeState::SliderAttachment> gateAttackSliderValue;
};
