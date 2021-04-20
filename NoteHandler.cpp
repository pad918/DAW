#include "NoteHandler.h"

float NoteHandler::keyIdToFrequency(int id)
{
	int octave = (id / 12) - 1;
	int key = id % 12;
	
	float octaveCoeff = std::pow(2, octave-4);
	
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

bool NoteHandler::sort(Note a, Note b)
{
	return a.clickTime < b.clickTime;
}

void NoteHandler::DEBUG_PRINT_INSTRUMENTNAME(int id, int channel)
{
	std::cout << "Channel = " << channel << "\n";
	if (channel == 9) {
		std::cout << "DRUMS\n";
		return;
	}
	if (id < 8) {
		std::cout << "Piano\n";
	}
	else if (id < 16) {
		std::cout << "Chromatic Percussion\n";
	}
	else if (id < 24) {
		std::cout << "Organ\n";
	}
	else if (id < 32) {
		std::cout << "Guitar\n";
	}
	else if (id < 40) {
		std::cout << "Bass\n";
	}
	else if (id < 48) {
		std::cout << "Strings\n";
	}
	else if (id < 56) {
		std::cout << "Ensemble\n";
	}
	else if (id < 64) {
		std::cout << "Brass\n";
	}
	else if (id < 72) {
		std::cout << "Reed\n";
	}
	else if (id < 80) {
		std::cout << "Pipe\n";
	}
	else if (id < 88) {
		std::cout << "Synth Lead\n";
	}
	else if (id < 96) {
		std::cout << "Synth Pad\n";
	}
	else if (id < 104) {
		std::cout << "Synth Effects\n";
	}
	else if (id < 112) {
		std::cout << "Ethnic\n";
	}
	else if (id < 120) {
		std::cout << "Percussive\n";
	}
	else {
		std::cout << "Sound Effects\n";
	}
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

void NoteHandler::loadFromMidiTrack(TrackChunk & track, int timeDivision)
{
	float tickFraction = (float)5E5 / timeDivision;
	long time=0;
	int program_change = 0;
	std::vector<Note> clickedNotes;
	auto events = track.getEvents();
	for (auto event : events) {
		const Event * ev = event.getEvent();
		if (ev->getType() == MidiType::EventType::MidiEvent) {
			//std::cout << "_______NOTE_______\n";
			const MidiEvent * tmp = (MidiEvent*)ev;
			auto status = tmp->getStatus();
			int deltaTime = event.getDeltaTime().getData();
			int velocity = tmp->getData() & 0b1111111;
			time += deltaTime;// < 10000 ? deltaTime : 0;
			if (status == MidiType::NoteOn && velocity != 0) {
				sf::Time clickTime = sf::seconds(time / tickFraction);
				Note note;
				note.velocity = velocity / 127.0f;
				note.clickTime = clickTime;
				note.keyNum = (int)tmp->getNote();
				note.freq = keyIdToFrequency((int)tmp->getNote());
				clickedNotes.push_back(note);
			}
			if (status == MidiType::NoteOff || (status == MidiType::NoteOn && velocity==0)) {
				for (int i = 0; i < clickedNotes.size(); ++i) {
					auto & note = clickedNotes[i];
					if (note.keyNum == (int)tmp->getNote()) {
						//std::cout << "ADDED NOTE | startPos = " << note.clickTime.asSeconds() << "\n";
						sf::Time relTime = sf::seconds(time / tickFraction); //200
						note.releaseTime = relTime;
						allNotes.push_back(note);
						clickedNotes.erase(clickedNotes.begin() + i);
						i--;
					}
				}
			}
			if (status == MidiType::ProgramChange) {
				int a = program_change;
				program_change = tmp->getData();
				//std::cout << "PC = " << program_change << " | channel = " << (tmp->getStatus() & 0xF) << " \n";
				DEBUG_PRINT_INSTRUMENTNAME(program_change, tmp->getChannel());
			}
		}
	}
	std::cout << "Added " << allNotes.size() << " notes\n";
	//Sort notes based on startTime:
	//std::sort(allNotes.begin(), allNotes.end(), NoteHandler::sort);
	std::sort(allNotes.begin(), allNotes.end(),
		[](const Note & a, const Note & b) -> bool
	{
		return a.clickTime < b.clickTime;
	});
}
