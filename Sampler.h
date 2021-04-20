#pragma once
#include <vector>
#include <string>
#include <iostream>
#include "Synth.h"
#include "FileHandler.h"

class Sampler : public Synth {
private:
	std::vector<float> samples;
	int baseKey = 0; //NOT IMPLEMENTED!
public:
	Sampler(std::string pathToSample);
	virtual void renderSamples(sf::Int16 * buffer, int bufferSize, sf::Time globalPlayBackPostion, int sampleRate);
};