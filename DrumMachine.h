#pragma once
#include <vector>
#include <iostream>
#include "Synth.h"
#include "FileHandler.h"

class DrumMachine : public Synth {
private:
	std::vector<float> bassDrum, highHat;
	float getCurrentSample(std::vector<float> &vector, unsigned long samplePos);
public:
	DrumMachine();
	virtual void renderSamples(sf::Int16 * buffer, int bufferSize, sf::Time globalPlayBackPostion, int sampleRate);
};