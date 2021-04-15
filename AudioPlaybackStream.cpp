#include "AudioPlaybackStream.h"

bool AudioPlaybackStream::onGetData(Chunk & data)
{
	globalTime = sf::seconds(((float)playBackPos / 44100.0f));
	sf::Int16 * new_data = new sf::Int16[1024];
	memset(new_data, 0, 1024 * sizeof(sf::Int16));

	int synthSize = synthArrPtr->size();
	sf::Int16 * synthData = new sf::Int16[1024];
	for (Synth * synth : *synthArrPtr) {
		synth->renderSamples(synthData, 1024, globalTime, 44100);
		for (int i = 0; i < 1024; ++i) {
			new_data[i] += synthData[i];
		}
	}
	delete[] synthData;
	
	data.samples = new_data;
	data.sampleCount = 1024;
	playBackPos += 1024; //FLYTTA kanske?
	return true;
}

void AudioPlaybackStream::onSeek(sf::Time timeOffset)
{
	//Update playback position for all the synths
	//playBackPos += 1024;
	//globalTime = timeOffset;
}

AudioPlaybackStream::AudioPlaybackStream(std::vector<Synth *> * synthArrPtr_)
{
	synthArrPtr = synthArrPtr_;
	//initialize soud stream
	initialize(1, 44100);
}
