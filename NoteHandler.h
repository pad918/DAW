#pragma once
#include <vector>
#include <iostream>
#include <algorithm>
#include "Note.h"
#include "MIDI/Midi.h"

class NoteHandler {
private:
	std::vector<Note> allNotes;
	sf::Time timeAtLastUpdate;
	int idOfLastPressedNote = 0;
	float keyIdToFrequency(int id);
	bool sort(Note a, Note b);
	void DEBUG_PRINT_INSTRUMENTNAME(int id, int channel);
public:
	std::vector<Note> activeNotes;
	void update(sf::Time currentTime);
	void addNote(sf::Time start, sf::Time end, float freq);
	void loadFromMidiTrack(TrackChunk &track, int timeDivision);
	//void loadNotes(std::string path);
};