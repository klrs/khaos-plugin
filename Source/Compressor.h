/*
  ==============================================================================

    Compressor.h
    Created: 18 Nov 2020 3:13:14pm
    Author:  K

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "Compressor.h"
#include "CircularBuffer.h"

class Compressor
{
public:

    // Constructor
    // Has to allocate the buffer that we'll be using to store the samples
    Compressor();

    // destructor
    ~Compressor();

    float process(float sample, float khaos, float sineSample);

private:
    float compressSample(float data, float thresh, float ratio, float attack, float release, float knee);
    CircularBuffer buffer;
    float tav, rms, gain;
};

