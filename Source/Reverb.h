/*
  ==============================================================================

    Reverb.h
    Created: 23 Nov 2020 3:35:26pm
    Author:  K

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "Effect.h"

class Reverb : public Effect
{
public:

    // Constructor
    // Has to allocate the buffer that we'll be using to store the samples
    Reverb(const double sampleRate);

    // destructor
    ~Reverb();

    float process(float sample);

private:
    juce::Reverb reverb;

};




