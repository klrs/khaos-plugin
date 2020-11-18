/*
  ==============================================================================

    Test.h
    Created: 17 Nov 2020 7:36:02pm
    Author:  K

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "Effect.h"

class Test : public Effect
{
public:

    // Constructor
    // Has to allocate the buffer that we'll be using to store the samples
    Test();

    // destructor
    ~Test();

    float process(float sample);

private:

    
};




