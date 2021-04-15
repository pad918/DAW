#pragma once
#include <SFML/Audio.hpp>
#include "Synth.h"

class SineWave : public Synth {
private:
	float frequency = 1000;
public:
	virtual void renderSamples(sf::Int16 * buffer, int bufferSize, sf::Time globalPlayBackPostion, int sampleRate);
	SineWave(float freq);
};
