#include "NoteHandler.h"

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
