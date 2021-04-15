#pragma once
#include <SFML/Audio.hpp>
#include <SFML/Main.hpp>
#include <vector>
#include "Synth.h"

class AudioPlaybackStream : public sf::SoundStream {
private:
	//Virtual functions
	virtual bool onGetData(Chunk& data);
	virtual void onSeek(sf::Time timeOffset);
	uint32_t playBackPos = 0;
	std::vector<Synth *> * synthArrPtr;
	sf::Time globalTime;
public:
	AudioPlaybackStream(std::vector<Synth *> * synthArrPtr_);
};