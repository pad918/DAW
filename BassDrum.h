#pragma once
#include <vector>
#include "Synth.h"

class BassDrum : public Synth {
private:

public:
	virtual void renderSamples(sf::Int16 * buffer, int bufferSize, sf::Time globalPlayBackPostion, int sampleRate);
};