#pragma once
#include <iostream>
#include <SFML/Audio.hpp>
#include "NoteHandler.h"
#include "Note.h"
#define PI 3.14159265358979f

class Synth {
protected:
	float attack = 0.05f, decay = 0.1f; 
public:
	virtual void renderSamples(sf::Int16 * buffer, int bufferSize, sf::Time globalPlayBackPostion, int sampleRate) = 0;
	NoteHandler noteHandler;
};