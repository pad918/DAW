#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "AudioPlaybackStream.h"

class DAW {
private:
	//Virtual functions
	sf::SoundStream * stream;
public:
	DAW();
	void update();
	void render(sf::RenderWindow & window);
	
	


};