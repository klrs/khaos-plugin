/*
  ==============================================================================

    Compressor.cpp
    Created: 18 Nov 2020 3:13:14pm
    Author:  K

  ==============================================================================
*/

#include "Compressor.h"
#include "globals.h"

Compressor::Compressor() {
    buffer = CircularBuffer(150, 20);
    tav = 0.01;
    rms = 0;
    gain = 1;
}

float Compressor::process(float sample) {
    //return sample;
    return sample + (compressSample(sample, -20.0f, 10.0f, 0.01f, 0.2f, 1.0f) * G_KHAOS_VAR);
}

float Compressor::compressSample(float data, float thresh, float ratio, float attack, float release, float knee) {
    rms = (1 - tav) * rms + tav * std::pow(data, 2.0f); //1
    float dbRMS = 10 * std::log10(rms); //2

    float slope = 1 - (1 / ratio); //1
    float dbGain = std::min(0.0f, (slope * (thresh - dbRMS))); //2
    float newGain = std::pow(10, dbGain / 20); //3

    float coeff;
    if (newGain < gain) coeff = attack; //1
    else coeff = release; //2
    gain = (1 - coeff) * gain + coeff * newGain; //3

    float compressedSample = gain * buffer.getData();
    buffer.setData(data);
    buffer.nextSample();
    return compressedSample;
}