/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
KhaosAudioProcessorEditor::KhaosAudioProcessorEditor (KhaosAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 300);

    khaosSlider.setSliderStyle(juce::Slider::Rotary);
    khaosSlider.setRange(0.0, 127.0, 1.0);
    khaosSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 90, 0);

    addAndMakeVisible(&khaosSlider);
}

KhaosAudioProcessorEditor::~KhaosAudioProcessorEditor()
{
}

//==============================================================================
void KhaosAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));

    g.setColour(juce::Colours::white);
    g.setFont(50.0f);
    g.drawFittedText("KHAOS", getLocalBounds(), juce::Justification::centredTop, 1);
}

void KhaosAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..

    auto border = 100;
    auto area = getLocalBounds();
    auto dialArea = area.removeFromTop(area.getHeight());
    khaosSlider.setBounds(dialArea.reduced(border, border));
}
