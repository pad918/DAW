#include "Sampler.h"

Sampler::Sampler(std::string pathToSample)
{
	attack = 0.0f;
	std::cout << "Loading sample...\n";
	FileHandler file;
	auto intSamples = file.loadWav(pathToSample);
	if (intSamples.size() == 0) {
		std::cout << "ERROR: Failed to load audio file\n";
		return;
	}
	std::cout << "Length = " << intSamples.size() / 44100.0f << "s\n";
	for (auto & sample : intSamples) {
		samples.push_back((float)sample / 32768.f);
	}
}

void Sampler::renderSamples(sf::Int16 * buffer, int bufferSize, sf::Time globalPlayBackPostion, int sampleRate)
{
	for (int i = 0; i < bufferSize; ++i) {
		noteHandler.update(globalPlayBackPostion);
		int sumAllNotes = 0;
		for (Note & note : noteHandler.activeNotes) {
			int playBackPosInSamples = (int)(0.5f + sampleRate * (globalPlayBackPostion.asSeconds() - note.clickTime.asSeconds()));
			if (playBackPosInSamples + i >= samples.size()) {
				break;
			}
			int tmp = samples[playBackPosInSamples + i] * 32768.0f;
			tmp *= note.velocity * note.getAmp(globalPlayBackPostion + sf::seconds(i / 44100.0f), attack, decay);
			tmp *= amplitude;
			sumAllNotes += tmp;
		}
		buffer[i] = (sf::Int16)sumAllNotes;
	}
}
