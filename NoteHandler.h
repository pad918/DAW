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
	
	bool sort(Note a, Note b);
	
public:
	std::vector<Note> activeNotes;
	void update(sf::Time currentTime);
	void addNote(sf::Time start, sf::Time end, float freq);
	float keyIdToFrequency(int id);
	void setNotes(std::vector<Note> & notes);
	std::string getInstrumentName();
	//void loadNotes(std::string path);
};