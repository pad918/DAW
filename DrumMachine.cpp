#include "DrumMachine.h"
#include "KeyDefinitions.h"

float DrumMachine::getCurrentSample(std::vector<float>& vector, unsigned long samplePos)
{
	if (samplePos >= vector.size()) { return 0; }
	return vector[samplePos] * 32768.0f;
}

DrumMachine::DrumMachine()
{
	attack = 0.00f;
	decay = 0.05f;
	std::cout << "Loading samples...\n";
	bassDrum = loadSamples("samples/bass_drum.wav");
	highHat = loadSamples("samples/hihat.wav");

	//GET BASS DRUM SUM
	double a = 0;
	for (auto samp : bassDrum) {
		a += std::abs(samp);
	}
	std::cout << "BASS DRUM = " << a << " | size of basedum = " << bassDrum.size() << "\n";
}

void DrumMachine::renderSamples(sf::Int16 * buffer, int bufferSize, sf::Time globalPlayBackPostion, int sampleRate)
{
	for (int i = 0; i < bufferSize; ++i) {
		noteHandler.update(globalPlayBackPostion + sf::seconds((float)i/44100.0f));
		int sumAllNotes = 0;
		for (Note & note : noteHandler.activeNotes) {
			int playBackPosInSamples = (int)(0.5f + sampleRate * (globalPlayBackPostion.asSeconds() - note.clickTime.asSeconds()));
			int tmp = 0; 

			if (note.keyNum == BASS_DRUM) {
				tmp = getCurrentSample(bassDrum, playBackPosInSamples + i);
			}
			else if (note.keyNum == CLOSED_HI_HAT) {
				tmp = getCurrentSample(highHat, playBackPosInSamples + i);
			}
			else {
				tmp = getCurrentSample(highHat, playBackPosInSamples + i);
			}

			tmp *= note.velocity * note.getAmp(globalPlayBackPostion + sf::seconds(i / 44100.0f), attack, decay);
			tmp *= amplitude;
			sumAllNotes += tmp;
		}
		buffer[i] = (sf::Int16)sumAllNotes;
	}
}
