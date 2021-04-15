#pragma once
#include <iostream>
#include <vector>
#include <array>
#include "Synth.h"
#include "NoteHandler.h"
#include "Note.h"

class HarmonicForm : public Synth{
private:
	std::array<float, 32> amplitude_parameter;
	std::array<float, 32> offset_parameter;
public:
	HarmonicForm();
	virtual void renderSamples(sf::Int16 * buffer, int bufferSize, sf::Time globalPlayBackPostion, int sampleRate);
};