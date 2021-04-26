#include "NoteHandler.h"

float NoteHandler::keyIdToFrequency(int id)
{
	int octave = (id / 12) - 1;
	int key = id % 12;
	
	//float octaveCoeff = std::pow(2, octave - 4);
	//FASTER THAN std::POW
	float octaveCoeff = 1;
	int exponent = octave - 4;
	if (exponent == 0) {
		octaveCoeff = 1;
	}
	else if (exponent < 0) {
		while (exponent < 0) {
			octaveCoeff *= 0.5f;
			exponent++;
		}
	}
	else {
		while (exponent > 0) {
			octaveCoeff *= 2.0f;
			exponent--;
		}
	}
	
	switch (key) {
	case 0: //  C
		return 261.63f * octaveCoeff;
	case 1: //  C#
		return 277.18f * octaveCoeff;
	case 2: //  D
		return 293.66f * octaveCoeff;
	case 3: //  D#
		return 311.13f * octaveCoeff;
	case 4: //  E
		return 329.63f * octaveCoeff;
	case 5: //  F
		return 349.23f * octaveCoeff;
	case 6: //  F#
		return 369.99f * octaveCoeff;
	case 7: //  G
		return 391.99f * octaveCoeff;
	case 8: //  G#
		return 415.30f * octaveCoeff;
	case 9: //  A
		return 440.00f * octaveCoeff;
	case 10: // A#
		return 466.16f * octaveCoeff;
	case 11: // B
		return 493.88f * octaveCoeff;
	}
	std::cout << "ERROR: not real key\n";
	return -1;
}

void NoteHandler::setNotes(std::vector<Note>& notes)
{
	allNotes = notes;
}

bool NoteHandler::sort(Note a, Note b)
{
	return a.clickTime < b.clickTime;
}

std::string NoteHandler::getInstrumentName()
{
	if (allNotes.size() == 0){
		return "NO INSTRUMENT";
	}

	int id		=	allNotes[0].instrument;
	int channel =	allNotes[0].channel;

	if (channel == 9) {
		return "Drums";
	}
	if (id < 8) {
		return "Piano";
	}
	else if (id < 16) {
		return "Chromatic Percussion";
	}
	else if (id < 24) {
		return "Organ";
	}
	else if (id < 32) {
		return "Guitar";
	}
	else if (id < 40) {
		return "Bass";
	}
	else if (id < 48) {
		return "Strings";
	}
	else if (id < 56) {
		return "Ensemble";
	}
	else if (id < 64) {
		return "Brass";
	}
	else if (id < 72) {
		return "Reed";
	}
	else if (id < 80) {
		return "Pipe";
	}
	else if (id < 88) {
		return "Synth Lead";
	}
	else if (id < 96) {
		return "Synth Pad";
	}
	else if (id < 104) {
		return "Synth Effects";
	}
	else if (id < 112) {
		return "Ethnic";
	}
	else if (id < 120) {
		return "Percussive";
	}
	else {
		return "Sound Effects";
	}
	return "NO INSTRUMENT";
}


void NoteHandler::update(sf::Time currentTime)
{
	//Check if new notes were pressed
	while(idOfLastPressedNote < allNotes.size() && currentTime > allNotes[idOfLastPressedNote].clickTime) {
		activeNotes.push_back(allNotes[idOfLastPressedNote]);
		activeNotes.back().status = TO_BE_CLICKED;
		idOfLastPressedNote++;
	}

	//Check if any of the active notes were released
	for (int i = 0; i < activeNotes.size(); ++i) {
		if (activeNotes[i].isDead) {
			activeNotes.erase(activeNotes.begin() + i);
			i--;
			continue;
		}
		else if (activeNotes[i].status != WAS_CLICKED && activeNotes[i].releaseTime < currentTime) {
			activeNotes[i].status = WAS_CLICKED;
		}
	}

	timeAtLastUpdate = currentTime;
}

void NoteHandler::addNote(sf::Time start, sf::Time end, float freq)
{
	Note tmp;
	tmp.clickTime = start;
	tmp.releaseTime = end;
	tmp.freq = freq;
	allNotes.push_back(tmp);
}

