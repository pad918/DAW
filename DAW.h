#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <fstream>
#include "AudioPlaybackStream.h"
#include "Synth.h"
#include "SineWave.h"
#include "HarmonicForm.h"
#include "BassDrum.h"
#include "Sampler.h"
#include "MIDI/Midi.h"

class DAW {
private:
	//Virtual functions
	sf::SoundStream * stream;
	std::vector<Synth *> synths;
public:
	DAW();
	void update();
	void render(sf::RenderWindow & window);
	
};