#pragma once
#include <SFML/Audio.hpp>

class AudioPlaybackStream : public sf::SoundStream {
private:
	//Virtual functions
	virtual bool onGetData(Chunk& data);
	virtual void onSeek(sf::Time timeOffset);
	uint32_t playBackPos = 0;
public:
	AudioPlaybackStream();
};