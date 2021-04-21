#pragma once
#include <iostream>
#include <SFML/Audio.hpp>
#include <vector>
#include "NoteHandler.h"
#include "Note.h"
#include "FileHandler.h"
#define PI 3.14159265358979f

class Synth {
protected:
	std::vector<float> loadSamples(std::string path);
public:
	virtual void renderSamples(sf::Int16 * buffer, int bufferSize, sf::Time globalPlayBackPostion, int sampleRate) = 0;
	NoteHandler noteHandler;
	float amplitude = 1.0f;
	float attack = 0.05f, decay = 0.1f;
};