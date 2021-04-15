#include "SineWave.h"

void SineWave::renderSamples(sf::Int16 * buffer, int bufferSize, sf::Time globalPlayBackPostion, int sampleRate)
{
	//memset(buffer, 0, 1024 * sizeof(sf::Uint16));
	int playBackPosInSamples = (int)(0.5f + sampleRate * globalPlayBackPostion.asSeconds());
	for (int i = 0; i < bufferSize; ++i) {
		noteHandler.update(globalPlayBackPostion);
		int tmp = 0;
		for (Note & note : noteHandler.activeNotes) {
			tmp += (5000.0f * std::sinf(PI * 2.0f * note.freq * (float)(playBackPosInSamples + i) / 44100.0f));
		}
		buffer[i] = (sf::Int16)tmp;
	}
	
}

SineWave::SineWave(float freq)
{
	frequency = 2.0f*freq;
}
