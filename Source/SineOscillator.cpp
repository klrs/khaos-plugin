#include "SineOscillator.h"

SineOscillator::SineOscillator(float sr, float freq, float initialPhase)
{
    samplerate = sr;
    frequency = freq;
    currentPhaseState = initialPhase;
}

float SineOscillator::getFrequency()
{
    return frequency;
}

void SineOscillator::setFrequency(float newFrequency)
{
    // frequency can't be above nyquist or below 0
    const float nyquist = samplerate / 2;

    // first, let's check that the new frequency is not below 0
    if (newFrequency < 0)
    {
        // if new frequency is below 0, mirror it back to positive axis
        newFrequency = -newFrequency;
    }

    // if we get here, check if our frequency is not above nyquist
    if (newFrequency > nyquist)
    {
        // if above nyquist, cap it to nyquist
        frequency = nyquist;
    }
    else
    {
        frequency = newFrequency;
    }
}

float SineOscillator::getSample()
{
    float oscillation = cos(currentPhaseState);
    return oscillation;
}

void SineOscillator::nextSample() {
    float phaseIncrement = frequency / samplerate * juce::MathConstants<float>::twoPi;

    currentPhaseState += phaseIncrement;

    // wrap the phase
    if (currentPhaseState > juce::MathConstants<float>::twoPi)
        currentPhaseState -= juce::MathConstants<float>::twoPi;
}
