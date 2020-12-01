#pragma once

// remember this!
#include "../JuceLibraryCode/JuceHeader.h"

// A simple sine oscillator that we use for our LFOs
class SineOscillator
{
public:
    SineOscillator(float sr, float freq, float initialPhase);

    // Note! No destructor a.k.a. ~SineOscillator, because we don't need to assign and delete memory

    // Get current frequency
    float getFrequency();

    // Set a new frequency
    void setFrequency(float newFrequency);

    // Get next output sample determined by the frequency and currentPhaseState.
    // This also increments the state.
    float getSample();

    void nextSample();

private:

    float samplerate;
    float frequency;

    // current phase state should wrap around 2*pi
    float currentPhaseState;
};