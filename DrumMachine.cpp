#include "DrumMachine.h"
#include "KeyDefinitions.h"

float DrumMachine::getCurrentSample(std::vector<float>& vector, unsigned long samplePos)
{
	if (samplePos >= vector.size()) { return 0; }
	return vector[samplePos] * 32768.0f;
}

DrumMachine::DrumMachine()
{
	attack = 0.0f;
	std::cout << "Loading samples...\n";
	bassDrum = loadSamples("samples/bass_drum.wav");
	highHat = loadSamples("samples/hihat.wav");
}

void DrumMachine::renderSamples(sf::Int16 * buffer, int bufferSize, sf::Time globalPlayBackPostion, int sampleRate)
{
	for (int i = 0; i < bufferSize; ++i) {
		noteHandler.update(globalPlayBackPostion);
		int sumAllNotes = 0;
		for (Note & note : noteHandler.activeNotes) {
			int playBackPosInSamples = (int)(0.5f + sampleRate * (globalPlayBackPostion.asSeconds() - note.clickTime.asSeconds()));
			int tmp = 0; 
			switch (note.keyNum)
			{
			case BASS_DRUM:
				tmp = getCurrentSample(bassDrum, playBackPosInSamples + i);
				break;
			case CLOSED_HI_HAT:
				
			default:
				tmp = getCurrentSample(highHat, playBackPosInSamples + i);
				break;
			}
			tmp *= note.velocity * note.getAmp(globalPlayBackPostion + sf::seconds(i / 44100.0f), attack, decay);
			tmp *= amplitude;
			sumAllNotes += tmp;
		}
		buffer[i] = (sf::Int16)sumAllNotes;
	}
}
