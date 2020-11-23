/*
  ==============================================================================

    Reverb.cpp
    Created: 23 Nov 2020 3:35:26pm
    Author:  K

  ==============================================================================
*/

#include "Reverb.h"
#include "globals.h"

Reverb::Reverb(const double sampleRate)
{
    reverb.setSampleRate(sampleRate);
}

Reverb::~Reverb() {}

float Reverb::process(float sample)
{
    float processedSample = sample;
    reverb.processMono(&processedSample, 1);
    return sample + processedSample * G_KHAOS_VAR;
}


