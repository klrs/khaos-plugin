/*
  ==============================================================================

    NGate.h
    Created: 23 Nov 2020 5:21:24pm
    Author:  K

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "juce_dsp/juce_dsp.h"
#include "Effect.h"

class NGate : public Effect
{
public:

    // Constructor
    // Has to allocate the buffer that we'll be using to store the samples
    NGate(double sampleRate, double blockSize);

    // destructor
    ~NGate();

    float process(float sample);

private:
    std::unique_ptr<juce::dsp::NoiseGate<float>> noiseGate;

};




