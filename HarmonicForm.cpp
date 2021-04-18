#include "HarmonicForm.h"

HarmonicForm::HarmonicForm()
{
	amplitude_parameter = {1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0, 0.0, 0, 0, 0.8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0.30f, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0.1f, 0, 0 };
	offset_parameter = {0, 0.0, 0.0, 0, 0.0, 0.0, 0, 0, 0, 0.25, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0.125f, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0.01, 0, 0 };
	for (int i = 0; i < 32; i+=1) {
		amplitude_parameter[i] = 1.0f / (1.0 + (float)(i % 2 + i));
		//offset_parameter[i] = 1.0f - (1.0f / (1.0 + (float)i));
	}
}

void HarmonicForm::renderSamples(sf::Int16 * buffer, int bufferSize, sf::Time globalPlayBackPostion, int sampleRate)
{
	//Info: https://en.wikipedia.org/wiki/Additive_synthesis
	int playBackPosInSamples = (int)(0.5f + sampleRate * globalPlayBackPostion.asSeconds());
	for (int i = 0; i < bufferSize; ++i) {
		noteHandler.update(globalPlayBackPostion);
		int sumAllNotes = 0;
		for (Note & note : noteHandler.activeNotes) {
			int tmp = 0;
			for (int k = 0; k < 32; ++k) {
				tmp += (32768.0f * 0.05f * amplitude_parameter[k] * std::cosf(PI * 2.0f * note.freq * (float)(k+1) 
					 * ((float)(playBackPosInSamples + i) / 44100.0f) + offset_parameter[k]));
			}
			tmp *= note.velocity * note.getAmp(globalPlayBackPostion + sf::seconds(i / 44100.0f), attack, decay);
			tmp *= amplitude;
			sumAllNotes += tmp;
		}
		buffer[i] = (sf::Int16)sumAllNotes;
	}
}
