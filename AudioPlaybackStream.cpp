#include "AudioPlaybackStream.h"

bool AudioPlaybackStream::onGetData(Chunk & data)
{
	sf::Int16 * new_data = new sf::Int16[1024];
	for (int i = 0; i < 1024; ++i) {
		int tmp = 32768;
		float freq = 2.0f * ((playBackPos/4100)%2==0) ? 1000.0f : 2000.0f;
		tmp += (5000.0 * std::cos(3.141592 * freq * (float)(playBackPos+i)/44100.0f));
		new_data[i] = (sf::Int16)tmp;
	}
	data.samples = new_data;
	data.sampleCount = 1024;
	playBackPos += 1024; //FLYTTA kanske?
	return true;
}

void AudioPlaybackStream::onSeek(sf::Time timeOffset)
{
	//Update playback position for all the synths
	//playBackPos += 1024;
}

AudioPlaybackStream::AudioPlaybackStream()
{
	//initialize soud stream
	initialize(1, 44100);
}
