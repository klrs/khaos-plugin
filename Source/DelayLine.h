#pragma once
// ^ always put that in the .h file

#include "../JuceLibraryCode/JuceHeader.h"
#include "Effect.h"

// A simple delay line with interpolated reads.
class DelayLine : public Effect
{
public:

    // Constructor
    // Has to allocate the buffer that we'll be using to store the samples
    DelayLine(int maxNumSamples);

    // destructor
    ~DelayLine();

    // Push a new sample into the delay line
    void pushSample(float sample);

    // Get a sample that has been delayed delayInSamples amount
    float getDelayedSample(int delayInSamples);

    // Get a sample, but interpolated. We need to use this if the delay read tap moves
    float getDelayedSampleInterp(float delayInSamples);

    float process(float sample);

private:

    std::unique_ptr<juce::AudioBuffer<float>> buffer;

    int writehead;
    const int maxNumSamples;
};






