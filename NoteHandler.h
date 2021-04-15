#pragma once
#include <vector>
#include <iostream>
#include "Note.h"

class NoteHandler {
private:
	std::vector<Note> allNotes;
	sf::Time timeAtLastUpdate;
	int idOfLastPressedNote = 0;
public:
	std::vector<Note> activeNotes;
	void update(sf::Time currentTime);
	void addNote(sf::Time start, sf::Time end, float freq);
	//void loadNotes(std::string path);
};