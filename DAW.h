#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "AudioPlaybackStream.h"
#include "Synth.h"
#include "SineWave.h"

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