#pragma once
#include <iostream>
#include <SFML/Audio.hpp>
#include "NoteHandler.h"
#include "Note.h"

class Synth {
protected:
	float attack = 0.1f, decay = 0.2f; // ATT IMPLEMENTERA
public:
	virtual void renderSamples(sf::Int16 * buffer, int bufferSize, sf::Time globalPlayBackPostion, int sampleRate) = 0;
	NoteHandler noteHandler;
};