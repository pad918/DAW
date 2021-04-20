#include "BassDrum.h"

void BassDrum::renderSamples(sf::Int16 * buffer, int bufferSize, sf::Time globalPlayBackPostion, int sampleRate)
{
	
	for (int i = 0; i < bufferSize; ++i) {
		noteHandler.update(globalPlayBackPostion + sf::seconds((float)i/44100.0f));
		int sumAllNotes = 0;
		for (Note & note : noteHandler.activeNotes) {
			int playBackPosInSamples = (int)(0.5f + sampleRate * (globalPlayBackPostion.asSeconds()-note.clickTime.asSeconds()));
			sf::Time timeAlive = globalPlayBackPostion - note.clickTime + sf::seconds((float)i / 44100.0f);
			float lifeSpan = note.releaseTime.asSeconds() - note.clickTime.asSeconds();
			float coeff = timeAlive.asSeconds() < 0.1f ?
				std::cosf(PI * (0.5f / 0.1f) * timeAlive.asSeconds()) : 0.0f;
			int tmp = std::abs(coeff) * 32768.0f * 0.5f * std::sinf(0.125f * PI * 2.0f * note.freq *
				((float)(playBackPosInSamples + i) / 44100.0f));
			float coeff_rev = (timeAlive.asSeconds() - lifeSpan) / lifeSpan;
			float sin = std::sinf(0.125f * PI * 2.0f * note.freq * ((float)(playBackPosInSamples + i) / 44100.0f) + 0.89172376f);
			tmp += 32768.0f * 0.1f * coeff_rev * sin;
			tmp *= note.velocity * note.getAmp(globalPlayBackPostion + sf::seconds(i / 44100.0f), attack, decay);
			tmp *= amplitude;
			sumAllNotes += tmp;
		}
		buffer[i] = (sf::Int16)sumAllNotes;
	}
}
