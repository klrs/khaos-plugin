#pragma once

class Effect
{
public:
	float virtual process(float sample) { return sample; }
};
