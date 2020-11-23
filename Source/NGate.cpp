/*
  ==============================================================================

    NGate.cpp
    Created: 23 Nov 2020 5:21:24pm
    Author:  K

  ==============================================================================
*/

#include "globals.h"
#include "NGate.h"

NGate::NGate(double sampleRate, double blockSize)
{
    noiseGate.reset(new juce::dsp::NoiseGate<float>());
    juce::dsp::ProcessSpec spec;
    spec.sampleRate = sampleRate;
    spec.maximumBlockSize = blockSize;
    spec.numChannels = 1;
    noiseGate->prepare(spec);
}

NGate::~NGate() {}

float NGate::process(float sample)
{
    return sample + noiseGate->processSample(0, sample) * G_KHAOS_VAR;
}