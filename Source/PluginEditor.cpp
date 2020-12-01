/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "globals.h"
#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
KhaosAudioProcessorEditor::KhaosAudioProcessorEditor (KhaosAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    khaosSliderValue = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treeState, "khaos", khaosSlider);
    freqSliderValue = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treeState, "freq", freqSlider);
    amplSliderValue = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treeState, "ampl", amplSlider);

    compTreshSliderValue = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treeState, "comp-tresh", compTreshSlider);
    compRatioSliderValue = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treeState, "comp-ratio", compRatioSlider);
    compAttackSliderValue = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treeState, "comp-attack", compAttackSlider);
    compReleaseSliderValue = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treeState, "comp-release", compReleaseSlider);
    compKneeSliderValue = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treeState, "comp-knee", compKneeSlider);
    
    gateAttackSliderValue = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treeState, "gate-attack", gateAttackSlider);

    setSize (400, 100);

    khaosSlider.setSliderStyle(juce::Slider::Rotary);
    khaosSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 90, 0);
    freqSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 90, 0);
    amplSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 90, 0);

    addAndMakeVisible(&khaosSlider);
    addAndMakeVisible(&freqSlider);
    addAndMakeVisible(&amplSlider);
    /*
    addAndMakeVisible(&compTreshSlider);
    addAndMakeVisible(&compRatioSlider);
    addAndMakeVisible(&compAttackSlider);
    addAndMakeVisible(&compReleaseSlider);
    addAndMakeVisible(&compKneeSlider);
    addAndMakeVisible(&gateAttackSlider);
    */
}

KhaosAudioProcessorEditor::~KhaosAudioProcessorEditor()
{
}

//==============================================================================
void KhaosAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));

    g.setColour(juce::Colours::dimgrey);
    g.setFont(100.0f);
    g.drawText("KHAOS", getLocalBounds(), juce::Justification::centred, 1);

    g.setFont(10.0f);
    g.setColour(juce::Colours::ghostwhite);
    g.drawText("SINE FREQUENCY", 0, 50, 100, 50, juce::Justification::centredTop, 1);
    g.drawText("SINE AMPLITUDE", 300, 50, 100, 50, juce::Justification::centredTop, 1);
}

void KhaosAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..

    auto border = 100;
    auto area = getLocalBounds();
    auto dialArea = area.removeFromTop(area.getHeight());
    khaosSlider.setBounds(150, 0, 100, 100);
    freqSlider.setBounds(0, 20, 100, 50);
    amplSlider.setBounds(300, 20, 100, 50);

    /*
    compTreshSlider.setBounds(0, 0, 100, 50);
    compRatioSlider.setBounds(0, 50, 100, 50);
    compAttackSlider.setBounds(0, 100, 100, 50);
    compReleaseSlider.setBounds(0, 150, 100, 50);
    compKneeSlider.setBounds(0, 200, 100, 50);

    gateAttackSlider.setBounds(300, 0, 100, 50);
    */

}